WiFiClient client_Controller;
const char* host_Controller = "192.168.1.109";
const int httpPort_Controller = 80;

WiFiClient client_sendCrashData;
const char* host_sendCrashData = "10.10.0.1";
const int httpPort_sendCrashData = 5000;

/*
   Request the steering value from the controller.
   Then send the received protocol to the RP6.

   The protocol: #X:<-100 t/m 100>%
*/
void getXasController(void)
{
  if (!client_Controller.connect(host_Controller, httpPort_Controller)) {
    Serial.println("connection failed");
    return;
  }

  client_Controller.print(String("GET ") + "/GetX/" + " HTTP/1.1\r\n" +
                          "Host: " + host_Controller + "\r\n" +
                          "Connection: close\r\n\r\n");

  while (client_Controller.available()) {
    String xProtocolString = client_Controller.readStringUntil('\r');
    Serial.println(xProtocolString);
  }
}

/*
   Request the speed value from the controller.
   Then send the received protocol to the RP6.

   The protocol: #SPEED:<-60 t/m 60>%
*/
void getSpeedController(void)
{
  if (!client_Controller.connect(host_Controller, httpPort_Controller)) {
    Serial.println("connection failed");
    return;
  }

  client_Controller.print(String("GET ") + "/GetSpeed/" + " HTTP/1.1\r\n" +
                          "Host: " + host_Controller + "\r\n" +
                          "Connection: close\r\n\r\n");

  while (client_Controller.available()) {
    String speedProtocolString = client_Controller.readStringUntil('\r');
    Serial.println(speedProtocolString);
  }
}

/*
   Send all items from the crash data to the boardComputer.
*/
void sendCrashData(String CrashDataProtocol[], int numberOfCrashDataDataToSend)
{
  if (!client_sendCrashData.connect(host_sendCrashData, httpPort_sendCrashData)) {
    Serial.println("connection failed");
    return;
  }

  for (int i = 0; i < numberOfCrashDataDataToSend; i++)
  {
    client_sendCrashData.print(String("GET ") + '/' + CrashDataProtocol[i] + '/' + " HTTP/1.1\r\n" +
                               "Host: " + host_sendCrashData + "\r\n" +
                               "Connection: close\r\n\r\n");
  }
}
