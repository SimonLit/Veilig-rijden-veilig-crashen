int conectedToBoardcomputer = 0;

void checkAndAcktOnSerialMessage(void)
{
  bool receivedMessage = getIncommingString(&stringFromSerial);
  if (receivedMessage)
  {
    if (stringFromSerial.indexOf(SEND_DATA_TO_BOARDCOMPUTER_INDICATOR) > -1)
    {
      int connectedToBoardcomputer = connectToBoardcomputer();
      if (connectedToBoardcomputer == 1)
      {
        sendCrashData(stringFromSerial, 5);
      }
    }
    else if (stringFromSerial == RP6_STARTED_PROGRAM)
    {
      RP6State = STARTED_PROGRAM;
      int connectedToBoardcomputer = connectToBoardcomputer();
      if (connectedToBoardcomputer == 1)
      {
        //Serial.println("Going to send RP6 status");
        sendRP6StatusToBoardcomputer();
      }
      conectedToBoardcomputer = 0;
    }
    else if (stringFromSerial == RP6_STOPPED_PROGRAM)
    {
      RP6State = STOPPED_PROGRAM;
      int conectedToBoardcomputer = connectToBoardcomputer();
      if (conectedToBoardcomputer == 1)
      {
        sendRP6StatusToBoardcomputer();
      }
      conectedToBoardcomputer = 0;
    }
  }
}

