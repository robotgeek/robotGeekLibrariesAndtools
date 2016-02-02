/***********************************************************************************
 *     ______            RobotGeek Desktop RoboTurret v3         ______
 *      |  |                    Test Code                         |  | 
 *      |__|_                                                    _|__|
 *   ___|____|_                                                 _|___|___
 *    |       |    _                                        _   |       |
 *   _|_______|____|_                                      _|___|_______|_
 * 
 *  The following sketch will test the Desktop RoboTurret by executing the following actions:
 *    1) Move the servos to a center position and turn off the laser
 *    2) Move the Pan servo from left to right, then center
 *    3) Move the Tilt Servo from back to front, then to center
 *    4)Blink the Laser 2 times.
 *
 *  Wiring
 *    Pan Servo - Digital Pin 10 
 *    Tilt Servo - Digital Pin 11 
 *    Laser - Digital Pin 2
 *   
 ***********************************************************************************/
//Includes
#include <Servo.h>           //include the servo library for working with servo objects

//Defines
#define PAN 10              //Pan Servo Digital Pin
#define TILT 11             //Tilt Servo Digital Pin
#define LASER 2             //Laser Digital Pin

Servo panServo, tiltServo;  // create servo objects to control the pan and tilt servos

int panValue = 90;   //current positional value being sent to the pan servo. 
int tiltValue = 90;  //current positional value being sent to the tilt servo. 

//State Variables
int laserState = HIGH;         //The current state of the laser module

void setup() 
{ 
  
  //initialize servos
  panServo.attach(PAN);  // attaches/activates the pan servo on pin PAN 
  tiltServo.attach(TILT);  // attaches/activates the tilt servo on pin TILT 

  //initalize digital pins
  pinMode(LASER, OUTPUT);      //set the LASER Pin to an output
  digitalWrite(LASER,LOW);
  
  //write initial servo positions to set the servos to 'home'
  panServo.write(90);  //sets the pan servo position to the default 'home' value
  tiltServo.write(90);//sets the tilt servo position to the default 'home' value
  delay(2000);
} 

void loop() 
{ 
  
  panServo.write(0);
  delay(1000);
  for(int i = 0; i< 180;i++)
  {
    panServo.write(i);
    delay(15);
  }
  for(int i = 180; i> 0;i--)
  {
    panServo.write(i);
    delay(15);
  }
  
  panServo.write(90);
  
  
  delay(1500);
  
  tiltServo.write(0);
  delay(1000);
  
  for(int i = 0; i< 180;i++)
  {
    tiltServo.write(i);
    delay(15);
  }
  for(int i = 180; i> 0;i--)
  {
    tiltServo.write(i);
    delay(15);
  }
  
  tiltServo.write(90);
  delay(1500);

  digitalWrite(LASER, LOW);
  delay(1000);
  digitalWrite(LASER, HIGH);
  delay(1000);
  digitalWrite(LASER, LOW);
  delay(1000);
  digitalWrite(LASER, HIGH);
  delay(1000);


} //end loop()


