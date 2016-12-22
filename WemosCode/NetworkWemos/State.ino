void checkAndAcktOnSerialMessage(void)
{
  bool receivedMessage = getIncommingString(&stringFromSerial);
  if (receivedMessage)
  {
    Serial.print("Received message: ");
    Serial.println(stringFromSerial);
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
      if (conectedToBoardcomputer);
      {
         sendCrashData(stringFromSerial, 5);
      }
    }
    else if (stringFromSerial == RP6_STARTED_PROGRAM)
    {
      RP6State = STARTED_PROGRAM;
      sendRP6StatusToBoardcomputer();
    }
    else if (stringFromSerial == RP6_STOPPED_PROGRAM)
    {
      RP6State = STOPPED_PROGRAM;
      sendRP6StatusToBoardcomputer();
    }
  }
}

