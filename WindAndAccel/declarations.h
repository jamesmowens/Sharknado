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

//create servo objects
Servo rudderServo;
Servo sailServo;

float pitchAccel = 0;
float rollAccel = 0;
float yawAccel = 0;
float robosailRollAccel = 0;

//Assign ID to Accelerometer and define event
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
sensors_event_t event;
