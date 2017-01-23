void ReadPCMessages()
{
  if (Serial.available() > 0)
  {
    char inputByte = Serial.read();
    if (inputByte == '#')
    {
      reading = true;
      inputString = "";
    }
    else if (inputByte == '%')
    {
      reading = false;
      if (inputString.startsWith("X:"))
      {
        xAxis = inputString.substring(2).toInt();
        Serial.println("#ACK%");
        failCounterSerial = 0;
      }
      else if (inputString.startsWith("SPEED:"))
      {
        velocity = inputString.substring(6).toInt();
        Serial.println("#ACK%");
        failCounterSerial = 0;
      }
      else if (inputString == "CHECK_HEARTBEAT")
      {
        Serial.println("#CONFIRM_HEARTBEAT%");
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
