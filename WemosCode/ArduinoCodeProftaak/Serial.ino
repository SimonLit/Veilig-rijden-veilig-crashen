bool startReadingSerialMessage = false;
bool startReadingStringMessage = false;
String internalTempMessage = "";
String tempFormattedMessage = "";

bool getIncommingString(String* stringFromSerial)
{
  if (Serial.available() > 64)
  {
    Serial.flush();
  }
  else
  {
    if (Serial.available() > 0)
    {
      char incommingChar = Serial.read();

      if (incommingChar == '%')
      {
        startReadingSerialMessage = false;
        *stringFromSerial = internalTempMessage;
        //Serial.println(internalTempMessage);
        return true;
      }

      if (startReadingSerialMessage)
      {
        internalTempMessage += incommingChar;
      }

      if (incommingChar == '#')
      {
        startReadingSerialMessage = true;
        internalTempMessage = "";
      }
    }
    return false;
  }
}

bool getIncommingStringFromMessage(String message, String* formattedMessage, int messageLength)
{
  for (int i = 0; i < messageLength; i++)
  {
    char readChar = (char)message[i];

    if (readChar == '%')
    {
      startReadingStringMessage = false;
      *formattedMessage = tempFormattedMessage;
      return true;
    }

    if (startReadingStringMessage)
    {
      tempFormattedMessage += message[i];
    }

    if (readChar == (char)'#')
    {
      startReadingStringMessage = true;
      tempFormattedMessage = "";
    }
  }
  return false;
}


