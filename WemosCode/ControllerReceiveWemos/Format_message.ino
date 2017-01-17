/*
   Format a protocol string.
   The protocol is stored in the protocolStringToSend variable.
*/
void makeProtocolString(String command)
{
  protocolStringToSend = "";
  protocolStringToSend = START_CHARACTER + command + END_CHARACTER;
}

/*
   Format a protocol string with value.
   The protocol is stored in the protocolStringToSend variable.
*/
void makeProtocolStringWithValue(String command, String value)
{
  protocolStringToSend = "";
  protocolStringToSend = START_CHARACTER + command + VALUE_CHARACTER + value + END_CHARACTER;
}

/*
 * 
 */
void makeProtocolStringWith2Value(String command, String value1, String value2)
{
  protocolStringToSend = "";
  protocolStringToSend = START_CHARACTER + command + VALUE_CHARACTER + value1 + MULTI_VALUE_SEPARATOR + value2 + END_CHARACTER;
}
