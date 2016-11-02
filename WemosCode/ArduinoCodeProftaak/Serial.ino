bool startReading = false;
String tempMessage = "";

void getIncommingString(void)
{
  if (Serial.available() > 0)
  {
    char incommingChar = Serial.read();
    
    if (incommingChar == '%')
    {
      startReading = false;
      Serial.println(tempMessage);
    }

    if (startReading)
    {
      tempMessage += incommingChar;
    }

    if (incommingChar == '#')
    {
      startReading = true;
      tempMessage = "";
    }
  }
}

