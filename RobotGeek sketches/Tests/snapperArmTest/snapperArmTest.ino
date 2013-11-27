/***********************************************************************************
 *  }--\     RobotGeek Snapper Robotic Arm     /--{
 *      |         Analog Control Code         |
 *   __/                                       \__
 *  |__|                                       |__|
 *
 *
 *  The following sketch will test the snapper arm by sequentially moving each 
 *  joint of the arm .
 *
 *  http://learn.trossenrobotics.com/33-robotgeek-getting-started-guides/robotgeek-snapper-robot-arm/63-robotgeek-snapper-arm-getting-started-guide
 *
 *
 *  WIRING
 *    Servos
 *      Digital I/O 3 - Base Rotation - Robot Geek Servo 
 *      Digital I/O 5 - Shoulder Joint - Robot Geek Servo 
 *      Digital I/O 6 - Elbow Joint - Robot Geek Servo 
 *      Digital I/O 9 - Wrist Joint - Robot Geek Servo 
 *      Digital I/O 10 - Gripper Servo - 9g Servo 
 *
 *    Analog Inputs
 *      Analog inputs will be ignored for this test sketch
 *  
 *    Use an external power supply and set both PWM jumpers to 'VIN'
 *
 *  Sequence
 *     -Arm Startup
 *     -Arm Moves to 'centered' position 
 *     -Base servo moves 90 degrees clockwise
 *     -Base servo moves 180 degress counterclockwise
 *     -Base servo moves 90 degrees clockwise to 'centered' position

 *     -Shoulder servo moves 90 degrees clockwise (back)
 *     -Shoulder servo moves ~120 degrees counterclockwise (forward)
 *     -Shoulder servo moves ~30 degrees clockwise (back) to 'centered' position

 *     -Elbow servo moves ~30 degrees clockwise (down)
 *     -Elbow servo moves ~120 degrees counterclockwise (up)
 *     -Elbow servo moves 90 degrees clockwise (down)to 'centered' position

 *     -Wrist servo moves 90 degrees clockwise (down)
 *     -Wrist servo moves 180 degrees counterclockwise (down)
 *     -Wrist servo moves 90 degrees clockwise (down)to 'centered' position

 *     -Gripper servo moves ~60 degrees clockwise (open)
 *     -Gripper servo moves ~120 degrees counterclockwise (closed)
 *     -Gripper servo moves ~60 degrees clockwise (half open) to 'centered' position
 *  
 *
 *  NOTES
 *    This test code has specific limits for testing the snapper arm. It is
 *    NOT reccomended that this code be used as a basis for any other code.    
 *    Instead, use the Analog control code, found here: 
 *    https://github.com/trossenrobotics/RobotGeekArmAnalog/archive/master.zip
 *
 *
 *  This code is a Work In Progress and is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 ***********************************************************************************/
#include <Servo.h>

//define analog pins that will be connected to the joystick pins
#define BASE     0  //connected to Rotation Knob / Potentiometer # 1
#define SHOULDER 1  //connected to Vertical Axis on Joystick # 1
#define ELBOW    2  //connected to Vertical Axis on Joystick # 2
#define WRIST    3  //connected to Vertical Axis on Joystick # 3
#define GRIPPER  4  //connected to Rotation Knob / Potentiometer # 2

// Servo position limitations - limits in microseconds
#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  1800
#define ELBOW_MIN     1200
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 
#define GRIPPER_MIN   900    //full counterclockwise for 9g servo
#define GRIPPER_MAX   2100   //full clockwise for 9g servo
#define CENTERED      1500

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 462   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 562  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

// Declare servo objects
Servo BAS_SERVO;    //base servo - RobotGeek Servo
Servo SHL_SERVO;    //shoulder servo - RobotGeek Servo 
Servo ELB_SERVO;    //elbow servo - RobotGeek Servo 
Servo WRI_SERVO;    //wrist servo - RobotGeek Servo
Servo WRO_SERVO;    //wrist rotate servo - RobotGeek Servo (unused for snapper arm)        
Servo GRI_SERVO;    //gripper servo - 9g servo

//present positions of the servos 
int Base     =1500;    //holds the present position of the Base servo, starts at 1500 (centered)
int Shoulder =1500;    //holds the present position of the Shoulder servo, starts at 1500 (centered)
int Elbow    =1500;    //holds the present position of the Elbow servo, starts at 1500 (centered)
int Wrist    =1500;    //holds the present position of the wrist servo, starts at 1500 (centered)
int Gripper  =1500;    //holds the present position of the gripper servo, starts at 1500 (centered)

