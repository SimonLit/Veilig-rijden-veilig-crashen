enum COMMUNICATIONSTATE
{
  IDLE,
  RECEIVEMESSAGE,
};

#include <ESP8266WiFi.h>

const int baudRate = 9600;

const char beginMessageMarker = '#';
const char endMessageMarker = '%';

const char* ssid = "Project";
const char* password = "123456780";

WiFiServer server(80);

int failCounterHB = 0;
int failCounterWifi = 0;

int xAxis;
int velocity;

COMMUNICATIONSTATE communicationState = IDLE;

bool reading = false;
String inputString = "";
unsigned long previousMillisFailHb = 0;
unsigned long failHbInterval = 150;
unsigned long previousMillisFail = 0;
unsigned long failInterval = 1000;

bool wifiConnected = false;
bool serialConnected = false;

void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:
  switch (communicationState)
  {
    case IDLE:
      Idle();
      break;
    case RECEIVEMESSAGE:
      ReadPCMessages();
      ReceiveMessageFromWemos();
      break;
  }
}
