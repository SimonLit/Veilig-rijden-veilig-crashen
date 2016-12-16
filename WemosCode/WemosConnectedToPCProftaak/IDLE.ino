void Idle()
{
  if (!wifiConnected)
  {
    Serial.println("#NO_WIFI_CONNECTION%");
  }
  if (!serialConnected)
  {
    xAxis = 0;
    velocity = 0;
  }
  communicationState = RECEIVEMESSAGE;
}

