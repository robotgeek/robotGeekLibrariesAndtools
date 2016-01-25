/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Set Servo Degrees
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code will set the positions on a servo using servo.write()
 *  
 *  Digital 3 - RobotGeek Servo
 *  Analog 0 - RobotGeek Rotation Knob or other Analog Input
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Servo Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/233-servo-primer.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  servo.writeMicroseconds()
 *  map()
 *****************************************************************************************/
#include <Servo.h>

const int ANALOG_PIN = 0;
const int SERVO_PIN = 3;      //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int SERVO_MIN_PULSE = 600;
const int SERVO_MAX_PULSE = 2400;
const int SERVO_CENTER_PULSE = 1500;

int analogSensorValue;    //the raw value read from the analog sensor
int servoValue;           //holds the current PWM value (0-255)
int degreeValue;          //value in degrees

Servo servo1;             //create servo object, 'servo1'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  servo1.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
  Serial.begin(9600);
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 
  
  servoValue = map(analogSensorValue, 0, 1023, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  //the map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values
  degreeValue = map(servoValue, SERVO_MIN_PULSE, SERVO_MAX_PULSE, 0, 180);  //the map functions converts a number from one range to another, so the analog input is mapped to the servo microsecond values
  servo1.write(degreeValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input
  
  Serial.print("Raw Analog Value:");
  Serial.print(analogSensorValue);
  Serial.print("| Mapped Value for Servo:");
  Serial.print(servoValue);
  Serial.print("uS ");
  Serial.print("| Mapped Value in degrees:");
  Serial.print(degreeValue);
  Serial.println("degrees");
  
  delay(100);  //short delay to account for servo movement
  
}//go back to the first line in loop()