//last read values of analog sensors (Native values, 0-1023)
int joyBaseVal = 0;     //present value of the base rotation knob (analog 0)
int joyShoulderVal = 0; //present value of the shoulder joystick (analog 1)
int joyElbowVal = 0;    //present value of the elbow joystick (analog 2)
int joyWristVal = 0;    //present value of the wrist joystick (analog 3)
int joyGripperVal = 0;  //present value of the gripper rotation knob (analog 4)

//last calculated values of analog sensors (Mapped values)
//knob values (base and gripper) will be mapped directly to the servo limits
//joystick values (shoulder, elbow and wrist) will be mapped from -speed to speed, to faciliate incremental control
int joyBaseMapped = 0;      //base knob value, mapped from 1-1023 to BASE_MIN-BASE_MAX
int joyShoulderMapped = 0;  //shoulder joystick value, mapped from 1-1023 to -speed to speed
int joyElbowMapped = 0;     //elbow joystick value, mapped from 1-1023 to -speed to speed
int joyWristMapped = 0;     //wrist joystick value, mapped from 1-1023 to -speed to speed
int joyGripperMapped = 0;   //gripper knob  value, mapped from 1-1023 to GRIPPER_MIN-GRIPPER_MAX

int speed = 10;  //speed modififer, increase this to increase the speed of the movement


//===================================================================================================
// Setup 
//====================================================================================================
void setup() 
{

  // Attach servo and set limits
  BAS_SERVO.attach(3, BASE_MIN, BASE_MAX);
  SHL_SERVO.attach(5, SHOULDER_MIN, SHOULDER_MAX);
  ELB_SERVO.attach(6, ELBOW_MIN, ELBOW_MAX);
  WRI_SERVO.attach(9, WRIST_MIN, WRIST_MAX);
  GRI_SERVO.attach(10, GRIPPER_MIN, GRIPPER_MAX);
  
  delay(2000);  //wait 1 second
  
  set_servo();  // Move servos to defualt positions
}

void loop() 
{
  
  BAS_SERVO.writeMicroseconds(BASE_MIN);
  delay(1000);
  BAS_SERVO.writeMicroseconds(BASE_MAX);
  delay(1000);
  BAS_SERVO.writeMicroseconds(CENTERED);
  delay(1000);
  
  SHL_SERVO.writeMicroseconds(SHOULDER_MIN);
  delay(1000);
  SHL_SERVO.writeMicroseconds(SHOULDER_MAX);
  delay(1000);
  SHL_SERVO.writeMicroseconds(CENTERED);
  delay(1000);

  ELB_SERVO.writeMicroseconds(ELBOW_MIN);
  delay(1000);
  ELB_SERVO.writeMicroseconds(ELBOW_MAX);
  delay(1000); 
  ELB_SERVO.writeMicroseconds(CENTERED);
  delay(1000); 
  
  WRI_SERVO.writeMicroseconds(WRIST_MIN);
  delay(1000);  
  WRI_SERVO.writeMicroseconds(WRIST_MAX);
  delay(1000);
  WRI_SERVO.writeMicroseconds(CENTERED);
  delay(1000);
  
  GRI_SERVO.writeMicroseconds(GRIPPER_MIN);
  delay(1000); 
  GRI_SERVO.writeMicroseconds(GRIPPER_MAX);
  delay(1000);
  GRI_SERVO.writeMicroseconds(CENTERED);
  delay(1000);
  
  }




/******************************************************
 *  set_servo()
 *
 *  This function sets the 5 servos on the snapper arm
 *  to the 5 positions variables. All servos and
 *  positions variables are globals 
 *
 *  Parameters:
 *    none
  *
 *  Globals Used:
 *      Servo BAS_SERVO
 *      Servo WRI_SERVO
 *      Servo SHL_SERVO
 *      Servo ELB_SERVO
 *      Servo GRI_SERVO
 *      int Base
 *      int Wrist
 *      int Shoulder
 *      int Elbow
 *      int Gripper
 *
 *  Returns: 
 *    none
 ******************************************************/ 

void set_servo()
{
  BAS_SERVO.writeMicroseconds(Base);
  WRI_SERVO.writeMicroseconds(Wrist);
  SHL_SERVO.writeMicroseconds(Shoulder);
  ELB_SERVO.writeMicroseconds(Elbow);
  GRI_SERVO.writeMicroseconds(Gripper);
    delay(10);
}