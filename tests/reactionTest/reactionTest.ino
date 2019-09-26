/* BoatCodeStarterWindOnly rev 7/31/2017
© 2014-2017 RoboSail
Find detailed description in Decription tab
*/
#include <Servo.h>
#include <RoboSail_Hardware.h>
#include "RoboSail.h"
boolean displayValues = true;  //true calls function for values to be printed to monitor
//enum state {
//  HOLD,
//  HEAD_UP,
//  FALL_OFF,
//}
//
//String currentState = HOLD;

//Fill in min/max parameters for the RC Receiver and WindSensor in RoboSail.h tab

void setup() {
  Serial.begin(115200);

  // Print the boat's name (as defined in RoboSail_Hardware.h as an
  // explicit check that the settings file is being included properly
  Serial.print("This boat is "); Serial.println(ROBOSAIL_BOAT_NAME);
  Serial.println(__FILE__);  // prints the name (path) of this sketch

  // Set RC receiver and WindSensor on digital input pins
  declarePins();
}


void loop() {
//*********** Read in data from the RC receiver and sensors *********
readReceiver();
readWind();



if(abs(windAngle) - 90 == MARGIN_OF_ERROR) {
  currentState = HOLD;
} if (abs(windAngle) - 90 < MARGIN_OF_ERROR) {
  currentState = FALL_OFF;
} if (abs(windAngle) - 90 > MARGIN_OF_ERROR) {
  currentState = HEAD_UP;
}


switch (currentState) {
  case HOLD:
    break;
   case HEAD_UP:
    rudderPosition = 25;
   case FALL_OFF: 
    rudderPosition = -25;
}

// You now have values from the RC Receiver and Sensors in these variable:
// rudderPosition, sailPosition, and windAngle
// Calculate new values for rudderPosition and sailPosition in degrees
// and set those variables to the new values.
// If you do not set the values, it will use the values from the RC Receiver
// For example, to make the rudder follow the wind angle you would have:
// rudderPosition = windAngle;
//**************** your code here ******************



/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);

  if (displayValues) {printToMonitor();}

} //end of loop()
