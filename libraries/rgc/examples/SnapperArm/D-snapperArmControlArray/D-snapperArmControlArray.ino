/***********************************************************************************
 *  }--\     RobotGeek Snapper Robotic Arm     /--{
 *      |         Analog Control Code         |
 *   __/                                       \__
 *  |__|                                       |__|
 *
 *
 *  The following sketch will move each joint of the arm based on analog inputs.
 *

 *  WIRING
 *    Servos
 *      Digital I/O 3 - Base Rotation - Robot Geek Servo 
 *      Digital I/O 5 - Shoulder Joint - Robot Geek Servo 
 *      Digital I/O 6 - Elbow Joint - Robot Geek Servo 
 *      Digital I/O 9 - Wrist Joint - Robot Geek Servo 
 *      Digital I/O 10 - Gripper Servo - Robot Geek Servo 
 *
 *    Analog Inputs
 *      Analog 0 - Joystick (Horizontal)
 *      Analog 1 - Joystick (Vertical)
 *      Analog 2 - Joystick (Vertical)
 *      Analog 3 - Joystick (Vertical)
 *      Analog 4 - Rotation Knob 
 *  
 *    Use an external power supply and set both PWM jumpers to 'VIN'
 *
 *  CONTROL
 *    Turn the 
 *
 *
 *  NOTES
 *    ANALOG INPUT MAPPING
 *      This code uses a combination of direct and incremental code for converting 
 *      analog inputs into servo positions
 *    
 *      Direct/Absolute
 *        Absolute positioning is used for the knobs controlling the base and gripper servo.
 *        This means that the value of the knob is mapped directly to the corresponding servo
 *        value. This method is ideal for sensors that stay at static positions such as
 *        knobs and sliders. 
 *    
 *      Incremental
 *        Incremental code is used for the joysticks controlling the shoulder, elbow and
 *        gripper servo. Each joystick value is mapped to a small realtiveley small positive
 *        or negative value. This value is then added to the currrent position of the servo.
 *        The action of slowly moving the joystick away from its center position can slowly 
 *        move each joint of the robot. When the joystick is centered, no movement is made
 *     
 *      The choice for using Direct/Incremental mapping for each joint was made based
 *      on usability, however the code can be modified so that any joint can use
 *      either direct or incremental mapping
 *

 *
 *  This code is a Work In Progress and is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 ***********************************************************************************/
#include <Servo.h>


//define analog pins that will be connected to the joystick pins
const int BASE_ANALOG_PIN = 0;  //connected to Horizontal Axis on Joystick # 1
const int SHOULDER_ANALOG_PIN = 1;  //connected to Vertical Axis on Joystick # 2
const int ELBOW_ANALOG_PIN = 2;  //connected to Vertical Axis on Joystick # 3
const int WRIST_ANALOG_PIN = 3;  //connected to Vertical Axis on Joystick # 4
const int GRIPPER_ANALOG_PIN = 4;  //connected to Rotation Knob / Potentiometer # 1

//define analog pins that will be connected to the joystick pins
const int BASE_SERVO_PIN = 3;  //connected to Horizontal Axis on Joystick # 1
const int SHOULDER_SERVO_PIN = 5;  //connected to Vertical Axis on Joystick # 2
const int ELBOW_SERVO_PIN = 6;  //connected to Vertical Axis on Joystick # 3
const int WRIST_SERVO_PIN = 9;  //connected to Vertical Axis on Joystick # 4
const int GRIPPER_SERVO_PIN = 10;  //connected to Rotation Knob / Potentiometer # 1

// Servo position limitations - limits in microseconds
const int BASE_MIN = 0;     //full counterclockwise for RobotGeek 180 degree servo
const int BASE_MAX = 180;    //full clockwise for RobotGeek 180 degree servo
const int SHOULDER_MIN = 0;
const int SHOULDER_MAX = 180;
const int ELBOW_MIN = 0;
const int ELBOW_MAX = 180;
const int WRIST_MIN = 0;
const int WRIST_MAX = 180;

const int GRIPPER_MIN = 15;    //fully closed
const int GRIPPER_MAX = 180;   //fully open


//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 482   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 542  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

// Declare servo objects
Servo baseServo;    //base servo - RobotGeek Servo
Servo shoulderServo;    //shoulder servo - RobotGeek Servo 
Servo elbowServo;    //elbow servo - RobotGeek Servo 
Servo wristServo;    //wrist servo - RobotGeek Servo
Servo gripperServo;    //gripper servo - 9g servo

//present positions of the servos 
int basePosition     = 90;    //holds the present position of the Base servo, starts at  90 (centered)
int shoulderPosition = 90;    //holds the present position of the Shoulder servo, starts at  90 (centered)
int elbowPosition    = 90;    //holds the present position of the Elbow servo, starts at  90 (centered)
int wristPosition    = 90;    //holds the present position of the wrist servo, starts at  90 (centered)
int gripperPosition  = 90;    //holds the present position of the gripper servo, starts at  90 (centered)


//last read values of analog sensors (Native values, 0-1023)
int joyBaseVal = 0;     //present value of the base rotation knob (analog 0)
int joyShoulderVal = 0; //present value of the shoulder joystick (analog 1)
int joyElbowVal = 0;    //present value of the elbow joystick (analog 2)
int joyWristVal = 0;    //present value of the wrist joystick (analog 3)
int joyGripperVal = 0;  //present value of the gripper rotation knob (analog 4)

