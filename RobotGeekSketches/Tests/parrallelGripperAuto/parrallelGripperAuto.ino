/***********************************************************************************
 *       _        _
 *      / |      | \                  RobotGeek Parallel Gripper  
 *     /  |      |  \                 Automatic Test
 *    /   |      |   \
 *   /    |______|    \
 *   |________________|
 *       | _____ |
 *        |     |
 *        |     |
 *        |_____|


 *  The following sketch will move each servo in the RobotGeek Gripper. It will repeat the following cycle
 * 
 *  1)Open gripper, wait 1.5 seconds
 *  2)Close Gripper, wait 1.5 seconds
 *  3)Lower Wrist Servo down, wait 1.5 seconds
 *  4)Raise Wrist Servo  up , wait 1.5 seconds
 *  5)Level Wrist Servo, wait 3 seconds
 *
 *  First it will open and close the gripper
 *  Then it will raise and lower the wrist servo.
 *  
 *  This test can be run without the wrist angle servo,
 *  just do not pluf in the wrist angle servo
 *
 *  This test is designed for the gripper and wrist servo on their own. If you have
 *  the gripper/wrist servo attached to a rover or other robot, this test may cause servo 
 *  collisions.
 *
 *    
 *  Wiring
 *
 *  DIO 9 - Black RobotGeek 180 Degree Servo  White -'S' Black -'G'
 *  DIO 10 - Black RobotGeek 180 Degree Servo  White -'S' Black -'G'
 *  
 *  Use an external power supply and set the jumper for pins 9/10/11 to 'VIN'
 *   
 *  For more information and wiring diagrams see
 *  http://learn.robotgeek.com/projects/191-robotgeek-gripper-getting-started-guide-v2.html
 *
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

#define WRIST_SERVOPIN 9  //pin that the large servo will be attached to
#define GRIPPER_SERVOPIN 10  //pin that the micro servo will be attached to

#define GRIPPER_MIN   30    //fully closed
#define GRIPPER_MAX   180   //fully open 
#define WRIST_MIN     0     //Wrist down
#define WRIST_MAX     180   //Wrist Up

Servo gripperServo;   //create an servo object for the 9g FT-FS90MG micro servo
Servo wristServo;   //create an servo object for the RobotGeek 180 degree serco

//setup servo objects and set initial position
void setup()
{ 
  gripperServo.attach(GRIPPER_SERVOPIN);
  gripperServo.write(90);    // sets the servo position to 150 degress, positioning the servo for the gripper closed
  wristServo.attach(WRIST_SERVOPIN);
  wristServo.write(90);    // sets the servo position to 90 degress, centered
  
  
  gripperServo.write(GRIPPER_MAX);    //set gripper to 0 degrees = fully open
  delay(1500);            //wait 3 seconds
  gripperServo.write(GRIPPER_MIN);  //set gripper to 130 degrees = fully closed
  delay(1500);            //wait 3 seconds
  gripperServo.write(90);  //set gripper to 130 degrees = fully closed
  delay(1500);            //wait 3 seconds
  
  wristServo.write(WRIST_MIN);    //set wrist servo to 0 degrees = wrist down
  delay(1500);            //wait 3 seconds
  wristServo.write(WRIST_MAX);  //set wrist servo to 180 degrees = wrist up
  delay(1500);            //wait 3 seconds
  wristServo.write(90);   //set wrist servo to 90 degrees = wrist level
  //delay(1500);            //wait 3 seconds
  
  
}
 
//repeat test process 
void loop()
{
}
 
 
 
 
 
