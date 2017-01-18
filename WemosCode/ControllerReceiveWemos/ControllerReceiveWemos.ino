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
//=================================================================
// ===         WIFI COMMUNICATION CONTROLLER PROTOCOL           ===
// ================================================================
#define CONTROLLER_VALUES "CONTROLLER_VALUES"
#define CONTROLLER_VALUE_PROTOCOL_RECEIVE "ControllerValues"
#define CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND "GetControllerValues"
#define GENERAL_NACK "NACK"

String protocolStringToSend = "";

// ================================================================
// ===                      WIFI VARIABLES                      ===
// ================================================================
//const char* ssid = "Project";
//const char* password = "123456780";
const char* ssid = "eversveraa";
const char* password = "qwerty69";
//const char* ssid = "HotSpotBoardComputer";
//const char* password = "1234567890";

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

  // config static IP
  /*IPAddress ip(10, 10, 0, 3); // where xx is the desired IP Address
  IPAddress gateway(10, 10, 0, 1); // set gateway to match your network
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);*/

  // If the router isn't available for use comment this while loop.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("IP gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("subnet: ");
  Serial.println(WiFi.subnetMask());
}

// ================================================================
// ===                        MAIN LOOP                         ===
// ================================================================
void loop()
{
  checkAndAcktOnSerialMessage();
}
