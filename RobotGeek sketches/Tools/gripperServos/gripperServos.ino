/***********************************************************************************
 *   ___________
 *  |     __    |           RobotGeek Gripper
 *  |   /    \  |                Micro Servo Setup Tool
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|
 *
 *  The following sketch will set up the 2 servos for the RobotGeek Gripper
 *  The sketch will send a signal to pin 9 of the Geekduino/Arduino's pins to
 *  that sets the attached servo to 150 degrees. This will set the micro servo correctly 
 *  for assembly of the gripper
 *  The sketch will also set the servo attached to pin 11 to 90 degrees, centering the large servo.
 *
 *  Servo
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


void setup()
{ 
  servoToSet.attach(MICRO_SERVOPIN);
  servoToSet.write(150);    // sets the servo position to 150 degress, positioning the servo for the gripper
  servoToSet.attach(LARGE_SERVOPIN);
  servoToSet.write(90);    // sets the servo position to 900 degress, centered
}
 
void loop()
{
  //Once the program uses '.write()' to send a signal to the pin, it will maintain that signal until the unit is powered off or a new signal is sent with '.write()'
}
 
 
 
 
 
