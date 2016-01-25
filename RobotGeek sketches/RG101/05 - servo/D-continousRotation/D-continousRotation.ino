/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Set Servo Microseconds
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code will set the speed of a continous turnservo using servo.writeMicroseconds()
 *  The continous turn servos will max out at 1200us/1800us ccw/cw speeds - any thing beyond
 *  these values will maintain the maximum speed. 
 *  
 *  Digital 3 - RobotGeek Servo
 *  
 *  There is a deadband arounf 1500 - from about 1450 to 1550. Within this deadband, 
 *  the servo will be off.
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

const int SERVO_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int SERVO_MIN_PULSE = 1200;
const int SERVO_MAX_PULSE = 1800;
const int SERVO_STOP_PULSE = 1500;

Servo servo1;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN

  servo1.writeMicroseconds(SERVO_STOP_PULSE);  //'stop' the servo

  //ramp up CW
  for(int i = SERVO_STOP_PULSE; i <= SERVO_MAX_PULSE; i++)
  {
    servo1.writeMicroseconds(i);  //write the servo value
    delay(50);                    //wait a short time so the speed ramp is evident
  }

  //ramp down to stopped
  for(int i = SERVO_MAX_PULSE; i >= SERVO_STOP_PULSE; i--)
  {
    servo1.writeMicroseconds(i);  //write the servo value
    delay(50);                    //wait a short time so the speed ramp is evident
  }
  
  //ramp up CCW
  for(int i = SERVO_STOP_PULSE; i >= SERVO_MIN_PULSE; i--)
  {
    servo1.writeMicroseconds(i);  //write the servo value
    delay(50);                    //wait a short time so the speed ramp is evident
  }

  
  //ramp down to stopped
  for(int i = SERVO_MIN_PULSE; i <= SERVO_STOP_PULSE; i++)
  {
    servo1.writeMicroseconds(i);  //write the servo value
    delay(50);                    //wait a short time so the speed ramp is evident
  }

  

} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  
  
}//go back to the first line in loop()
