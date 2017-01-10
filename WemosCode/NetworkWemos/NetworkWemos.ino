// ================================================================
// ===                        INCLUDES                          ===
// ================================================================
#include <ESP8266WiFi.h>
String stringFromSerial = "";

// ================================================================
// ===           GENERAL SERIAL COMMUNICATION PROTOCOL          ===
// ================================================================
#define START_CHARACTER '#'
#define END_CHARACTER '@'
#define VALUE_CHARACTER ':'
#define MULTI_VALUE_SEPARATOR ','
#define MULTI_COMMAND_SEPARATOR '|'
// ================================================================
// ===            SERIAL COMMUNICATION RP6 PROTOCOL             ===
// ================================================================
#define CONNECT_TO_DEVICE "CONNECT"
#define CONNECTED_ACK_RECEIVE "CONNECTED"
#define RP6_STARTED_PROGRAM "START_RP6"
#define RP6_STOPPED_PROGRAM "STOP_RP6"
#define SPEED_PROTOCOL_SEND_RECEIVE "SPEED"
#define SIDE_HIT_PROTOCOL_SEND_RECEIVE "SIDE_HIT"
#define CONTROLLER_DISCONNECTED "CTRL_DISCONNECTED"
#define CONTROLLER_CONNECTED "CTRL_CONNECTED"
#define IMPACT_PROTOCOL_SEND_RECEIVE "IMPACT"
#define DIST_DRIVEN_PROTOCOL_SEND_RECEIVE "DIST_DRIVEN"
#define ORIENTATION_PROTOCOL_SEND "ORIENTATION_YPR"
#define ORIENTATION_PROTOCOL_RECEIVE "ORIENTATION"
#define HEARTBEAT_RP6 "HEARTBEAT"
#define CONTROLLER_VALUES "CONTROLLER_VALUES"
//=================================================================
// ===         WIFI COMMUNICATION CONTROLLER PROTOCOL           ===
// ================================================================
#define CONTROLLER_VALUE_PROTOCOL_RECEIVE "ControllerValues"
#define CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND "GetControllerValues"
//=================================================================
// ===        WIFI COMMUNICATION BOARDCOMPUTER PROTOCOL         ===
// ================================================================
#define SEND_DATA_TO_BOARDCOMPUTER_INDICATOR "DAT"
//=================================================================

#define GENERAL_ACK "ACK"
#define GENERAL_NACK "NACK"
#define RP6_NAME "RP6"
#define WEMOS_NAME "CAR"
#define BOARDCOMPUTER_NAME "BOARDCOMPUTER"
//=================================================================

String protocolStringToSend = "";

int maxNACKCounter = 3;
int maxResponseTimeout = 2000;
bool receivedEndOfSerialString = false;

typedef enum
{
  RP6_CONNECTED,
  RP6_DISCONNECTED
} connectionRP6;

typedef enum
{
  STARTED_PROGRAM,
  STOPPED_PROGRAM
} stateRP6;
char* RP6States[] = {RP6_STARTED_PROGRAM, RP6_STOPPED_PROGRAM};

typedef enum
{
  CTRL_CONNECTED,
  CTRL_DISCONNECTED
} connectionController;
char* ctrlConnectionStates[] = {RP6_STARTED_PROGRAM, RP6_STOPPED_PROGRAM};

connectionRP6 WemosToRP6Connection = RP6_DISCONNECTED;
stateRP6 RP6State = STOPPED_PROGRAM;
connectionController WemosToCTRLConnection = CTRL_DISCONNECTED;

// ================================================================
// ===                      WIFI VARIABLES                      ===
// ================================================================
//const char* ssid = "Project";
//const char* password = "123456780";
//const char* ssid = "eversveraa";
//const char* password = "qwerty69";
const char* ssid = "HotSpotBoardComputer";
const char* password = "1234567890";

String controllerToRP6Protocol = "";

long currentMillis = 0;

// ================================================================
// ===                    SETUP FOR ESP                         ===
// ================================================================
void setup() {
  Serial.begin(38400);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // If the router isn't available for use comment this while loop.
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// ================================================================
// ===                        MAIN LOOP                         ===
// ================================================================
void loop()
{
  checkAndAcktOnSerialMessage();
}
