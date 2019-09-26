// variables to hold input and output values
int rudderPulseWidth;
int rudderPosition = 0;
int rudderServoOut;
int sailPulseWidth;
int sailPosition = 45;
int sailServoOut;
//variables for WindSensor
int windAngle = 0;
int windPulseWidth = 0;


enum state {
  HOLD,
  HEAD_UP,
  FALL_OFF,
}

state currentState = state.HOLD;

//create servo objects
Servo rudderServo;
Servo sailServo;
