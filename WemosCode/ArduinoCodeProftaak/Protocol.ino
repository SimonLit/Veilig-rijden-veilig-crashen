// ================================================================
// ===            SERIAL COMMUNICATION CRASH PROTOCOL           ===
// ================================================================
#define START_CHARACTER '#'
#define END_CHARACTER '%'
#define VALUE_CHARACTER ':'

#define SPEED_PROTOCOL_SEND_RECEIVE "SPEED:"
#define SIDE_HIT_PROTOCOL_SEND_RECEIVE "SIDE_HIT:"
#define IMPACT_PROTOCOL_SEND_RECEIVE "IMPACT:"
#define DIST_DRIVEN_PROTOCOL_SEND_RECEIVE "DIST_DRIVEN:"
#define ORIENTATION_PROTOCOL_SEND "ORIENTATION_YPR:"
#define ORIENTATION_PROTOCOL_RECEIVE "ORIENTATION"

//=================================================================

/*
   Assing the received crash data values to the corresponding indexes of the array.
*/
void formatMessageToProtocol(String message, String *pointer_protocolToSendArray)
{
  DMPRoutine();
  getYPR();

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
    pointer_protocolToSendArray[4] = (String)START_CHARACTER + (String)ORIENTATION_PROTOCOL_SEND + (String)(ypr[0] * 180 / M_PI) + ',' + (String)(ypr[1] * 180 / M_PI) + ',' + (String)(ypr[2] * 180 / M_PI) + END_CHARACTER;
  }
}

