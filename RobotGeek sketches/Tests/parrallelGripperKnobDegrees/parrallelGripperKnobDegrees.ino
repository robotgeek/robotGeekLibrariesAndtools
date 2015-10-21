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

#define KNOB1_ANALOGPIN 0  //analog pin of knob1 to control micro/gripper servo
#define KNOB2_ANALOGPIN 1  //analog pin of knob2 to control large/wrist servo
#define WRIST_SERVOPIN 9  //pin that the large servo will be attached to
#define GRIPPER_SERVOPIN 10  //pin that the micro servo will be attached to

#define GRIPPER_MIN   30    //fully closed
#define GRIPPER_MAX   180   //fully open 
#define WRIST_MIN     0
#define WRIST_MAX     180 


Servo gripperServo;   //create an servo object for the 9g FT-FS90MG micro servo
Servo wristServo;   //create an servo object for the RobotGeek 180 degree serco

int knob1Value = 0;
int knob2Value = 0;

int gripperServoValue = 90;
int wristServoValue = 90;

//setup servo objects and set initial position
void setup()
{ 
  gripperServo.attach(GRIPPER_SERVOPIN);
  gripperServo.write(gripperServoValue);    // sets the servo position to 150 degress, positioning the servo for the gripper closed
  wristServo.attach(WRIST_SERVOPIN);
  wristServo.write(wristServoValue);    // sets the servo position to 90 degress, centered
  
  Serial.begin(9600);
  Serial.print("Gripper Knob Test");
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
  gripperServoValue = map(knob1Value, 0, 1023, GRIPPER_MIN, GRIPPER_MAX);
  wristServoValue = map(knob2Value, 0, 1023, WRIST_MIN, WRIST_MAX);

  //write scaled values from the knobs to the servos.  
  gripperServo.write(gripperServoValue);   
  wristServo.write(wristServoValue);    
  
  
  Serial.print("Gripper Knob:");
  Serial.print(knob1Value);
  Serial.print("    Gripper Servo Value:");
  Serial.print(gripperServoValue);
  Serial.print("    Wrist Knob:");
  Serial.print(knob2Value);
  Serial.print("    Gripper Servo Value:");
  Serial.println(wristServoValue);
  
  delay(10);//short delay for servos to move
  
}
 
 
 
 
 