//last calculated values of analog sensors (Mapped values)
//knob values (base and gripper) will be mapped directly to the servo limits
//joystick values (shoulder, elbow and wrist) will be mapped from -speed to speed, to faciliate incremental control
int baseIncrement = 0;      //base knob value, mapped from 1-1023 to -speed to speed
int shoulderIncrement = 0;  //shoulder joystick value, mapped from 1-1023 to -speed to speed
int elbowIncrement = 0;     //elbow joystick value, mapped from 1-1023 to -speed to speed
int wristIncrement = 0;     //wrist joystick value, mapped from 1-1023 to -speed to speed
int joyGripperMapped = 0;   //gripper knob  value, mapped from 1-1023 to GRIPPER_MIN-GRIPPER_MAX

int speed = 10;  //speed modififer, increase this to increase the speed of the movement


//===================================================================================================
// Setup 
//====================================================================================================
void setup() 
{

  // Attach servo and set limits
  baseServo.attach(BASE_SERVO_PIN, BASE_MIN, BASE_MAX);
  shoulderServo.attach(SHOULDER_SERVO_PIN, SHOULDER_MIN, SHOULDER_MAX);
  elbowServo.attach(ELBOW_SERVO_PIN, ELBOW_MIN, ELBOW_MAX);
  wristServo.attach(WRIST_SERVO_PIN, WRIST_MIN, WRIST_MAX);
  gripperServo.attach(GRIPPER_SERVO_PIN, GRIPPER_MIN, GRIPPER_MAX);
  
  delay(1000);  //wait 1 second
  

}

void loop() 
{
    //**********READ CONTROLS*********************/
   //read analog values from analog sensors
   joyBaseVal = analogRead(BASE_ANALOG_PIN);
   joyShoulderVal = analogRead(SHOULDER_ANALOG_PIN);
   joyElbowVal = analogRead(ELBOW_ANALOG_PIN);
   joyWristVal = analogRead(WRIST_ANALOG_PIN);
   joyGripperVal = analogRead(GRIPPER_ANALOG_PIN);
    

 
    //**********BASE SERVO CONTROL*********************/
   //only update the base joint if the joystick is outside the deadzone (i.e. moved oustide the center position)
   if(joyBaseVal > DEADBANDHIGH || joyBaseVal < DEADBANDLOW)
   {
     baseIncrement = map(joyBaseVal, 0, 1023, -speed, speed); //Map analog value from native joystick value (0 to 1023) to incremental change (-speed to speed)
     basePosition = basePosition + baseIncrement; //add mapped base joystick value to present Base Value (positive values of joyBaseMapped will increase the position, negative values will decrease the position)
   }

   

    //**********SHOULDER SERVO CONTROL*********************/
   //only update the shoulder joint if the joystick is outside the deadzone (i.e. moved oustide the center position)
   if(joyShoulderVal > DEADBANDHIGH || joyShoulderVal < DEADBANDLOW)
   {
     shoulderIncrement = map(joyShoulderVal, 0, 1023, -speed, speed); //Map analog value from native joystick value (0 to 1023) to incremental change (-speed to speed)
     shoulderPosition = shoulderPosition - shoulderIncrement; //add mapped shoulder joystick value to present Shoulder Value (positive values of joyShoulderMapped will increase the position, negative values will decrease the position)
   }

   

    //**********ELBOW SERVO CONTROL*********************/
   //only update the elbow joint if the joystick is outside the deadzone (i.e. moved oustide the center position)
   if(elbowIncrement > DEADBANDHIGH || joyElbowVal < DEADBANDLOW)
   {
     elbowIncrement = map(joyElbowVal, 0, 1023, -speed, speed); //Map analog value from native joystick value (0 to 1023) to incremental change (-speed to speed)
     elbowPosition = elbowPosition + elbowIncrement;//add mapped elbow joystick value to present elbow Value (positive values of joyElbowMapped will increase the position, negative values will decrease the position)
   }

   

    //**********WRIST SERVO CONTROL*********************/
   //only update the wrist joint if the joystick is outside the deadzone (i.e. moved oustide the center position)
   if(wristIncrement > DEADBANDHIGH || joyWristVal < DEADBANDLOW)
   {
     wristIncrement = map(joyWristVal, 0, 1023, -speed, speed); //Map analog value from native joystick value (0 to 1023) to incremental change (-speed to speed)
     wristPosition = wristPosition + wristIncrement;//add mapped wrist joystick value to present wrist Value (positive values of joyWristMapped will increase the position, negative values will decrease the position)
   }

   

    //**********GRIPPER SERVO CONTROL*********************/
   //absolute Mapping analog joystick value to servo  signal range
   joyGripperMapped = map(joyGripperVal, 0, 1023, GRIPPER_MIN, GRIPPER_MAX);
   gripperPosition = joyGripperMapped;//set servo position variable to the mapped value from the knob


    //**********CONTSTAIN SERVOS*********************/
   // We need to keep the servo value between MIN and MAX. If values go above MAX or below MIN we will have eratic behavior.
   // the contstrain function takes care of this. Values below MIN are set to MIN and above MAX are set to MAX 
    basePosition = constrain( basePosition, BASE_MIN, BASE_MAX );
    shoulderPosition = constrain( shoulderPosition, SHOULDER_MIN, SHOULDER_MAX );
    elbowPosition = constrain( elbowPosition, ELBOW_MIN, ELBOW_MAX );
    wristIncrement = constrain( wristIncrement, WRIST_MIN, WRIST_MAX );
    gripperPosition = constrain( gripperPosition, GRIPPER_MIN, GRIPPER_MAX );


   

    //**********WRITE SERVOS*********************/
    //write all of the calculated servo positions
    baseServo.write(basePosition);
    shoulderServo.write(shoulderPosition);
    elbowServo.write(elbowPosition);
    wristServo.write(wristIncrement);
    gripperServo.write(gripperPosition);

    
    delay(10);  //wait a short time to account for servo movement.

  
  }


