WiFiClient client_sendCrashData;
const char* host_sendCrashData = "10.10.0.1";
const int httpPort_sendCrashData = 5000;

/*
   Connect to the boardcomputer
*/
int connectToBoardcomputer(void)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  // Make a connection with the boardcomputer.
  if (!client_sendCrashData.connect(host_sendCrashData, httpPort_sendCrashData))
  {
    //Serial.println("Couldn't connect to boardcomputer");
    return -1;
  }
  //Serial.println("Something");

  // Send the Identification info.
  makeProtocolStringWithValue(CONNECT_TO_DEVICE, (String)WEMOS_NAME);
  client_sendCrashData.print(protocolStringToSend);

  while (((millis() - timeoutTimer) < maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();
    //Serial.println(crashDataResponse);

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      if (crashDataResponse == GENERAL_ACK)
      {
        // If the identity is verified send the crash data to the boardcomputer.
        //Serial.println("Connected to boardcomputer");
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
    //Serial.println("Nope on connect request.");
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
    return -1;
  }
}

int sendRP6StatusToBoardcomputer(void)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  makeProtocolString(RP6States[RP6State]);
  client_sendCrashData.print(protocolStringToSend);
  //Serial.println("Sending RP6 state.");

  while (((millis() - timeoutTimer) <= maxResponseTimeout) && (nackCounter <= maxNACKCounter))
  {
    String crashDataResponse = client_sendCrashData.readString();
    //Serial.println(crashDataResponse);

    if (getIncommingStringFromMessage(crashDataResponse, &crashDataResponse, sizeof(crashDataResponse)))
    {
      if (crashDataResponse == GENERAL_ACK)
      {
        client_sendCrashData.stop();
        //Serial.println("Succes sending RP6 state.");
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
    //Serial.println("Nope on sending RP6 state.");
    return -1;
  }
}
