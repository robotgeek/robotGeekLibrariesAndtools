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
 *  The following sketch send a signal to pin 9 of the Geekduino/Arduino's pins to
 *  that sets the attached servo to 150 degrees. This will set the servo correctly 
 *  for assembly of the gripper
 *
 *  Servo
 *    This tool is meant for use with the blue micro servo (FT-FS90MG) that came with the
 *    RobotGeek Gripper. This sketch should NOT be used to center RobotGeek Servos.
 *    
 *  Wiring
 *    A servo should be connected to pin 9 on the sensor shield. The orange cable 
 *    will plug into the 'S' port, the red cable will plug into 'V' and the brown 
 *    cable will plug into 'G'
 *
 *    For the centering process, the power jumpers should be set to '5v'
 *
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

#define SERVOPIN 9  //pin that the servo will be attached to

Servo servoToSet;   //create an array of servos with 6 elements, one for each PWM pin


void setup()
{ 
  servoToSet.attach(SERVOPIN);
  servoToSet.write(150);    // sets the servo position to 150 degress, positioning the servo for the gripper
}
 
void loop()
{
  //Once the program uses '.write()' to send a signal to the pin, it will maintain that signal until the unit is powered off or a new signal is sent with '.write()'
}
 
 
 
 
 
