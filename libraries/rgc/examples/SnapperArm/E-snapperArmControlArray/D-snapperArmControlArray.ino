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

const int NUMBER_OF_SERVOS = 5;
//define analog pins that will be connected to the joystick pins
const int ANALOG_PINS[] = {0,1,2,3,4};
const int SERVO_PINS[] = {3,5,6,9,10,11};

const int SERVO_MINS[] = {0,0,0,0,15};
const int SERVO_MAXES[] = {180,180,180,180,180};

int servoPositions[NUMBER_OF_SERVOS];
int analogValues[NUMBER_OF_SERVOS];
int servoIncrements[NUMBER_OF_SERVOS];

const int BASE_INDEX = 0;  //connected to Horizontal Axis on Joystick # 1
const int SHOULDER_ANALOG_PIN = 1;  //connected to Vertical Axis on Joystick # 2
const int ELBOW_ANALOG_PIN = 2;  //connected to Vertical Axis on Joystick # 3
const int WRIST_ANALOG_PIN = 3;  //connected to Vertical Axis on Joystick # 4
const int GRIPPER_ANALOG_PIN = 4;  //connected to Rotation Knob / Potentiometer # 1



//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
const int DEADBANDLOW = 482;   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
const int DEADBANDHIGH = 542;  //increase this value if drift occurs, decrease it to increase sensitivity around the center position



Servo armServos[5];

int speed = 10;  //speed modififer, increase this to increase the speed of the movement


//===================================================================================================
// Setup 
//====================================================================================================
void setup() 
{

  for(int i = 0; i < NUMBER_OF_SERVOS; i++)
  {
    armServos[i].attach(SERVO_PINS[i]);
  }


  
  delay(1000);  //wait 1 second
  

}

void loop() 
{
    //**********READ CONTROLS*********************/
   //read analog values from analog sensors

  for(int i = 0; i < NUMBER_OF_SERVOS; i++)
  {
    analogValues[i] = analogRead(ANALOG_PINS[i]);
    
   if(analogValues[i] > DEADBANDHIGH || analogValues[i] < DEADBANDLOW)
   {
     servoIncrements[i] = map(analogValues[i], 0, 1023, -speed, speed); //Map analog value from native joystick value (0 to 1023) to incremental change (-speed to speed)
     servoPositions[i] =  servoPositions[i] + servoIncrements[i]; //add mapped base joystick value to present Base Value (positive values of joyBaseMapped will increase the position, negative values will decrease the position)
   }
   
  }

    //**********GRIPPER SERVO CONTROL*********************/
   //absolute Mapping analog joystick value to servo  signal range
   servoIncrements[4] = map(analogValues[4], 0, 1023, SERVO_MINS[4], SERVO_MAXES[4]);
   servoPositions[4] = servoIncrements[4];//set servo position variable to the mapped value from the knob

  for(int i = 0; i < NUMBER_OF_SERVOS; i++)
  {
    servoPositions[i] = constrain(servoPositions[i], SERVO_MINS[i], SERVO_MAXES[i]);
  }
  
  for(int i = 0; i < NUMBER_OF_SERVOS; i++)
  {
    armServos[i].write(servoPositions[i]); 
  }

   delay(10);  //wait a short time to account for servo movement.
  
 }


