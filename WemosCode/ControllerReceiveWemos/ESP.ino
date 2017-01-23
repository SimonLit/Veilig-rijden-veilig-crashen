WiFiClient client_Controller;
const char* host_Controller = "192.168.1.2";
const int httpPort_Controller = 80;

int getControllerValues(String* controllerToRP6Protocol)
{
  String speedValue = "";
  int valueSeparetor = -1;
  String steerValue = "";

  if (!client_Controller.connect(host_Controller, httpPort_Controller))
  {
    return -1;
  }
  makeProtocolString(CONTROLLER_VALUE_PROTOCOL_REQUEST_SEND);
  client_Controller.print(protocolStringToSend);

  String controllerValuesString = client_Controller.readStringUntil('@');
  if (controllerValuesString.substring(1, 17) == CONTROLLER_VALUE_PROTOCOL_RECEIVE)
  {
    valueSeparetor = controllerValuesString.indexOf(MULTI_VALUE_SEPARATOR);
    steerValue = controllerValuesString.substring(18, valueSeparetor);
    speedValue = controllerValuesString.substring(valueSeparetor + 1);
  }

  makeProtocolStringWith2Value(CONTROLLER_VALUES, speedValue, steerValue);
  *controllerToRP6Protocol = protocolStringToSend;

  client_Controller.stop();
  return 0;
}
