/***********************************************************************************
 *   ___________
 *  |     __    |           RobotGeek Gripper / Snapper Arm
 *  |   /    \  |                Servo Setup Tool
 *  |  |      | |   _____
 *  |   \ __ /  |  |  _  |
 *  |           |  | |*| |
 *  |           |  |     |
 *  |___________|  |_____|
 *
 *  The following sketch can be used to configure the servos for the
 *  RobotGeek Gripper and or the RobotGeek Snapper Arm. 
 *  The sketch will send a signal to pin 10 of the Geekduino/Arduino's pins to
 *  that sets the attached servo to 150 degrees. This will set the micro servo correctly 
 *  for assembly of the gripper
 *  The sketch will also set the servos attached to pins 3,5,6 and 9 to 90 degrees, 
 *  centering the larger RobotGeek servos. If you are not centering servos on these ports,
 *  you can simply leave the ports unplugged.
 *
 *  Wiring
 *		Gripper Kit Servos
 *  	DIO 9 - Black RobotGeek 180 Degree Servo (Wrist)     White -'S' Black -'G'
 *  	DIO 10 - Blue Micro Servo (FT-FS90MG) (Gripper)      Orange - 'S' Brown -'G'
 *
 *		Additional Snapper Arm Servos
 *  	DIO 9 - Black RobotGeek 180 Degree Servo(Base)       White -'S' Black -'G'
 *  	DIO 9 - Black RobotGeek 180 Degree Servo(Shoulder)   White -'S' Black -'G'
 *  	DIO 9 - Black RobotGeek 180 Degree Servo (Elbow)     White -'S' Black -'G'

 *
 *  Use an external power supply and set both power jumpers to 'VIN'
 *   
 *  For more information and wiring diagrams see the getting started guide for your kit
 *	Gripper Kit
 *  http://learn.trossenrobotics.com/30-robotgeek-getting-started-guides/dev-kits/55-robotgeek-gripper-kit-tips
 *  Snapper Arm Kit
 *  http://learn.trossenrobotics.com/33-robotgeek-getting-started-guides/robotgeek-snapper-robot-arm/63-robotgeek-snapper-arm-getting-started-guide
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

#define WRIST_SERVO_PIN 9  //pin that the wrist servo will be attached to
#define GRIPPER_SERVO_PIN_9g 11  //pin that the gripper 9g servo will be attached to
#define GRIPPER_SERVO_PIN_PARALLEL 10  //pin that the gripper 9g servo will be attached to

//also send data to pins 3, 5, and 6 for convieice when building the snapper arm
#define BASE_SERVO_PIN 3  //pin that the large servo will be attached to
#define SHOULDER_SERVO_PIN 5  //pin that the large servo will be attached to
#define ELBOW_SERVO_PIN 6  //pin that the large servo will be attached to



//gripper and wrist servos
Servo wristServo;
Servo gripperServo9g;   //create an servo object for the 9g FT-FS90MG micro servo
Servo gripperServoParallel;   //create an servo object for the robotgeek parallel gripper

//arm servos
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

void setup()
{ 
  

  
  
  
  
  
  //attach servos	
  gripperServo9g.attach(GRIPPER_SERVO_PIN_9g);
  gripperServoParallel.attach(GRIPPER_SERVO_PIN_PARALLEL);
  wristServo.attach(WRIST_SERVO_PIN); 
  baseServo.attach(BASE_SERVO_PIN);
  shoulderServo.attach(SHOULDER_SERVO_PIN);
  elbowServo.attach(ELBOW_SERVO_PIN);
  
  
 
  gripperServo9g.write(45);    // sets the servo position to 150 degress, positioning the servo for the 9g gripper
  gripperServoParallel.write(45);    // sets the servo position to 90 degress, positioning the servo for the parallel gripper
  wristServo.write(45);    // sets the servo position to 90 degress, centered
  baseServo.write(45);    // sets the servo position to 90 degress, centered
  shoulderServo.write(45);    // sets the servo position to 90 degress, centered
  elbowServo.write(45);    // sets the servo position to 90 degress, centered
  delay(1000);
 
  gripperServo9g.write(125);    // sets the servo position to 150 degress, positioning the servo for the 9g gripper
  gripperServoParallel.write(125);    // sets the servo position to 90 degress, positioning the servo for the parallel gripper
  wristServo.write(125);    // sets the servo position to 90 degress, centered
  baseServo.write(125);    // sets the servo position to 90 degress, centered
  shoulderServo.write(125);    // sets the servo position to 90 degress, centered
  elbowServo.write(125);    // sets the servo position to 90 degress, centered
  delay(1000);
  
  gripperServo9g.write(150);    // sets the servo position to 150 degress, positioning the servo for the 9g gripper
  gripperServoParallel.write(90);    // sets the servo position to 90 degress, positioning the servo for the parallel gripper
  wristServo.write(90);    // sets the servo position to 90 degress, centered
  baseServo.write(90);    // sets the servo position to 90 degress, centered
  shoulderServo.write(90);    // sets the servo position to 90 degress, centered
  elbowServo.write(90);    // sets the servo position to 90 degress, centered
}
 
void loop()
{
  //Once the program uses '.write()' to send a signal to the pin, it will maintain that signal until the unit is powered off or a new signal is sent with '.write()'
}
 
 
 
