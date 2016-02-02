/***********************************************************************************
 *     -(] [)-          RobotGeek Gripper  
 *   / /     \ \              Automatic Test
 *  | |       | |
 *   \ \_____/ /
 *    |  ___  |
 *    |_|___|_|
 *    | _____ |
 *     |     |
 *     |     |
 *     |_____|
 *
 *  The following sketch will move each servo in the RobotGeek Gripper. It will repeat the following cycle
 * 
 *  1)Open gripper, wait 3 seconds
 *  2)Close Gripper, wait 3 seconds
 *  3)Lower Wrist Servo ~ 90 degrees, wait 3 seconds
 *  4)Raise Wrist Servo ~ 90 degrees, wait 3 seconds
 *  5)Level Wrist Servo, wait 3 seconds
 *
 *  First it will open and close the gripper
 *  Then it will raise and lower the wrist servo.
 *  
 *    
 *  Wiring
 *
 *  DIO 9 - Blue Micro Servo (FT-FS90MG)      Orange - 'S' Brown -'G'
 *  DIO 11 - Black RobotGeek 180 Degree Servo  White -'S' Black -'G'
 *  
 *  Use an external power supply and set the jumper for pins 9/10/11 to 'VIN'
 *   
 *  For more information and wiring diagrams see
 *  http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/55-robotgeek-gripper-kit-tips
 *
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

#define MICRO_SERVOPIN 9  //pin that the micro servo will be attached to
#define LARGE_SERVOPIN 11  //pin that the large servo will be attached to

Servo microServo;   //create an servo object for the 9g FT-FS90MG micro servo
Servo largeServo;   //create an servo object for the RobotGeek 180 degree serco

//setup servo objects and set initial position
void setup()
{ 
  microServo.attach(MICRO_SERVOPIN);
  microServo.write(150);    // sets the servo position to 150 degress, positioning the servo for the gripper closed
  largeServo.attach(LARGE_SERVOPIN);
  largeServo.write(90);    // sets the servo position to 90 degress, centered
}
 
//repeat test process 
void loop()
{
  microServo.write(0);    //set gripper to 0 degrees = fully open
  delay(3000);            //wait 3 seconds
  microServo.write(150);  //set gripper to 130 degrees = fully closed
  delay(3000);            //wait 3 seconds
  largeServo.write(0);    //set wrist servo to 0 degrees = wrist down
  delay(3000);            //wait 3 seconds
  largeServo.write(180);  //set wrist servo to 180 degrees = wrist up
  delay(3000);            //wait 3 seconds
  largeServo.write(90);   //set wrist servo to 90 degrees = wrist level
  delay(3000);            //wait 3 seconds
  
}
 
 
 
 
 
