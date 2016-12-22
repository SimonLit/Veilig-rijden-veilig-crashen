bool startReadingSerialMessage = false;
bool startReadingSoftwareMessage = false;
bool startReadingStringMessage = false;
String internalTempMessageSerial = "";
String internalTempMessageSoftwareSerial = "";
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

      if (incommingChar == END_CHARACTER)
      {
        startReadingSerialMessage = false;
        *stringFromSerial = internalTempMessageSerial;
        return true;
      }

      if (startReadingSerialMessage)
      {
        internalTempMessageSerial += incommingChar;
      }

      if (incommingChar == START_CHARACTER)
      {
        startReadingSerialMessage = true;
        internalTempMessageSerial = "";
      }
    }
    return false;
  }
}

bool getIncommingStringFromSoftwareSerial(String* stringFromSerial)
{
  if (softwareSerial.available() > 64)
  {
    softwareSerial.flush();
  }
  else
  {
    if (softwareSerial.available() > 0)
    {
      char incommingChar = softwareSerial.read();

      if (incommingChar == END_CHARACTER)
      {
        startReadingSoftwareMessage = false;
        *stringFromSerial = internalTempMessageSoftwareSerial;
        return true;
      }

      if (startReadingSoftwareMessage)
      {
        internalTempMessageSoftwareSerial += incommingChar;
      }

      if (incommingChar == START_CHARACTER)
      {
        startReadingSoftwareMessage = true;
        internalTempMessageSoftwareSerial = "";
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

    if (readChar == END_CHARACTER)
    {
      startReadingStringMessage = false;
      *formattedMessage = tempFormattedMessage;
      return true;
    }

    if (startReadingStringMessage)
    {
      tempFormattedMessage += message[i];
    }

    if (readChar == START_CHARACTER)
    {
      startReadingStringMessage = true;
      tempFormattedMessage = "";
    }
  }
  return false;
}


