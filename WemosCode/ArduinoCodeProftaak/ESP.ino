WiFiClient client_Controller;
const char* host_Controller = "10.10.0.28";
const int httpPort_Controller = 80;

WiFiClient client_sendCrashData;
const char* host_sendCrashData = "192.168.1.100";
const int httpPort_sendCrashData = 5500;

/*
   Request the speed value from the controller.
   Then send the received protocol to the RP6.
*/
void getControllerValues(String* speedProtocol, String* steerProtocol)
{
  if (!client_Controller.connect(host_Controller, httpPort_Controller))
  {
    Serial.println("client_Controller failed");
    return;
  }

  client_Controller.print("/GetControllerValues\r\n");

  // String controllerValuesString = "";
  while (client_Controller.available()) {
    String controllerValuesString = client_Controller.readString();

    String speedValue = "";
    int valueSeparetor = -1;
    String steerValue = "";

    if (getIncommingStringFromMessage(controllerValuesString, &controllerValuesString, controllerValuesString.length()))
    {
      if (controllerValuesString.substring(0, 17) == "ControllerValues:")
      {
        valueSeparetor = controllerValuesString.indexOf(';');
        steerValue = controllerValuesString.substring(17, valueSeparetor);
        speedValue = controllerValuesString.substring(valueSeparetor + 1);
      }
    }
    *speedProtocol = "#SPEED:" + speedValue + '%';
    *steerProtocol = "#X:" + steerValue + '%';
  }

  client_Controller.stop();
}

/*
   Send all items from the crash data to the boardComputer.
*/
void sendCrashData(String CrashDataProtocol[], int numberOfCrashDataDataToSend)
{
  if (!client_sendCrashData.connect(host_sendCrashData, httpPort_sendCrashData)) {
    Serial.println("client_sendCrashData failed");
    return;
  }

  client_sendCrashData.print(CrashDataProtocol[0] + '|' +
                             CrashDataProtocol[1] + '|' +
                             CrashDataProtocol[2] + '|' +
                             CrashDataProtocol[3] + '|' +
                             CrashDataProtocol[4]);
  //String charDataResponse = "";
  while (client_sendCrashData.available()) {
    String charDataResponse = client_sendCrashData.readString();
  }
  client_sendCrashData.stop();
}
