int8_t yawOffsetValue = 0;
int8_t pitchOffsetValue = 0;
int8_t rollOffsetValue = 0;

long lastMillisForCalibration = 0;
int calibrationWaitTime = 1000;

void DMPRoutine(void)
{
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    // other program behavior stuff here
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
  }

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024)
  {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    //while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

  }
}

void getYPR(void)
{
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
}

/*
   Assignt the YPR values from the DMP, minus the YPR offsets to the YPR int array.
*/
void updateCurrentOrientation(int* YPRArrayToUpdate)
{
  getYPR();
  YPRArrayToUpdate[0] = (ypr[0] * 180 / M_PI) - yawOffsetValue;
  YPRArrayToUpdate[1] = (ypr[1] * 180 / M_PI) - pitchOffsetValue;
  YPRArrayToUpdate[2] = (ypr[2] * 180 / M_PI) - rollOffsetValue;
}

// THIS CAN BE DELETED WHEN THE PROGRAM WORKS.
void prinYawPitchRoll(int* YPRArrayToUpdate)
{
  Serial.print("ypr\t");
  Serial.print(YPRArrayToUpdate[0]);
  Serial.print("\t");
  Serial.print(YPRArrayToUpdate[1]);
  Serial.print("\t");
  Serial.println(YPRArrayToUpdate[2]);

  Serial.println();
}

/*
   Check if the values of the MPU are stabalized or not.

   Return: true if the MPU is stable.
           false if the MPU isn't stable yet.
*/
bool getMPUIsStabilized(void)
{
  int yaw1 = 0;
  int pitch1 = 0;
  int roll1 = 0;

  int yaw2 = 0;
  int pitch2 = 0;
  int roll2 = 0;

  int errorMargin = 5;

  DMPRoutine();

  if ((millis() -  lastMillisForCalibration) <  calibrationWaitTime / 3)
  {
    getYPR();
    yaw1 = ypr[0] * 180 / M_PI;
    pitch1 = ypr[1] * 180 / M_PI;
    roll1 = ypr[2] * 180 / M_PI;
  }

  if ((millis() - lastMillisForCalibration) > calibrationWaitTime)
  {
    getYPR();
    yaw2 = ypr[0] * 180 / M_PI;
    pitch2 = ypr[1] * 180 / M_PI;
    roll2 = ypr[2] * 180 / M_PI;

    int yawDifference = yaw1 - yaw2;
    int pitchDifference = pitch1 - pitch2;
    int rollDifference = roll1 - roll2;

    Serial.print("yawDifference");
    Serial.println(yawDifference);
    Serial.print("pitchDifference");
    Serial.println(pitchDifference);
    Serial.print("rollDifference");
    Serial.println(rollDifference);

    if ((yawDifference > -errorMargin && yawDifference <  errorMargin)
        && (pitchDifference > -errorMargin && pitchDifference <  errorMargin)
        && (rollDifference > -errorMargin && rollDifference <  errorMargin))
    {
      return true;
    }
    else
    {
      return false;
    }

    lastMillisForCalibration = millis();
  }
  return false;
}

/*
   Assign the YPR offsets to the current values of the MPU.
*/
void resetYPRValues(void)
{
  DMPRoutine();
  getYPR();
  yawOffsetValue = ypr[0] * 180 / M_PI;
  pitchOffsetValue = ypr[1] * 180 / M_PI;
  rollOffsetValue = ypr[2] * 180 / M_PI;
}

