/***********************************************************************************
 *   ___________
 *  |     __    |           RGC - Servo 
 *  |   /    \  |                Analog To Servo - Absolute Inverse
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code is intended for use with the RobotGeek Snapper Arm and the RobotGeek
 *   curriculum.
 *  
 *  This code will set the positions on a servo using servo.write()
 *  based on the input from an analog sensor. It will use the analog input from the third 
 *  joystick (analog pin 3) and target the wrist servo on the arm (digital pin 9). This sketch will invert
 *  the values, so that the 2 devices move in the same direction
 *  
 *  A simple mapping of the analog to servo values will control the joystick absolutley-
 *  the angle of the joystick will directly be set to the angle of the servo.
 *  
 *  Digital 9 - RobotGeek Servo
 *  Analog 3 - RobotGeek Rotation Knob or other Analog Input
 *  
 * For a more in depth explanation of wiring,  this code and more information, see
 * http://learn.robotgeek.com/rgc/262-rgc-robotgeek-snapper-arm.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  servo.write()
 *  map()
 *****************************************************************************************/
#include <Servo.h>

const int ANALOG_PIN = 4;           //rotational knob sensor
const int SERVO_PIN = 9;            //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory

int analogSensorValue;    //the raw value read from the analog sensor
int servoValue;           //holds the servo position (0-180)

Servo wristServo;             //create an instance of the servo class, 'wristServo'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  wristServo.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 
  
  servoValue = map(analogSensorValue, 0, 1023, 180, 0 );  //the map functions converts a number from one range to another, so the analog input is mapped to the servo degree values
  wristServo.write(servoValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input
  delay(10);  //short delay to account for servo movement
  
}//go back to the first line in loop()
