int nrStringIn_arrayWithRP6Protcols = 7;
String arrayWithRP6Protocol_receive[] = {RP6_STARTED_PROGRAM, RP6_STOPPED_PROGRAM, SPEED_PROTOCOL_SEND_RECEIVE,
                                         SIDE_HIT_PROTOCOL_SEND_RECEIVE, IMPACT_PROTOCOL_SEND_RECEIVE,
                                         DIST_DRIVEN_PROTOCOL_SEND_RECEIVE, ORIENTATION_PROTOCOL_RECEIVE
                                        };

int checkForValidBoardcomputerMessage(String message)
{
  if (message.indexOf(GENERAL_ACK) > -1)
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
