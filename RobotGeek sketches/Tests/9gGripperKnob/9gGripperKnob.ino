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
 *  The following sketch will move each servo in the RobotGeek Gripper. It will rpeat the following cycle
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
#define KNOB1_ANALOGPIN 0  //analog pin of knob1 to control micro/gripper servo
#define KNOB2_ANALOGPIN 1  //analog pin of knob2 to control large/wrist servo

Servo microServo;   //create an servo object for the 9g FT-FS90MG micro servo
Servo largeServo;   //create an servo object for the RobotGeek 180 degree serco

int knob1Value = 0;
int knob2Value = 0;

int microServoValue = 150;
int largeServoValue = 90;

//setup servo objects and set initial position
void setup()
{ 
  microServo.attach(MICRO_SERVOPIN);
  microServo.write(microServoValue);    // sets the servo position to 150 degress, positioning the servo for the gripper closed
  largeServo.attach(LARGE_SERVOPIN);
  largeServo.write(largeServoValue);    // sets the servo position to 90 degress, centered
}
 
//repeat test process 
void loop()
{
  knob1Value = analogRead(KNOB1_ANALOGPIN);
  delay(5);//short delay to allow the Analog-Digital-Converter (ADC) to settle down
  knob2Value = analogRead(KNOB2_ANALOGPIN);
 
  //the knob values will be read as a value between 0-1023, 
  //so they must be converted to a value between 0 and 180 (150 for the micro servo)
  //the map()function will convert the values 
  microServoValue = map(knob1Value, 0, 1023, 0, 150);
  largeServoValue = map(knob2Value, 0, 1023, 0, 180);

  //write scaled values from the knobs to the servos.  
  microServo.write(microServoValue);   
  largeServo.write(largeServoValue);    
  
  delay(10);//short delay for servos to move
  
}
 
 
 
 
 
