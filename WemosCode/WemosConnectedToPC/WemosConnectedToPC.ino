enum COMMUNICATIONSTATE
{
  IDLE,
  RECEIVEMESSAGE
};

#include <ESP8266WiFi.h>

bool reading = false;
String inputString = "";
int xAxis;
int velocity;
const int baudRate = 9600;

const char* ssid = "Project";
const char* password = "123456780";

bool wifiConnected = false;
bool serialConnected = false;
bool waitingForACK = false;

WiFiServer server(80);

const long interval = 100;
unsigned long previousMillis = 0;
int failCounterWifi = 0;
int failCounterSerial = 0;

COMMUNICATIONSTATE communicationState = IDLE;

void setup()
{
  Serial.begin(baudRate);

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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  /*switch (communicationState)
  {
    case IDLE:
      Idle();
      break;
    case RECEIVEMESSAGE:
      ReceiveMessageFromWemos();
      ReadPCMessages();
      break;
  }*/
  ReceiveMessageFromWemos();
  ReadPCMessages();
  FailCounter();
}
