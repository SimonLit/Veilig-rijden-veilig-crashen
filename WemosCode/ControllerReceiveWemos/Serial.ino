bool startReadingSerialMessage = false;
bool startReadingStringMessage = false;
String internalTempMessage = "";
String tempFormattedMessage = "";

bool getIncommingString(String* stringFromSerial)
{

  if (Serial.available() > 0)
  {
    char incommingChar = Serial.read();

    if (incommingChar == END_CHARACTER)
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

    if (incommingChar == START_CHARACTER)
    {
      startReadingSerialMessage = true;
      internalTempMessage = "";
    }
  }
  return false;
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


