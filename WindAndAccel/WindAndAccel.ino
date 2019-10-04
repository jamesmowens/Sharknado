/* BoatCodeStarterWind_Accel rev 9/22/2019
© 2014-2019 RoboSail
Find detailed description in Decription tab
*/

#include <RoboSail_Hardware.h>  //Fill in min/max hardware parameters in this file
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include "declarations.h"       // tab with variable declarations

boolean displayValues = false;  //true calls function for values to be printed to monitor

void setup() 
{
  Serial.begin(115200);
  delay(1000); Serial.print("This boat is "); Serial.println(ROBOSAIL_BOAT_NAME);
  accel.begin();
  Serial.println("\nRoboSail BoatCode using Wind and Accel - XXXXX");  //write program name here
  declarePins();    // Set RC receiver and WindSensor on digital input pins
}

void loop() 
{
//*********** Read in data from the RC receiver and sensors *********
readReceiver();
readWind();
readAccel();

// You should have values from the RC Receiver and Sensors in these variables:
// rudderPosition, sailPosition, and windAngle,and robosailRollAccel
// as defined in the declarations.h tab and on the Frame-of-Reference model
// The variable robosailRollAccel is positive when rolling to Port side, 
// and negative when rolling to Starboard
// 
// Calculate new values for rudderPosition and sailPosition in degrees
// and set those variables to the new values.
// If you do not set the values, it will use the values from the RC Receiver

//**************** your code here - add lines as needed ******************
float wind = abs(windAngle);
//sailPosition = getSailPosition(wind);
rudderPosition = sailToAngle(90, windAngle);
Serial.print("New Rudder: ");
Serial.print(rudderPosition);
Serial.print("      ");
Serial.print("Current Wind: ");
Serial.print(windAngle);

Serial.println();


//********************* send commands to motors ***************************
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);

  if (displayValues) {printToMonitor();}

} //end of loop()
