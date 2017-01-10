int conectedToBoardcomputer = 0;

void checkAndAcktOnSerialMessage(void)
{
  bool receivedMessage = getIncommingString(&stringFromSerial);
  if (receivedMessage)
  {
    if (stringFromSerial == CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND)
    {
      String controllerValues = "";
      int controllerReceiveSate = getControllerValues(&controllerValues);
      if (controllerValues.indexOf(CONTROLLER_VALUES) > -1)
      {
        Serial.println(controllerValues);
      }
      else
      {
        makeProtocolString("ControllerDisconnected");
        Serial.println(protocolStringToSend);
      }
    }
    else if (stringFromSerial.indexOf(SEND_DATA_TO_BOARDCOMPUTER_INDICATOR) > -1)
    {
      int conectedToBoardcomputer = connectToBoardcomputer();
      if (conectedToBoardcomputer)
      {
        sendCrashData(stringFromSerial, 5);
      }
    }
    else if (stringFromSerial == RP6_STARTED_PROGRAM)
    {
      RP6State = STARTED_PROGRAM;
      conectedToBoardcomputer = connectToBoardcomputer();
      if (conectedToBoardcomputer == 1)
      {
        Serial.println("Going to send RP6 status");
        sendRP6StatusToBoardcomputer();
      }
      conectedToBoardcomputer = 0;
    }
    else if (stringFromSerial == RP6_STOPPED_PROGRAM)
    {
      RP6State = STOPPED_PROGRAM;
      conectedToBoardcomputer = connectToBoardcomputer();
      if (conectedToBoardcomputer == 1)
      {
        Serial.println("Going to send RP6 status");
        sendRP6StatusToBoardcomputer();
      }
      conectedToBoardcomputer = 0;
    }
  }
}

