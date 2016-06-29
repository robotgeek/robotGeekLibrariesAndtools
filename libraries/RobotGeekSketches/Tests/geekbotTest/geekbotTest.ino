/***********************************************************************************
 *    _                     RobotGeek Geekbot Rover
 *  _|_|______________      
 *   |___         |
 *  _/ . \ _______|_
 *   \___/      \_/
 *
 *  The
 *
 *    
 *  Wiring
 *    
 *    Right Servo - Digital Pin 9
 *    Left Servo - Digital Pin 10
 *    Scanning Servo - Digital Pin 11
 *    IR Sensor - Analog Pin 0
 *    Jumper for pins 9/10/11 should be set to 'VIN'
 *    Jumper for pins 3/5/6 should be set to '5V'
 *
 *  Control Behavior:
 *
 *  External Resources
 *
 ***********************************************************************************/
//Includes
#include <Servo.h> //include servo library to control continous turn servos

//servo speed
//95 deg - 125 deg full ccw
//85 deg - 55 deg full cw


#define PAN_SERVO_PIN 12
#define WRIST_SERVO_PIN 6
#define GRIPPER_SERVO_PIN 9
#define LEFT_SERVO_PIN 10
#define RIGHT_SERVO_PIN 11

#define BUZZER_PIN 2
#define LED_RIGHT_PIN 4
#define LED_LEFT_PIN 7
#define BUTTON_PIN 8

#define DISTANCE_SENSOR_PIN 0



#define CW_MIN_SPEED 1400 //increase if the rover is drifting left
#define CW_MAX_SPEED 1000 //increase if the rover is drifting left

#define CCW_MIN_SPEED 1600 //decrease if the rover is drifting right
#define CCW_MAX_SPEED 2000 //decrease if the rover is drifting right

#define SERVO_STOP 1500
  
Servo servoPan, servoWrist, servoGripper, servoLeft, servoRight;


int servoSpeedLeft;
int servoSpeedRight;
  
int roverSpeed = 1;  

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting Geekbot Test");
  //basic drive servos
  servoLeft.attach(LEFT_SERVO_PIN); 
  servoRight.attach(RIGHT_SERVO_PIN);
  servoLeft.write(SERVO_STOP); //write 1500us, servo stopped
  servoRight.write(SERVO_STOP); //write 1500us, servo stopped
  
  
  //Pan servo for servo sensor
  servoPan.attach(PAN_SERVO_PIN);                    //attach pan 9g microservo
  servoPan.write(1500);  //write 1500us, 90 degrees
  
  //gripper and wrist angle
  servoWrist.attach(WRIST_SERVO_PIN, 1000, 2000);    //attach with limits
  servoGripper.attach(GRIPPER_SERVO_PIN, 750, 2400); //attach with limits, lower limit makes sure gripper doesn't burn out
  servoWrist.write(1500); //write 1500us, servo stopped
  servoGripper.write(1500);  //write 1500us, servo stopped
  
  pinMode(LED_RIGHT_PIN, OUTPUT);
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);


  Serial.println("Testing Left Servo");
  servoLeft.writeMicroseconds(CW_MIN_SPEED);
  delay(1000);
  servoLeft.writeMicroseconds(CW_MAX_SPEED);
  delay(1000);
  servoLeft.writeMicroseconds(CCW_MIN_SPEED);
  delay(1000);
  servoLeft.writeMicroseconds(CCW_MAX_SPEED);
  delay(1000);
  servoLeft.writeMicroseconds(SERVO_STOP);
  delay(1000);
  
  Serial.println("Testing Right Servo");
  servoRight.writeMicroseconds(CW_MIN_SPEED);
  delay(1000);
  servoRight.writeMicroseconds(CW_MAX_SPEED);
  delay(1000);
  servoRight.writeMicroseconds(CCW_MIN_SPEED);
  delay(1000);
  servoRight.writeMicroseconds(CCW_MAX_SPEED);
  delay(1000);
  servoRight.writeMicroseconds(SERVO_STOP);
  delay(1000);
  
  
  
  Serial.println("Testing Pan Servo");
  servoPan.writeMicroseconds(2000);
  delay(1000);
  servoPan.writeMicroseconds(1000);
  delay(1000);
  servoPan.writeMicroseconds(1500);
  delay(1000);
  
  
  
  Serial.println("Testing Buzzers and LEDs");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);  
  digitalWrite(LED_RIGHT_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_RIGHT_PIN, LOW);  
  digitalWrite(LED_LEFT_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_LEFT_PIN, LOW);  
  
  
  
  
  Serial.println("Begin Button and IR sensor Test");
  
}

void loop()
{
  if(digitalRead(BUTTON_PIN) == HIGH)
  {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);  
  }
 
  Serial.print("Analog Sensor:");
  Serial.println(analogRead(DISTANCE_SENSOR_PIN));
  delay(10);
 
}

