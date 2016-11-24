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
      }
      else if (inputString.startsWith("SPEED:"))
      {
        velocity = inputString.substring(6).toInt();
      }
      inputString = "";
    }
    else if (reading)
    {
      inputString += inputByte;
    }
  }
}
