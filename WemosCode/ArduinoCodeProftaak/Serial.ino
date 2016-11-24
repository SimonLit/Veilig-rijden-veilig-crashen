bool startReading = false;
String internalTempMessage = "";

bool getIncommingString(void)
{
  if (Serial.available() > 0)
  {
    char incommingChar = Serial.read();
    
    if (incommingChar == '%')
    {
      startReading = false;
      tempMessage = internalTempMessage;
      Serial.println(tempMessage);
      return true;
    }

    if (startReading)
    {
      internalTempMessage += incommingChar;
    }

    if (incommingChar == '#')
    {
      startReading = true;
      internalTempMessage = "";
    }
  }
  return false;
}


