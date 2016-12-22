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
      if (conectedToBoardcomputer);
      {
        sendCrashData(protocolToSendArray, 5);
      }
      else
      {
        Serial.println("canNotConnectToBoardcomputer"
      }
    }
  }
}

