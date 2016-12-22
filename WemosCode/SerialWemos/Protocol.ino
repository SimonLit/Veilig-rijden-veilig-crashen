int nrStringIn_arrayWithRP6Protcols = 7;
String arrayWithRP6Protocol_receive[] = {RP6_STARTED_PROGRAM, RP6_STOPPED_PROGRAM, SPEED_PROTOCOL_SEND_RECEIVE,
                                         SIDE_HIT_PROTOCOL_SEND_RECEIVE, IMPACT_PROTOCOL_SEND_RECEIVE,
                                         DIST_DRIVEN_PROTOCOL_SEND_RECEIVE, ORIENTATION_PROTOCOL_RECEIVE
                                        };

/*
   Assing the received crash data values to the corresponding indexes of the array.

   Return: 0 if the received message is a valid crash data.
*/
int formatMessageToProtocol(String message, String *pointer_protocolToSendArray)
{
  if (message.indexOf(SPEED_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[0] = message;
  }
  else if (message.indexOf(SIDE_HIT_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[1] = message;
  }

  else if (message.indexOf(IMPACT_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[2] = message;
  }

  else if (message.indexOf(DIST_DRIVEN_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[3] = message;
  }

  else if (message.indexOf(ORIENTATION_PROTOCOL_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[4] = (String)ORIENTATION_PROTOCOL_SEND +
                                     (String)(currentYPR[0]) + MULTI_VALUE_SEPARATOR +
                                     (String)(currentYPR[1]) + MULTI_VALUE_SEPARATOR +
                                     (String)(currentYPR[2]);
  }
}

int checkForValidRP6Message(String message)
{
  for (int i = 0; i < nrStringIn_arrayWithRP6Protcols; i++)
  {
    if (message.indexOf(arrayWithRP6Protocol_receive[i]) > -1)
    {
      // Message is a protocol.
      return 1;
    }
    else if (message.indexOf(GENERAL_NACK) > -1)
    {
      // Message is a NACK
      return -1;
    }
  }

  //Message is not a protocol.
  return 0;
}

/*
   Return: 0 if the messageToCheckFor was received.
          -1 if to many times NACK was received or it took to long to receive a response.
*/
int timeoutHandlerWemosToRP6(String messageToSend, String messageToCheckFor)
{
  int nackCounter = 0;
  int timeoutTimer = millis();

  Serial.println(messageToSend);

  while ((millis() - timeoutTimer) <= maxResponseTimeout && nackCounter <= maxNACKCounter)
  {
    // Listen for a response from the RP6
    receivedEndOfSerialString = getIncommingString(&stringFromSerial);

    if (receivedEndOfSerialString)
    {
      if (stringFromSerial == messageToCheckFor)
      {
        // ACK was reeived.
        return 0;
      }
      else if (stringFromSerial == GENERAL_NACK)
      {
        // NACK was received. Increase the NACK counter and send the message again.
        nackCounter++;
        timeoutTimer = millis();
        Serial.println(messageToSend);
      }
    }
  }

  // It took to long to get a response from the RP6.
  if ((millis() - timeoutTimer) > maxResponseTimeout || nackCounter > maxNACKCounter)
  {
    return -1;
  }
}
