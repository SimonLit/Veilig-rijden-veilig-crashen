WiFiClient client_Controller;
const char* host_Controller = "10.10.0.28";
const int httpPort_Controller = 80;

WiFiClient client_sendCrashData;
const char* host_sendCrashData = "192.168.1.100";
const int httpPort_sendCrashData = 5500;


/*
   Request the speed value from the controller.
   The string to sent to the RP6 are stored in the String pointers
   from the parameters.

   Return: -1 if connection with the controller broke.
            0 if the controller values are received
*/
int getControllerValues(String* controllerToRP6Protocol)
{
  int nackCounter = 0;
  int timeOutTimer = millis();
  String speedValue = "";
  int valueSeparetor = -1;
  String steerValue = "";

  if (!client_Controller.connect(host_Controller, httpPort_Controller))
  {
    return -1;
  }

  nackCounter = 0;
  timeOutTimer = millis();

  //!!!
  //TODO: Make sure a identity check is implemented.
  //!!!

  makeProtocolString(CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND);
  client_Controller.print(protocolStringToSend);

  String controllerValuesString = "";
  while (client_Controller.available() && ((millis() - timeOutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String controllerValuesString = client_Controller.readString();

    if (getIncommingStringFromMessage(controllerValuesString, &controllerValuesString, sizeof(controllerValuesString)))
    {
      switch (checkForValidControllerMessage(controllerValuesString))
      {
        // The message with the controller values are received.
        case 1:
          if (getIncommingStringFromMessage(controllerValuesString, &controllerValuesString, controllerValuesString.length()))
          {
            if (controllerValuesString.substring(0, 16) == CONTROLLER_VALUE_PROTOCOL_RECEIVE)
            {
              valueSeparetor = controllerValuesString.indexOf(MULTI_VALUE_SEPARATOR);
              steerValue = controllerValuesString.substring(17, valueSeparetor);
              speedValue = controllerValuesString.substring(valueSeparetor + 1);
            }
          }

          makeProtocolStringWith2Value(CONTROLLER_VALUES, speedValue, steerValue);
          *controllerToRP6Protocol = protocolStringToSend;

          lastControllerReceiveTimer = millis();
          client_Controller.stop();

          return 0;

        // The message that was send from the controller to the wemos doesn't
        // match any of the defined protocols.
        case 0:
          makeProtocolString(GENERAL_NACK);
          client_Controller.print(protocolStringToSend);
          break;

        // NACK is received
        case -1:
          makeProtocolString(CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND);
          client_Controller.print(protocolStringToSend);
          nackCounter++;
          break;
      }
    }
  }

  if ((millis() - timeOutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_Controller.stop();
    return -1;
  }
}

/*
   Send all items from the crash data to the boardComputer.
*/
int connectToBoardcomputerAndSendCrashData(String CrashDataProtocol[], int numberOfCrashDataDataToSend)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  // Make a connection with the boardcomputer.
  if (!client_sendCrashData.connect(host_sendCrashData, httpPort_sendCrashData)) {
    return -1;
  }

  // Send the Identification info.
  makeProtocolStringWith2Value(CONNECT_TO_DEVICE, (String)WEMOS_NAME, (String)WEMOS_NUMBER);
  client_sendCrashData.print(protocolStringToSend);

  while (client_sendCrashData.available() && ((millis() - timeoutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      switch (checkForValidBoardcomputerMessage(crashDataResponse))
      {
        // If the identity is verified send the crash data to the boardcomputer.
        case 1:
          return sendCrashData(CrashDataProtocol, numberOfCrashDataDataToSend);
          break;

        // The message that was send from the boardcomputer to the wemos doesn't
        // match any of the defined protocols.
        case 0:
          makeProtocolString(GENERAL_NACK);
          client_sendCrashData.print(protocolStringToSend);
          break;

        // NACK was received
        case -1:
          nackCounter++;
          makeProtocolStringWith2Value(CONNECT_TO_DEVICE, (String)WEMOS_NAME, (String)WEMOS_NUMBER);
          client_sendCrashData.print(protocolStringToSend);
          break;
      }
    }
  }

  if ((millis() - timeoutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_sendCrashData.stop();
    return -1;
  }
}

/*
 * Send the crash data to the boardcomputer.
 */
int sendCrashData(String CrashDataProtocol[], int numberOfCrashDataDataToSend)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  // The connection was verified. Now the crash data has to be send to the boardcomputer.
  // Send the chrash data to the boardcomputer.
  client_sendCrashData.print(CrashDataProtocol[0] + '|' +
                             CrashDataProtocol[1] + '|' +
                             CrashDataProtocol[2] + '|' +
                             CrashDataProtocol[3] + '|' +
                             CrashDataProtocol[4]);

  while (client_sendCrashData.available() && ((millis() - timeoutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      switch (checkForValidBoardcomputerMessage(crashDataResponse))
      {
        case 1:
          client_sendCrashData.stop();
          return 1;

        // The message that was send from the boardcomputer to the wemos doesn't
        // match any of the defined protocols.
        case 0:
          makeProtocolString(GENERAL_NACK);
          client_sendCrashData.print(protocolStringToSend);
          break;

        case -1:
          client_sendCrashData.print(CrashDataProtocol[0] + '|' +
                                     CrashDataProtocol[1] + '|' +
                                     CrashDataProtocol[2] + '|' +
                                     CrashDataProtocol[3] + '|' +
                                     CrashDataProtocol[4]);
          break;

      }
    }
  }
  
  if ((millis() - timeoutTimer) > maxResponseTimeout || (nackCounter > maxNACKCounter))
  {
    client_sendCrashData.stop();
    return -1;
  }
}

void sendRP6StatusToBoardcomputer(void)
{
  makeProtocolString(RP6States[RP6State]);
}
