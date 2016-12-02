// ================================================================
// ===           GENERAL SERIAL COMMUNICATION PROTOCOL          ===
// ================================================================
#define START_CHARACTER '#'
#define END_CHARACTER '%'
#define VALUE_CHARACTER ':'
#define MULTI_VALUE_SEPARATOR ';'
// ================================================================
// ===            SERIAL COMMUNICATION RP6 PROTOCOL             ===
// ================================================================
#define RP6_STARTED_PROGRAM "STARTED_PROGRAM"
#define RP6_STOPPED_PROGRAM "STOPPED_PROGRAM"
#define SPEED_PROTOCOL_SEND_RECEIVE "SPEED:"
#define SIDE_HIT_PROTOCOL_SEND_RECEIVE "SIDE_HIT:"
#define IMPACT_PROTOCOL_SEND_RECEIVE "IMPACT:"
#define DIST_DRIVEN_PROTOCOL_SEND_RECEIVE "DIST_DRIVEN:"
#define ORIENTATION_PROTOCOL_SEND "ORIENTATION_YPR:"
#define ORIENTATION_PROTOCOL_RECEIVE "ORIENTATION"
// ================================================================
// ===         SERIAL COMMUNICATION CONTROLLER PROTOCOL         ===
// ================================================================
#define CONTROLLER_SPEED_PROTOCOL_SEND "SPEED:"
#define CONTROLLER_STEER_PROTOCOL_SEND "X:"
//=================================================================
// ===         WIFI COMMUNICATION CONTROLLER PROTOCOL           ===
// ================================================================
#define CONTROLLER_VALUE_PROTOCOL_RECEIVE "ControllerValues:"
#define CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND "GetControllerValues"
//=================================================================

//=================================================================
// ===         SERIAL NACK COMMUNICATION PROTOCOL               ===
// ================================================================
#define RP6_RECEIVED_NON_PROTOCOL_STRING "NACK"
#define WEMOS_RECEIVED_NON_PROTOCOL_STRING "NACK"
//=================================================================

int nrStringIn_arrayWithAllProtcols = 10;
String arrayWithAllProtcols[] = {SPEED_PROTOCOL_SEND_RECEIVE, SIDE_HIT_PROTOCOL_SEND_RECEIVE,
                                 IMPACT_PROTOCOL_SEND_RECEIVE, DIST_DRIVEN_PROTOCOL_SEND_RECEIVE,
                                 ORIENTATION_PROTOCOL_SEND, ORIENTATION_PROTOCOL_RECEIVE,
                                 CONTROLLER_SPEED_PROTOCOL_SEND, CONTROLLER_STEER_PROTOCOL_SEND,
                                 CONTROLLER_VALUE_PROTOCOL_RECEIVE, CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND};

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
                                      (String)(currentYPR[2])+ END_CHARACTER;
  }
}

int checkForValidMessage(String message)
{
  for (int i = 0; i < nrStringIn_arrayWithAllProtcols; i++)
  {
    if (message.indexOf(arrayWithAllProtcols[i]) > -1)
    {
      //Message is a protocol.
      return 1;
    }
    else
    {
      //Message is not a protocol.
      return 0;
    }
  }
  // Something went wrong.
  return -1;
}

