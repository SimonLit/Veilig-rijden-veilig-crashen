void ReadPCMessages()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisFailHb >= failHbInterval)
  {
    previousMillisFailHb = currentMillis;
    failCounterHB++;
    if (failCounterHB >= 5)
    {
      serialConnected = false;
      communicationState = IDLE;
    }
  }
  if (Serial.available() > 0)
  {
    char inputByte = Serial.read();
    if (inputByte == beginMessageMarker)
    {
      reading = true;
      inputString = "";
    }
    else if (inputByte == endMessageMarker)
    {
      reading = false;
      serialConnected = true;
      if (inputString.startsWith("X:"))
      {
        xAxis = inputString.substring(2).toInt();
        Serial.println("#ACK%");
      }
      else if (inputString.startsWith("SPEED:"))
      {
        velocity = inputString.substring(6).toInt();
        Serial.println("#ACK%");
      }
      else if (inputString == "CHECK_HEARTBEAT")
      {
        Serial.println("#CONFIRM_HEARTBEAT%");
        failCounterHB = 0;
      }
      else
      {
        Serial.println("#NACK%");
      }
      inputString = "";
    }
    else if (reading)
    {
      inputString += inputByte;
    }
  }
}
