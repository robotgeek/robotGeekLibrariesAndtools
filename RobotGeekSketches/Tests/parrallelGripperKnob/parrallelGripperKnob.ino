/***********************************************************************************
 *       _        _
 *      / |      | \                  RobotGeek Parallel Gripper  
 *     /  |      |  \                 Analog Test
 *    /   |      |   \
 *   /    |______|    \
 *   |________________|
 *       | _____ |
 *        |     |
 *        |     |
 *        |_____|
 *
 *  The following sketch will allow you to manually control the RobotGeek Parallel
 *  gripper and a wrist angle servo using analog inputs. 
 *    
 *  Wiring
 *  Analog Input 0 - Knob or other Analog Input Device
 *  Analog Input 1 - Knob or other Analog Input Device
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
  //so they must be converted to a value between the min and max for the servo
  //the map()function will convert the values 
  gripperServoValue = map(knob1Value, 0, 1023, GRIPPER_MIN, GRIPPER_MAX);
  wristServoValue = map(knob2Value, 0, 1023, WRIST_MIN, WRIST_MAX);

  //write scaled values from the knobs to the servos.  
  gripperServo.write(gripperServoValue);   
  wristServo.write(wristServoValue);    
  
  delay(10);//short delay for servos to move
  
  //display servo data to serial output for debugging
  Serial.print("Gripper Knob:");
  Serial.print(knob1Value);
  Serial.print("    Gripper Servo Value:");
  Serial.print(gripperServoValue);
  Serial.print("    Wrist Knob:");
  Serial.print(knob2Value);
  Serial.print("    Gripper Servo Value:");
  Serial.println(wristServoValue);
}
 
 
 
 
 
