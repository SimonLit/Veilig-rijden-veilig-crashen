const char* host_sendCrashProtocol = "192.168.1.103";
const int httpPort = 80;

void sendChrashDataOverNetwork(String* CrashDataProtocol, int numberOfCrashDataDataToSend)
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host_sendCrashProtocol, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  /*for(int i = 0; i < numberOfCrashDataDataToSend; i++)
  {
    client.print(String("GET ") + '/'CrashDataProtocol[i]'/' + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
  }*/
  
  if (ledState)
  {
    client.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState = false;
  }
  else if (!ledState)
  {
    client.print(String("GET ") + "/LED=ON/" + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState = true;
  }


  /*unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 3000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }*/

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  /*Serial.println();
  Serial.println("closing connection");*/
}

