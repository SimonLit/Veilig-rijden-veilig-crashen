// ================================================================
// ===               SERIAL COMMUNICATION PROTOCOL              ===
// ================================================================
#define START_CHARACTER '#'
#define END_CHARACTER '%'
#define VALUE_CHARACTER ':'

#define SPEED_PROTOCOL "SPEED:"
#define SIDE_HIT_PROTOCOL "SIDE_HIT:"
#define IMPACT_PROTOCOL "IMPACT:"
#define ORIENTATION_YAW_PROTOCOL "YAW:"
#define ORIENTATION_PITCH_PROTOCOL "PITCH:"
#define ORIENTATION_ROLL_PROTOCOL "ROLL:"

//=================================================================

bool startReading = false;
String tempMessage = "";

void getIncommingString(void)
{
  if (Serial.available() > 0)
  {
    char incommingChar = Serial.read();
    
    if (incommingChar == '%')
    {
      startReading = false;
      Serial.println(tempMessage);
    }

    if (startReading)
    {
      tempMessage += incommingChar;
    }

    if (incommingChar == '#')
    {
      startReading = true;
      tempMessage = "";
    }
  }
}

