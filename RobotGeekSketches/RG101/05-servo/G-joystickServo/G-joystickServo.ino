/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Joystick Servo
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code will incrementally set the position on a servo based on a joystick. 
 *	The servo will move in the direction that the joystick moves, but it will stay
 *  at its positon when the joystick is centered, allowing you to slowly adjust the 
 *  overall position of the servo.
 *  
 *  Digital 3 - RobotGeek Servo
 *  Analog 0 - RobotGeek Joystick (Horizontal or Vertical)
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Servo Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/233-servo-primer.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  servo.writeMicroseconds()
 *  map()
 *****************************************************************************************/
#include <Servo.h>

const int ANALOG_PIN = 0;			 //analog pin for joystick
const int SERVO_PIN = 3;      		 //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int SERVO_MIN_PULSE = 600;	 //minimum servo pulse in microceconds (0 degrees)
const int SERVO_MAX_PULSE = 2400;	 //maximum servo pulse in microceconds (180 degrees)
const int SERVO_CENTER_PULSE = 1500; //centered servo pulse in microceconds (90 degrees)

//deadband values for the joysticks - values between DEADBANDLOW and DEADBANDHIGH will be ignored
const int DEADBANDLOW = 480;   //lower deadband value for the joysticks  
const int DEADBANDHIGH = 540;  //upper deadband value for the joysticks  

int analogSensorValue;  //the raw value read from the analog sensor
int servoValue;         //holds the current PWM value (0-255)\
int speed = 10;         //alter this value to change the speed of the system. Higher values mean higher speeds 5-500 approximate recommended range

Servo servo1;             //create servo object, 'servo1'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 

   //check that the joystick is outisde of the deadband. Movements in the deadband should not register
   if(analogSensorValue < DEADBANDLOW || analogSensorValue > DEADBANDHIGH)
   {
     //analogSensorValue will hold a value between 0 and 1023 that correspods to the location of the joystick. The map() function will convert this value
     //into a value between speed and -speed. This value can then be added to the current servoValue to incrementley move ths servo 
     analogSensorValueMapped = map(analogSensorValue, 0, 1023, -speed, speed) ;
     
     servoValue = servoValue + analogSensorValueMapped; //add the analogSensorValueMapped to servoValue to slowly increment/decrement the tiltValue
     
     // We need to keep the servo value between SERVO_MIN_PULSE and SERVO_MAX_PULSE - the contstrain function takes care of this. 
     //Values below SERVO_MIN_PULSE are set to SERVO_MIN_PULSE and above SERVO_MAX_PULSE are set to SERVO_MAX_PULSE 
     servoValue = constrain(servoValue, SERVO_MIN_PULSE, SERVO_MAX_PULSE);	//
   }   

   servo1.writeMicroseconds(servoValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input
   delay(10);  //short delay to account for servo movement

  
}//go back to the first line in loop()
