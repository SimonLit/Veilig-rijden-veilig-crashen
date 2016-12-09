void actOnState(void)
{
  switch (WemosToRP6Connection)
  {
    case RP6_DISCONNECTED:
      // Send a connect request to the RP6.
      Serial.println(START_CHARACTER + CONNECT_TO_DEVICE + (String)RP6_NAME + END_CHARACTER);
      break;
    case RP6_CONNECTED:
      /*
        Send a heartbeatRequest to the RP6 every 1 second.
      */
      if ((millis() -  lastHeartbeatTimer) > heartbeatInterval)
      {
        // Send the heartbeat request.
        String heartBeatString = START_CHARACTER +  HEARTBEAT_RP6 + END_CHARACTER;
        Serial.println(heartBeatString);

        // Wait for a ACK to come back.
        while (!receivedEndOfSerialString  && (millis() -  lastHeartbeatTimer) <= maxResponseTimeout)
        {
          // Read incomming messages.
          receivedEndOfSerialString = getIncommingString(&stringFromSerial);
        }

        // While the Incomming message is NACK or the the maximum timeout seconds hasn't passed (1.2 seconds)
        // send the message again and check if the messag is ACK.
        while (checkForValidRP6Message(stringFromSerial) == -1 && (millis() -  lastHeartbeatTimer) <= maxResponseTimeout)
        {
          Serial.println(heartBeatString);
          getIncommingString(&stringFromSerial);
          if (checkForValidRP6Message(stringFromSerial) == 1)
          {
            break;
          }
        }

        // If the timeout time has passed send a message to the boardcomputer saying the RP6 is offline
        // and thus stopped driving.
        if ((millis() -  lastHeartbeatTimer) > maxResponseTimeout)
        {
          sendRP6StatusToBoardcomputer(START_CHARACTER + RP6States[RP6State] + END_CHARACTER);
        }

        lastHeartbeatTimer = millis();
      }

      /*
         Update the values in the currentYPR array to the latest YPR values from the MPU.
         The YPR values are then corrected with the offset values.
      */
      if ((millis() -  lastYPRUpdate) > updateTime)
      {
        updateCurrentOrientation(currentYPR);
        lastYPRUpdate = millis();
      }

      /*
         Reset the orentation values close to 0.
      */
      if (stringFromSerial == "RESET")
      {
        Serial.println(stringFromSerial);
        stringFromSerial = "";
        resetYPRValues();
      }

      /*
         Receive the controller values and send these to the RP6.
      */
      if ((millis() - currentMillis) > requestInterval)
      {
        getControllerValues(&speedProtocol, &steerProtocol);
        currentMillis = millis();
      }

      /*
         When the no controller messages are received for maxControllerTimeoutTimer amount of time
         send a messsage to the RP6 that sais that the RP6 must stop driving.
      */
      if ((millis() - lastControllerReceiveTimer) > maxControllerTimeoutTimer)
      {
        String noControllerMessage = START_CHARACTER + CONTROLLER_DISCONNECTED + END_CHARACTER;
        Serial.println(noControllerMessage);
      }

      /*
         When a '@' is received from the Serial line a potentional protocol message is received.
      */
      if (receivedEndOfSerialString)
      {
        if (checkForValidRP6Message(stringFromSerial) == 1)
        {
          if (stringFromSerial == RP6_STARTED_PROGRAM || stringFromSerial == RP6_STOPPED_PROGRAM)
          {
            sendRP6StatusToBoardcomputer(stringFromSerial);
          }


          //  When ORIENTATION is received it means all the crash data is received
          //  from the RP6 and can be send to the boardcomputer.
          if (stringFromSerial == ORIENTATION_PROTOCOL_RECEIVE)
          {
            sendCrashData(protocolToSendArray, 5);
          }
        }

        // When the received message isn't in the protocol from RP6 to Wemos a NACK is send to the RP6.
        if (checkForValidRP6Message(stringFromSerial) == 0)
        {
          String nackMessage = START_CHARACTER + GENERAL_NACK + END_CHARACTER;
          Serial.println(nackMessage);
        }

        // If the received message was NACK, send the speed speed values again.
        else if (checkForValidRP6Message(stringFromSerial) == -1)
        {
          Serial.println(speedProtocol);
          Serial.println(steerProtocol);
        }

        // This method checks if the received message belongs to one of the recieved crach data messages
        // and puts the message with their values in de crash data arrray.
        formatMessageToProtocol(stringFromSerial, protocolToSendArray);

        // Set the boolean to false to ensure these actions only happen again when a potantional valid
        // serial message is received.
        protocolEndCharReceived = false;
      }
      break;
  }
}

void changeState(void)
{
  
}

