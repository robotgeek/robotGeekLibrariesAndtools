/***********************************************************************************
 *
 *      __                 RobotGeek Foam Dart Gun Test
 *       \_____ 
 *       |      |          
 *       |______|=    =====>
 *         |  | 
 *        _|__|
 *       _|___|___
 *   _   |       |
 *  _|___|_______|_
 * 
 *  The following sketch will activate a single servo to fire the foam dart gun.
 *  The code will fire the gun once and only once. 
 *
 *  Wiring
 *
 *  DIO 9 - Black RobotGeek 180 Degree Servo  White -'S' Black -'G'
 *  
 *  Use an external power supply and set the jumper for pins 9/10/11 to 'VIN'
 *   
 *  For more information and wiring diagrams see
 *  http://learn.robotgeek.com/getting-started/29-desktop-roboturret/159-robotgeek-foam-dart-gun-getting-started-guide.html
 ***********************************************************************************/
#include <Servo.h>   //include the servo library to control the RobotGeek Servos

#define SERVOPIN 9        //pin that the large servo will be attached to

#define FIRE_POSITION 113 //default position the servo will move to in order to fire the dar gun  

Servo triggerServo;   //create an servo object for the RobotGeek 180 degree serco

//setup servo objects and set initial position
void setup()
{ 
  
  triggerServo.attach(SERVOPIN); //attach the trigger servo on pin SERVOPIN
  triggerServo.write(90);        //sets the servo position to 90 degress, centered
  delay(200); //wait 200ms

  triggerServo.write(FIRE_POSITION); // move the servo to FIRE_POSITION to fire the dart gun
  delay(300);     

  triggerServo.write(90);    // sets the servo position to 90 degress, centered

}
 
//repeat test process 
void loop()
{
  
  
}
 
 
 
 
 
