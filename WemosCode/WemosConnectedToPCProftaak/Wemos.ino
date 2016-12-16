void ReceiveMessageFromWemos(void)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisFail >= failInterval)
  {
    previousMillisFail = currentMillis;
    failCounterWifi++;
    if (failCounterWifi >= 4)
    {
      wifiConnected = false;
      communicationState = IDLE;
    }
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  //client.flush();
  if (request.indexOf("GetControllerValues") != -1)
  {
    wifiConnected = true;
    Serial.println(velocity);
    // Send in this way: "#ControllerValues:<xAxis-100To100>;<velocity-150To150>%"
    client.print("#ControllerValues:");
    client.print(xAxis);
    client.print(",");
    client.print(velocity);
    client.println("@");
    failCounterWifi = 0;
  }
  request = "";
}
