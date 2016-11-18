const char* host_sendCrashProtocol = "192.168.1.100";
const int httpPort = 80;

const char* host_Wemos2 = "192.168.1.102";
const int httpPort_Wemos2 = 90;

void changeLedState()/*String* CrashDataProtocol, int numberOfCrashDataDataToSend*/
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client1;
  if (!client1.connect(host_sendCrashProtocol, httpPort)) {
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
    client1.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState = false;
    Serial.println("led OFF");
  }
  else if (!ledState)
  {
    client1.print(String("GET ") + "/LED=ON/" + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState = true;
    Serial.println("led ON");

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
  while (client1.available()) {
    String line = client1.readStringUntil('\r');
    Serial.print(line);
  }


  
  WiFiClient client2;
  if (!client2.connect(host_Wemos2, httpPort_Wemos2)) {
    Serial.println("connection failed");
    return;
  }

  /*for(int i = 0; i < numberOfCrashDataDataToSend; i++)
    {
    client.print(String("GET ") + '/'CrashDataProtocol[i]'/' + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    }*/

  if (ledState1)
  {
    client2.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
                 "Host: " + host_Wemos2 + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState1 = false;
    Serial.println("led OFF");
  }
  else if (!ledState1)
  {
    client2.print(String("GET ") + "/LED=ON/" + " HTTP/1.1\r\n" +
                 "Host: " + host_Wemos2 + "\r\n" +
                 "Connection: close\r\n\r\n");
    ledState1 = true;
    Serial.println("led ON");

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
  while (client2.available()) {
    String line = client2.readStringUntil('\r');
    Serial.print(line);
  }
  /*Serial.println();
    Serial.println("closing connection");*/
}

