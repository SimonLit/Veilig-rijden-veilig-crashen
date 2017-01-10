WiFiClient client_Controller;
const char* host_Controller = "10.10.0.30";
const int httpPort_Controller = 80;

WiFiClient client_sendCrashData;
const char* host_sendCrashData = "10.10.0.1";
const int httpPort_sendCrashData = 5000;


/*
   Request the speed value from the controller.
   The string to sent to the RP6 are stored in the String pointers
   from the parameters.

   Return: -1 if connection with the controller broke.
            0 if the controller values are received
*/
int getControllerValues(String* controllerToRP6Protocol)
{
  String speedValue = "";
  int valueSeparetor = -1;
  String steerValue = "";
  
  if (!client_Controller.connect(host_Controller, httpPort_Controller))
  {
    return -1;
  }
  makeProtocolString(CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND);
  client_Controller.print(protocolStringToSend);

  String controllerValuesString = client_Controller.readStringUntil('@');
  //if (getIncommingStringFromMessage(controllerValuesString, &controllerValuesString, controllerValuesString.length()))
  //{
    if (controllerValuesString.substring(1, 17) == CONTROLLER_VALUE_PROTOCOL_RECEIVE)
    {
      valueSeparetor = controllerValuesString.indexOf(MULTI_VALUE_SEPARATOR);
      steerValue = controllerValuesString.substring(18, valueSeparetor);
      speedValue = controllerValuesString.substring(valueSeparetor + 1);
    }

    makeProtocolStringWith2Value(CONTROLLER_VALUES, speedValue, steerValue);
    *controllerToRP6Protocol = protocolStringToSend;
    
    //client_Controller.stop();
    return 0;
  //}

  //client_Controller.stop();
  //return -1;
}

/*
   Connect to the boardcomputer
*/
int connectToBoardcomputer(void)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  // Make a connection with the boardcomputer.
  if (!client_sendCrashData.connect(host_sendCrashData, httpPort_sendCrashData)) {
    return -1;
  }

  // Send the Identification info.
  makeProtocolStringWithValue(CONNECT_TO_DEVICE, (String)WEMOS_NAME);
  client_sendCrashData.print(protocolStringToSend);
  Serial.println("Sending connect request to boardcomputer");

  while (((millis() - timeoutTimer) < maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();
    Serial.println(crashDataResponse);

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      if (crashDataResponse == GENERAL_ACK)
      {
        // If the identity is verified send the crash data to the boardcomputer.
        Serial.println("Connected to boardcomputer");
        return 1;
      }
      else if (crashDataResponse == GENERAL_NACK)
      {
        nackCounter++;
        makeProtocolStringWithValue(CONNECT_TO_DEVICE, (String)WEMOS_NAME);
        client_sendCrashData.print(protocolStringToSend);
        timeoutTimer = millis();
      }
      else
      {
        // The message that was send from the boardcomputer to the wemos doesn't
        // match any of the defined protocols.
        makeProtocolString(GENERAL_NACK);
        client_sendCrashData.print(protocolStringToSend);
      }
    }
  }

  if ((millis() - timeoutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_sendCrashData.stop();
    Serial.println("Nope on connect request.");
    return -1;
  }
}

/*
   Send the crash data to the boardcomputer.
*/
int sendCrashData(String CrashDataProtocol, int numberOfCrashDataDataToSend)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  // The connection was verified. Now the crash data has to be send to the boardcomputer.
  // Send the chrash data to the boardcomputer.
  makeProtocolString(CrashDataProtocol);
  client_sendCrashData.print(protocolStringToSend);
  Serial.println("sending Crash data");

  while (((millis() - timeoutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();
    Serial.println(crashDataResponse);

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      Serial.println(crashDataResponse);
      switch (checkForValidBoardcomputerMessage(crashDataResponse))
      {
        case 1:
          client_sendCrashData.stop();
          Serial.println("Succes sending crash data.");
          return 1;

        // The message that was send from the boardcomputer to the wemos doesn't
        // match any of the defined protocols.
        case 0:
          makeProtocolString(GENERAL_NACK);
          client_sendCrashData.print(protocolStringToSend);
          break;

        case -1:
          makeProtocolString(CrashDataProtocol);
          client_sendCrashData.print(protocolStringToSend);
          nackCounter++;
          timeoutTimer = millis();
          break;

      }
    }
  }

  if ((millis() - timeoutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_sendCrashData.stop();
    Serial.println("Nope on sending crash data.");
    return -1;
  }
}

int sendRP6StatusToBoardcomputer(void)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  makeProtocolString(RP6States[RP6State]);
  client_sendCrashData.print(protocolStringToSend);
  Serial.println("Sending RP6 state.");

  while (((millis() - timeoutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();
    Serial.println(crashDataResponse);

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      if (crashDataResponse == GENERAL_ACK)
      {
        client_sendCrashData.stop();
        Serial.println("Succes sending RP6 state.");
        return 1;
      }
      else if (crashDataResponse == GENERAL_NACK)
      {
        makeProtocolString(RP6States[RP6State]);
        client_sendCrashData.print(protocolStringToSend);
      }
      // The message that was send from the boardcomputer to the wemos doesn't
      // match any of the defined protocols.
      else
      {
        makeProtocolString(GENERAL_NACK);
        client_sendCrashData.print(protocolStringToSend);
      }
    }
  }

  if ((millis() - timeoutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_sendCrashData.stop();
    Serial.println("Nope on sending RP6 state.");
    return -1;
  }
}
