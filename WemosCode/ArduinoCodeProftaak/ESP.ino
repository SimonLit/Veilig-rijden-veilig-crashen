WiFiClient client1;
const char* host_Wemos1 = "192.168.1.101";
const int httpPort_Wemos1 = 80;

WiFiClient client2;
const char* host_Wemos2 = "10.10.0.1";
const int httpPort_Wemos2 = 5000;

void initControllerHost(void)
{
  // Use WiFiClient class to create TCP connections
  /*if (!client1.connect(host_Wemos1, httpPort_Wemos1)) {
    Serial.println("connection failed");
    return;
    }*/

  if (!client2.connect(host_Wemos2, httpPort_Wemos2)) {
    Serial.println("connection failed");
    return;
  }
}

void changeLedState()/*String* CrashDataProtocol, int numberOfCrashDataDataToSend*/
{
  /*if (!client1.connect(host_Wemos1, httpPort_Wemos1)) {
    Serial.println("connection failed");
    return;
    }

    if (!client2.connect(host_Wemos2, httpPort_Wemos2)) {
    Serial.println("connection failed");
    return;
    }

    client2.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
                  "Host: " + host_Wemos2 + "\r\n" +
                  "Connection: close\r\n\r\n");

    /*for(int i = 0; i < numberOfCrashDataDataToSend; i++)
    {
    client.print(String("GET ") + '/'CrashDataProtocol[i]'/' + " HTTP/1.1\r\n" +
                 "Host: " + host_sendCrashProtocol + "\r\n" +
                 "Connection: close\r\n\r\n");
    }*/

  if (ledState)
  {
    client1.print(String("GET ") + "/LED=OFF/" + " HTTP/1.1\r\n" +
                  "Host: " + host_Wemos1 + "\r\n" +
                  "Connection: close\r\n\r\n");
    ledState = false;
    Serial.println("led OFF");
  }
  else if (!ledState)
  {
    client1.print(String("GET ") + "/LED=ON/" + " HTTP/1.1\r\n" +
                  "Host: " + host_Wemos1 + "\r\n" +
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
                  "Host: " + host_Wemos2 + "\r\n");
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

void getXasController(void)
{
  if (!client1.connect(host_Wemos1, httpPort_Wemos1)) {
    Serial.println("connection failed");
    return;
  }

  client1.print(String("GET ") + "/GetX/" + " HTTP/1.1\r\n" +
                "Host: " + host_Wemos1 + "\r\n" +
                "Connection: close\r\n\r\n");

  while (client1.available()) {
    String xProtocolString = client1.readStringUntil('\r');
    Serial.println(xProtocolString);
    /*for (int i = 0; i < xProtocolString.length(); i++)
    {
      Serial.write(xProtocolString[i]);
      Serial.println();
      Serial.print(xProtocolString[i]);
      //swSer.write(xProtocolString[i]);
    }*/
  }
}

void getSpeedController(void)
{
  if (!client1.connect(host_Wemos1, httpPort_Wemos1)) {
    Serial.println("connection failed");
    return;
  }

  client1.print(String("GET ") + "/GetSpeed/" + " HTTP/1.1\r\n" +
                "Host: " + host_Wemos1 + "\r\n" +
                "Connection: close\r\n\r\n");

  while (client1.available()) {
    String speedProtocolString = client1.readStringUntil('\r');
    Serial.println(speedProtocolString);
    /*for (int i = 0; i < speedProtocolString.length(); i++)
    {
      Serial.write(speedProtocolString[i]);
      Serial.println();
      Serial.print(speedProtocolString[i]);
      //swSer.write(speedProtocolString[i]);
    }*/
  }
}

