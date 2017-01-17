#ifndef PROTOCOL_DEFINES_H
#define PROTOCOL_DEFINES_H

#include <stdint.h>

// ================================================================
// ===           GENERAL SERIAL COMMUNICATION PROTOCOL          ===
// ================================================================
#define START_CHARACTER "#"
#define END_CHARACTER "@"
#define VALUE_CHARACTER ":"
#define MULTI_VALUE_SEPARATOR ","
// ================================================================
// ===            SERIAL COMMUNICATION RP6 PROTOCOL             ===
// ================================================================
#define CONNECT_TO_DEVICE_RECEIVE "CONNECT"
#define CONNECTED_ACK "CONNECTED"
#define RP6_STARTED_PROGRAM "START_RP6"
#define RP6_STOPPED_PROGRAM "STOP_RP6"
#define SPEED_PROTOCOL_SEND "SPEED"
#define SIDE_HIT_PROTOCOL_SEND_RECEIVE "SIDE_HIT"
#define IMPACT_PROTOCOL_SEND_RECEIVE "IMPACT"
#define DIST_DRIVEN_PROTOCOL_SEND_RECEIVE "DIST_DRIVEN"
#define ORIENTATION_PROTOCOL_SEND "ORIENTATION_YPR"
#define ORIENTATION_PROTOCOL_RECEIVE "ORIENTATION"
#define HEARTBEAT_RP6 "HEARTBEAT"
#define CONTROLLER_VALUES "CONTROLLER_VALUES"
// ================================================================
// ===               GENERAL COMMUNICATION PROTOCOL             ===
// ================================================================
#define GENERAL_ACK "ACK"
#define GENERAL_NACK "NACK"
#define RP6_NAME "RP6"
#define WEMOS_NAME "CAR"
// ================================================================

#define MAX_COMMAND_LENGTH 20
#define MAX_VALUE_LENGTH 20
#define MAX_NACK_COUNTER 3
#define MAX_HEARTBEAT_TIMEOUT 4000 // Since every 1 second a heartbeat is supposed
								   // to be received there can be a 200 ms delay before
								   // deciding the connection to the wemos is broken.

typedef enum
{
	DISCONNECTED,
	CONNECTED
} connection;

typedef enum
{
	STARTED_PROGRAM,
	STOPPED_PROGRAM
} stateRP6;

extern uint16_t lastHeartbeatReceived;
 
#endif