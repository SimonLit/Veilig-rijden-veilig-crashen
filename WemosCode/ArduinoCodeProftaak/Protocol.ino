int nrStringIn_arrayWithRP6Protcols = 7;
String arrayWithRP6Protocol_receive[] = {RP6_STARTED_PROGRAM, RP6_STOPPED_PROGRAM, SPEED_PROTOCOL_SEND_RECEIVE,
                                         SIDE_HIT_PROTOCOL_SEND_RECEIVE, IMPACT_PROTOCOL_SEND_RECEIVE, 
                                         DIST_DRIVEN_PROTOCOL_SEND_RECEIVE, ORIENTATION_PROTOCOL_RECEIVE};

/*
   Assing the received crash data values to the corresponding indexes of the array.
*/
void formatMessageToProtocol(String message, String *pointer_protocolToSendArray)
{
  if (message.indexOf(SPEED_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[0] = START_CHARACTER + message + END_CHARACTER;
  }
  else if (message.indexOf(SIDE_HIT_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[1] = START_CHARACTER + message + END_CHARACTER;
  }

  else if (message.indexOf(IMPACT_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[2] = START_CHARACTER + message + END_CHARACTER;
  }

  else if (message.indexOf(DIST_DRIVEN_PROTOCOL_SEND_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[3] = START_CHARACTER + message + END_CHARACTER;
  }

  else if (message.indexOf(ORIENTATION_PROTOCOL_RECEIVE) > -1)
  {
    pointer_protocolToSendArray[4] = START_CHARACTER + (String)ORIENTATION_PROTOCOL_SEND +
                                     (String)(currentYPR[0]) + ',' +
                                     (String)(currentYPR[1]) + ',' +
                                     (String)(currentYPR[2]) + END_CHARACTER;
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
    else
    {
      //Message is not a protocol.
      return 0;
    }
  }
}

int checkForValidBoardcomputerMessage(String message)
{
  if (message.indexOf(BOARDCOMPUTER_CONNECT_RESPONSE) > -1 || message.indexOf(GENERAL_ACK) > -1)
  {
    // Message is a protocol.
    return 1;
  }
  else if (message.indexOf(GENERAL_NACK) > -1)
  {
    // Message is a NACK
    return -1;
  }
  else
  {
    //Message is not a protocol.
    return 0;
  }
}

int checkForValidControllerMessage(String message)
{
  if (message.indexOf(CONTROLLER_VALUE_PROTOCOL_RECEIVE) > -1)
  {
    //Message is a protocol.
    return 1;
  }
  else
  {
    //Message is not a protocol.
    return 0;
  }
  // Something went wrong.
  return -1;
}
