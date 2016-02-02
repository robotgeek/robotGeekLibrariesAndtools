

#include <Servo.h>

#define LEFT_SERVOPIN 3  //pin that the left servo will be attached to
#define RIGHT_SERVOPIN 5  //pin that the right servo will be attached to
#define CAMERA_SERVOPIN 6
#define GRIP_SERVOPIN 9  //pin that the micro servo will be attached to
#define WRIST_SERVOPIN 10  //pin that the large servo will be attached to
#define LEFT_FSR 0
#define RIGHT_FSR 1

Servo leftServo;  // create servo object to control left wheel continuous turn servo
Servo rightServo;  // create servo object to control right wheel continuous turn servo
Servo gripServo;   //create an servo object for the 9g FT-FS90MG micro servo
Servo wristServo;   //create an servo object for the RobotGeek 180 degree serco
Servo camServo;

int gripperServoValue;

void setup()
{
  leftServo.attach(LEFT_SERVOPIN);
  rightServo.attach(RIGHT_SERVOPIN);
  gripServo.attach(GRIP_SERVOPIN);
  wristServo.attach(WRIST_SERVOPIN);
  camServo.attach(CAMERA_SERVOPIN);
  
  
  rightServo.write(80);
  delay(1000);
  rightServo.write(100);
  delay(1000);
  
  rightServo.write(90);
  delay(500);
      
  leftServo.write(100);
  delay(1000);
  leftServo.write(80);
  delay(1000);
  leftServo.write(90);
      
  delay(500);
  gripServo.write(25);
  delay(1000);
  gripServo.write(180);
  delay(1000);
  gripServo.write(30);
  gripperServoValue = 30;
  delay(500);
  
  
      
  wristServo.write(120);
  delay(1000);
  
  wristServo.write(90);
  delay(500);
  
  
  camServo.write(120);
  delay(1000);
  camServo.write(65);
  delay(1000);
  camServo.write(90);
  
  
}




void loop()
{
  int analogLeftVal = analogRead(LEFT_FSR);
  delay(2);
  int analogRightVal = analogRead(RIGHT_FSR);
  
  if((analogLeftVal > 400 || analogRightVal > 400) && gripperServoValue < 180)
  {
    gripperServoValue = gripperServoValue + 1;
    
    gripServo.write(gripperServoValue);
  }
  else
  {
    if(gripperServoValue > 30)
    {
      gripperServoValue = gripperServoValue - 1;
      gripServo.write(gripperServoValue);
      
    }
  }
  
      
          
}


