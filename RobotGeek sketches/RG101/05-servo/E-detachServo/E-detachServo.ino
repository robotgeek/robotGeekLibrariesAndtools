/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Detach Servo
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code will set the positions on a servo using servo.writeMicroseconds(). Pressing
 *  a button will detach the servo using servo.detach(), stopping it from receiving commands
 *  
 *  Note that this will only work on digital servos, like the second generation robotgeek
 *  servos (these servos have a solid white cable for signal)
 *  
 *  Digital 2 - RobotGeek Pushbutton
 *  Digital 3 - RobotGeek Servo
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Servo Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/233-servo-primer.html
 *  
 * Important Functions
 *  servo.attach()
 *  servo.write()
 *  servo.detach()
 *****************************************************************************************/
#include <Servo.h>

const int SERVO_MIN_PULSE = 600;
const int SERVO_MAX_PULSE = 2400;
const int SERVO_CENTER_PULSE = 1500;
const int SERVO_PIN = 3;      //pin number for the servo pin - this is 'const' since it will not change during code, and saves Arduino memory
const int BUTTON_PIN = 2;      //pin number for the button pin - this is 'const' since it will not change during code, and saves Arduino memory

int servoValue = SERVO_MIN_PULSE;
int servoIncrement = 100;      //value to increment/decrement the servo by
Servo servo1;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{

  pinMode(BUTTON_PIN, INPUT);
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN

  servo1.writeMicroseconds(servoValue);  //send the servo to '0' degrees
  delay(3000);      //wait for the servo to move before moving again
  
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  servo1.writeMicroseconds(servoValue);     //send the servo to '0' degrees
  servoValue = servoValue + servoIncrement; //update servo value for next loop

  //if the servo is out of bounds, 
  if(servoValue <= SERVO_MIN_PULSE || servoValue >= SERVO_MAX_PULSE)
  {
    servoIncrement = -1 * servoIncrement; //reverse the increment
  }

  delay(50);  //wait for the servo to move

  //check if the button has been pressed
  if(digitalRead(BUTTON_PIN) == HIGH)
  {
    servo1.detach();  //detach the servo - this will stop it from receiving commands and turn its torque off.
  }
  
}//go back to the first line in loop()
