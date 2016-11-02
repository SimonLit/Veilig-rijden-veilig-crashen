const char* host = "192.168.1.107";
const int httpPort = 80;

void espTestWithLed(bool LedState)
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  if (LedState)
  {
      client.print(String("GET ") + "/LED=ON/" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  }
  else
  {
      client.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  }

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

void changeLedState(void)
{
    ledState = !ledState;
    espTestWithLed(ledState);
    Serial.print("ledState: ");
    Serial.println(ledState);
}
