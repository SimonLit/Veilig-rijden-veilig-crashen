void Idle()
{
  
}

void FailCounter()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    failCounterWifi++;
    failCounterSerial++;
  }
  if (failCounterWifi >= 35)
  {
    failCounterWifi = 0;
    wifiConnected = false;
    Serial.println("#WIFI_DISCONNECTED%");
    waitingForACK = true;
  }
  if (failCounterSerial >= 5)
  {
    failCounterSerial = 0;
    serialConnected = false;
    xAxis = 0;
    velocity = 0;
  }
}

