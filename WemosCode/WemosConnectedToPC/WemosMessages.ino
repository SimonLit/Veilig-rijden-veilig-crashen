void ReceiveMessageFromWemos(void)
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  //Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  //Serial.println(request);
  //client.flush();
  if (request.indexOf("GetControllerValues") != -1)
  {
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
