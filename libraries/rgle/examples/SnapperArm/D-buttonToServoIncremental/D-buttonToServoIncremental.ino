/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Analog To Servo - Incremental
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code is intended for use with the RobotGeek Snapper Arm and the RobotGeek
 *   curriculum.
 *  
 *  This code will set the positions on a servo using servo.write()
 *  based on the input from an analog sensor. It will use the analog input from the third 
 *  joystick (analog pin 3) and target the wrist servo on the arm (digital pin 9).
 *  
 *  This code will take into account the physical properties of a joystick by incrementally
 *  adjusting the servo. This means that when the joystick is centered, the servo will stay
 *  at its current positon. When the servo is moved, it will adjust the servos postion slowly.
 *  
 *  Digital 9 - RobotGeek Servo
 *  Analog 3 - RobotGeek Rotation Knob or other Analog Input
 *  
 * For a more in depth explanation of wiring,  this code and more information, see
 * http://learn.robotgeek.com/rgc/262-rgc-robotgeek-snapper-arm.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  servo.write()
 *  map()
 *****************************************************************************************/

#include <Servo.h>

const int BUTTON_PIN_1 = 2;           //button 1
const int BUTTON_PIN_2 = 4;           //button 2
const int SERVO_PIN = 9;            //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory

int servoValue = 90;           //holds the servo position (0-180)
int servoIncrement = 10;         //alter this value to change the speed of the system. Higher values mean higher speeds 5-500 approximate recommended range

Servo wristServo;             //create an instance of the servo class, 'wristServo'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  wristServo.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
    if(digitalRead(BUTTON_PIN_1) == HIGH)
    {
      servoValue = servoValue + servoIncrement;
      delay(1000);  //short delay to account for servo movement
    }
    else if(digitalRead(BUTTON_PIN_2) == HIGH)
    {
      servoValue = servoValue - servoIncrement;
      delay(1000);  //short delay to account for servo movement
    }

    servoValue = constrain(servoValue, 0, 180);
   wristServo.write(servoValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input

  
}//go back to the first line in loop()
