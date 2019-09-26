/*********Functions for Setup ************/
void declarePins()
{
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);
  pinMode(ROBOSAIL_PIN_WIND, INPUT);

  // attach the servos to the proper pins
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}


/*********Functions to read RC Transmitter/Receiver and Sensors *****/

 void readReceiver()
        // Takes in the PWM signals from the RC Receiver and translates
        // translates them to the servo positions in degrees.
 {
  // pulseIn returns the width of the command pulse in microseconds.
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);

  // Calculate the commanded positions in degrees.
  rudderPosition = map(rudderPulseWidth,
                      ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH,-50, 50);
  sailPosition = map(sailPulseWidth,
                    ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH, 0, 90);
 }

 void readWind()
        // Takes in the PWM signals from the WindSensor and translate
        // it to the windvane position in degrees.
 {
  // Read values from the WindSensor
  windPulseWidth = pulseIn(ROBOSAIL_PIN_WIND, HIGH);
  // Convert the wind angle to degrees from PWM values.  Range -180 to +180
  // Note that the the low value of the angle corresponds to the high value of the sensor
  windAngle = map(windPulseWidth,
                  ROBOSAIL_WIND_SENSOR_LOW, ROBOSAIL_WIND_SENSOR_HIGH, 180, -180);
  windAngle = constrain(windAngle, -180, 180);
 }
/************Functions to drive Sail and Rudder servos ****************/
 // This code takes in the desired postions for the servos in degrees (as
 // defined in RoboSail) then calculates appropriate values for the servo commands,
 // making sure not to send the servos to impossible positions, which could
 // damage the servo motors.
 // The Rudder servo motor ranges from 0 to 180 with 90 deg in the center
 // The Sailwinch servo is at ~55 deg when full-in, which we think of as 0 deg,
 // and ~125 deg when full out, which we think of as 90 deg

void driveRudderServo(int rudderPos)
{
  if ((rudderPos >= -50) && (rudderPos <= 50))
  {
    // calculate the commanded positions into servo angles on the Robosail boat
    // the Rudder servo motor ranges from 0 to 180 with 90 deg in the center
    rudderServoOut = map(rudderPos,-90, 90, 0, 180);
    rudderServo.write(rudderServoOut);
  }
  else
    {
    Serial.print("ERROR - rudder position out of range: ");
    Serial.println(rudderPos);
    }
}

void driveSailServo(int sailPos)
{
  // calculate the commanded positions into servo angles on the Robosail boat
  // the Sailwinch servo is at ~ 55 deg when full-in, which we think of as 0 deg,
  //  and ~125 deg when full out, which we thnk of as 90 deg
  if ((sailPos >= 0) && (sailPos <= 90))  // the command in degrees is valid
  {
  sailServoOut = map(sailPos, 0, 90, ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH);
  sailServo.write(sailServoOut);
  }
  else
  {
    Serial.print("ERROR - sail position out of range: ");
    Serial.println(sailPos);
    }
}
/****************************************************/
// Function to Print out all values for debug.
void printToMonitor()
{
  Serial.print("Wind Angle: ");
  Serial.print(windAngle);

  Serial.print("     Sail, RC: ");
  Serial.print(sailPulseWidth);
  Serial.print("  desired angle: ");
  Serial.print(sailPosition);
  Serial.print("  to servo: ");
  Serial.print(sailServoOut);

  Serial.print("  Rudder, RC: ");
  Serial.print(rudderPulseWidth);
  Serial.print("  desired angle: ");
  Serial.print(rudderPosition);
  Serial.print("  to servo: ");
  Serial.println(rudderServoOut);
}
