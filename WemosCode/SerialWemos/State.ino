String connectResponse = CONNECTED_ACK_RECEIVE + (String)VALUE_CHARACTER + (String)RP6_NAME;
long lastControllerReceived = 0;

void actOnState_WemosToRP6Connection(void)
{
  switch (WemosToRP6Connection)
  {
    case RP6_DISCONNECTED:
      RP6State = STOPPED_PROGRAM;

      // Send a connect request to the RP6.
      makeProtocolStringWithValue(CONNECT_TO_DEVICE, WEMOS_NAME);

      // if the the RP6 send a message back that confirms the connectionis opened.
      // set the WemosToRP6Connection to connected so data can be exchanged.
      if (timeoutHandlerWemosToRP6(protocolStringToSend, connectResponse) == 0)
      {
        WemosToRP6Connection = RP6_CONNECTED;
        lastControllerReceiveTimer = millis();
        lastHeartbeatTimer = millis();
        lastYPRUpdate = millis();
      }

      break;

    case RP6_CONNECTED:
      // Send a heartbeatRequest to the RP6 every 1 second.

      sendHeartbeatToRP6();


      // Update the values in the currentYPR array to the latest YPR values from the MPU.
      // The YPR values are then corrected with the offset values.
      if ((millis() -  lastYPRUpdate) > updateTime)
      {
        updateCurrentOrientation(currentYPR);
        lastYPRUpdate = millis();
      }

      // Receive the controller values and send these to the RP6.
      if ((millis() - lastControllerReceiveTimer) > controllerRequestInterval)
      {
        ControllerSoftwareSerial.begin(38400);
        
        makeProtocolString(CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND);
        ControllerSoftwareSerial.print(protocolStringToSend);
        lastControllerReceiveTimer = millis();
      }

      receivedEndOfSerialString = false;

      // Check if the RP6 has send a message.
      receivedEndOfSerialString = getIncommingString(&stringFromSerial);

      // When a '@' is received from the Serial line a potentional protocol message is received.
      if (receivedEndOfSerialString)
      {
        if (stringFromSerial != GENERAL_ACK)
        {
          if (checkForValidRP6Message(stringFromSerial) == 1)
          {
            makeProtocolString(GENERAL_ACK);
            Serial.println(protocolStringToSend);

            if (stringFromSerial == RP6_STARTED_PROGRAM)
            {
              softwareSerial.begin(38400);
              
              RP6State = STARTED_PROGRAM;
              makeProtocolString(RP6States[RP6State]);
              softwareSerial.print(protocolStringToSend);
            }
            else if (stringFromSerial == RP6_STOPPED_PROGRAM)
            {
              softwareSerial.begin(38400);
              
              RP6State = STOPPED_PROGRAM;
              makeProtocolString(RP6States[RP6State]);
              softwareSerial.print(protocolStringToSend);
            }

            //  When ORIENTATION is received it means all the crash data is received
            //  from the RP6 and can be send to the boardcomputer.
            if (stringFromSerial == ORIENTATION_PROTOCOL_RECEIVE)
            {
              softwareSerial.begin(38400);
              
              String crashDataForBoardcomputer = SEND_DATA_TO_BOARDCOMPUTER_INDICATOR + (String)MULTI_COMMAND_SEPARATOR +
                                                 protocolToSendArray[0] + (String)MULTI_COMMAND_SEPARATOR +
                                                 protocolToSendArray[1] + (String)MULTI_COMMAND_SEPARATOR +
                                                 protocolToSendArray[2] + (String)MULTI_COMMAND_SEPARATOR +
                                                 protocolToSendArray[3] + (String)MULTI_COMMAND_SEPARATOR +
                                                 protocolToSendArray[4];  
              makeProtocolString(crashDataForBoardcomputer);
              softwareSerial.print(protocolStringToSend);
            }
          }

          // When the received message isn't in the protocol from RP6 to Wemos a NACK is send to the RP6.
          else if (checkForValidRP6Message(stringFromSerial) == 0)
          {
            makeProtocolString(GENERAL_NACK);
            Serial.println(protocolStringToSend);
          }

          // This method checks if the received message belongs to one of the recieved crach data messages
          // and puts the message with their values in de crash data arrray.
          formatMessageToProtocol(stringFromSerial, protocolToSendArray);
        }

        // Set the boolean to false to ensure these actions only happen again when a potantional valid
        // serial message is received.
        receivedEndOfSerialString = false;
      }

      // Check if the network wemos send a message.
      receivedEndOfControllerSoftwareSerialString = getIncommingStringFromControllerSoftwareSerial(&stringFromControllerSoftwareSerial);

      if((millis() - lastControllerReceived) > 2000)
      {
        RP6State = STOPPED_PROGRAM;
      }
      if (receivedEndOfControllerSoftwareSerialString)
      {
        if (stringFromControllerSoftwareSerial.indexOf(CONTROLLER_VALUES) > -1)
        {
          makeProtocolString(stringFromControllerSoftwareSerial);
     
          int timeoutState = timeoutHandlerWemosToRP6(protocolStringToSend, GENERAL_ACK);
          if (timeoutState == -1)
          {
            WemosToRP6Connection = RP6_DISCONNECTED;
          }
          else if (timeoutState == 0)
          {
            WemosToRP6Connection = RP6_CONNECTED;
          }
        }
        else if (stringFromControllerSoftwareSerial == "ControllerDisconnected")
        {
          WemosToRP6Connection = RP6_DISCONNECTED;
        }

        lastControllerReceived = millis();

        receivedEndOfControllerSoftwareSerialString = false;
      }

      break;
  }
}

void sendHeartbeatToRP6(void)
{
  if ((millis() -  lastHeartbeatTimer) > heartbeatInterval)
  {
    makeProtocolString(HEARTBEAT_RP6);

    // No response from the RP6 was received on the heartbeat request.
    if (timeoutHandlerWemosToRP6(protocolStringToSend, GENERAL_ACK) == -1)
    {
      WemosToRP6Connection = RP6_DISCONNECTED;
    }
    else
    {
      lastHeartbeatTimer = millis();
    }
    receivedEndOfSerialString = false;
  }
}

void actOnState_RP6State(void)
{
  if (lastRP6State != RP6State)
  {
    softwareSerial.begin(38400);
    
    makeProtocolString(RP6States[RP6State]);
    softwareSerial.print(protocolStringToSend);
    lastRP6State = RP6State;
  }
}

void actOnState_WemosToCTRLConnection(void)
{
  if (lastWemosToCTRLConnection != WemosToCTRLConnection)
  {
    makeProtocolString(ctrlConnectionStates[WemosToCTRLConnection]);

    if (timeoutHandlerWemosToRP6(protocolStringToSend, GENERAL_ACK))
    {
      WemosToRP6Connection = RP6_DISCONNECTED;
    }

    lastWemosToCTRLConnection = WemosToCTRLConnection;
  }
}
