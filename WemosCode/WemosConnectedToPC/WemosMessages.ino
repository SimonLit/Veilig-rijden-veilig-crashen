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
  //Serial.println(request);
  client.flush();
  if (request.indexOf("/GetX") != -1)
  {
    client.print("#X:");
    client.print(xAxis);
    client.println("%");
  }
  if (request.indexOf("/GetSpeed") != -1)
  {
    client.print("#SPEED:");
    client.print(velocity);
    client.println("%");
  }
  request = "";
}
