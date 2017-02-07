/***********************************************************************************
 * Small Vacation Fish Feeder - Single Servo
 * 
 * This is a dead simple project. Using the 3D printed body, a single servo, and a
 * Geekduino, you can feed a small fish automatically for over a week!
 * 
 * DIO-3 - RobotGeek 180 Degree Servo
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

#define SECOND 1000L
#define MINUTE (60*SECOND)
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)

const int SERVO_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory

Servo servo1;

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  //******************************************************************************
  //NOTE: YOU WILL HAVE TO CHANGE THESE VALUES based on your servo horn alignment.
  //******************************************************************************
  
  servo1.writeMicroseconds(651);  //send the servo to '0' degrees
  delay(DAY);      //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(880);  //send the servo to '20' degrees
  delay(DAY);       //wait for the servo to move before moving again
    
  servo1.writeMicroseconds(1047);  //send the servo to '40' degrees
  delay(DAY);      //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(1241);  //send the servo to '60' degrees
  delay(DAY);      //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(1433);  //send the servo to '80' degrees
  delay(DAY);       //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(1638);  //send the servo to '100' degrees
  delay(DAY);       //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(1834);  //send the servo to '120' degrees
  delay(DAY);       //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(2051);  //send the servo to '140' degrees
  delay(DAY);       //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(2220);  //send the servo to '160' degrees
  delay(DAY);       //wait for the servo to move before moving again
  
  servo1.writeMicroseconds(2400);  //send the servo to '180' degrees
  delay(DAY);       //wait for the servo to move before moving again
}//go back to the first line in loop()
