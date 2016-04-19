#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <Servo.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
Servo servo1;   //servo object

const int SERVO_PIN = 3;
//low/high for deadzone - anything between these numbers will not move the servo
const int DEADBAND_LOW = 108;
const int DEADBAND_HIGH = 148;

const int SERVO_MIN_PULSE = 600;   //minimum servo pulse in microceconds (0 degrees)
const int SERVO_MAX_PULSE = 2400;  //maximum servo pulse in microceconds (180 degrees)
const int SERVO_CENTER_PULSE = 1500; //centered servo pulse in microceconds (90 degrees)

int servo1Value = 1500; //servo position
int servoIncrement;

int leftStickXMapped; //value to hold the transformed joystick value 

int spd = 50; //increase to increase servo speed


void setup() 
{
  delay(100);
  nunchuk.init(); //start the wii classic interface
  delay(100);
  nunchuk.update(); //update the interface

  servo1.attach(SERVO_PIN); //attach the servo on pin 3
  
}

void loop() 
{
  nunchuk.update();

  if(nunchuk.analogY > DEADBAND_HIGH || nunchuk.analogY < DEADBAND_LOW )
  {
    servoIncrement = map(nunchuk.analogY, 0, 255, -spd, spd);
    servo1Value = servo1Value + servoIncrement;  //add the mapped value to the servo value
    servo1Value = constrain(servo1Value, SERVO_MIN_PULSE, SERVO_MAX_PULSE);  //constrain the servo value to keep in between 0 and 180
  }
    
  servo1.writeMicroseconds(servo1Value);  //write the value to the servo
  delay(10);
}