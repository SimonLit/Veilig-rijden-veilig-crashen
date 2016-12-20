String connectResponse = CONNECTED_ACK_RECEIVE + (String)VALUE_CHARACTER + (String)RP6_NAME;

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
      }

      break;

    case RP6_CONNECTED:
      // Send a heartbeatRequest to the RP6 every 1 second.
      if ((millis() -  lastHeartbeatTimer) > heartbeatInterval)
      {
        sendHeartbeatToRP6();
      }

      // Update the values in the currentYPR array to the latest YPR values from the MPU.
      // The YPR values are then corrected with the offset values.
      if ((millis() -  lastYPRUpdate) > updateTime)
      {
        //updateCurrentOrientation(currentYPR);
        lastYPRUpdate = millis();
      }

      // Receive the controller values and send these to the RP6.
      if ((millis() - lastControllerReceiveTimer) > controllerRequestInterval)
      {
        //sendAndReceiveController();
      }

      receivedEndOfSerialString = false;

      // Check if the RP6 has send a message.
      receivedEndOfSerialString = getIncommingString(&stringFromSerial);

      // When a '@' is received from the Serial line a potentional protocol message is received.
      if (receivedEndOfSerialString)
      {
        if (checkForValidRP6Message(stringFromSerial) == 1)
        {
          makeProtocolString(GENERAL_ACK);
          Serial.println(protocolStringToSend);

          if (stringFromSerial == RP6_STARTED_PROGRAM)
          {
            RP6State = STARTED_PROGRAM;
          }
          else if (stringFromSerial == RP6_STOPPED_PROGRAM)
          {
            RP6State = STOPPED_PROGRAM;
          }

          //  When ORIENTATION is received it means all the crash data is received
          //  from the RP6 and can be send to the boardcomputer.
          if (stringFromSerial == ORIENTATION_PROTOCOL_RECEIVE)
          {
            if (connectToBoardcomputer() == 1);
            {
              sendCrashData(protocolToSendArray, 5);
            }
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

        // Set the boolean to false to ensure these actions only happen again when a potantional valid
        // serial message is received.
        receivedEndOfSerialString = false;
      }
      break;
  }
}

void sendHeartbeatToRP6(void)
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

void sendAndReceiveController()
{
  // Format the received controller values to the protcol that is send
  // form the wemos to the RP6 to let the RP6 drive.
  // If getControllerValues return 0 is means the controller
  // values are received correctly

  int statusControllerConnection = getControllerValues(&controllerToRP6Protocol);
  switch (statusControllerConnection)
  {
    // Succes
    case 0:
      // Check is GENERAL_ACK is received from the RP6.
      if (timeoutHandlerWemosToRP6(controllerToRP6Protocol, GENERAL_ACK) == -1)
      {
        Serial.println("No ACK on heartbeat");
        WemosToRP6Connection = RP6_DISCONNECTED;
      }

      WemosToCTRLConnection = CTRL_CONNECTED;
      break;

    // Fail
    case -1:
      //WemosToCTRLConnection = CTRL_DISCONNECTED;
      break;
  }
}

void actOnState_RP6State(void)
{
  if (lastRP6State != RP6State)
  {
    if (connectToBoardcomputer() == 1);
    {
      sendRP6StatusToBoardcomputer();
    }
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
