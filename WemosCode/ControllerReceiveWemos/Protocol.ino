int checkForValidControllerMessage(String message)
{
  if (message.indexOf(CONTROLLER_VALUE_PROTOCOL_RECEIVE) > -1)
  {
    //Message is a protocol.
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
