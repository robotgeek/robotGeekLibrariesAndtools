/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Set Servo Degrees
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code will set the positions on a servo using servo.write()
 *  
 *  Digital 3 - RobotGeek Servo
 *  
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Servo Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/233-servo-primer.html
 *  
 * Important Functions
 *  servo.attach()
 *  servo.write()
 *****************************************************************************************/
#include <Servo.h>

const int SERVO_PIN = 3;  //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory

Servo servo1;             //create servo object, 'servo1'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN

  servo1.write(0);  //send the servo to '0' degrees
  delay(3000);      //wait for the servo to move before moving again
  
  servo1.write(90);  //send the servo to '90' degrees
  delay(3000);       //wait for the servo to move before moving again
    
  servo1.write(180);  //send the servo to '180' degrees
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  
}//go back to the first line in loop()
