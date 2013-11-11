/***********************************************************************************
 *   ___________
 *  |     __    |           RobotGeek Servo Centering Tool
 *  |   /    \  |
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|
 *
 *  The following sketch send a signal to all 6 of the Geekduino/Arduino's pins to
 *  that sets any attached servo to 90 degrees, centering the servo.
 *    
 *  Wiring
 *    A servo can be connected to any of the PWM ports: 3,5,6,9,10 or 11
 *    Mutiple servos can be centered at one time, but the number of servos you can attach
 *    may be limited by your power supply. For best performance limit 
 *    testing to one servo at a time. 
 *    For the centering process, the power jumpers should be set to '5v' if you are powering
 *    the Geekduino/Arduino from USB. 
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

Servo servoToCenter[6];   //create an array of servos with 6 elements, one for each PWM pin

int servoPins[] = {3,5,6,9,10,11};  //create an array of 6 ints holding the pin numbers for the PWM pins
 
void setup()
{ 
  //iterate from 0->6. For each pin attach the servo and set it to 90 degrees
  for(int i = 0; i < 6; i++)
  {
    servoToCenter[i].attach(servoPins[i]);    //attach pan servo object on pin i
    servoToCenter[i].write(90);               // sets the servo position to 90 degress, the center of the servo. This will also serve as 'stopped' for continous rotation servos
  }
}
 
void loop()
{
  //Once the program uses '.write()' to send a signal to the pin, it will maintain that signal until the unit is powered off or a new signal is sent with '.write()'
}
 
 
 
 
 
