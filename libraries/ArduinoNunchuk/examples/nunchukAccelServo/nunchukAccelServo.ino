#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <Servo.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
Servo servoRoll, servoPitch;   //servo object

const int SERVO_PIN_ROLL = 3;
const int SERVO_PIN_PITCH = 5;


int servoPitchValue = 90; //servo position
int servoRollValue = 90; //servo position

void setup() 
{
  delay(100);
  nunchuk.init(); //start the wii classic interface
  delay(100);
  nunchuk.update(); //update the interface

  servoRoll.attach(SERVO_PIN_ROLL); //attach the servo on pin 3
  servoPitch.attach(SERVO_PIN_PITCH); //attach the servo on pin 3
  
}

void loop() 
{
  nunchuk.update();

  
  if(nunchuk.cButton == 1)
  {
    servoPitchValue = nunchuk.pitch;
    servoPitchValue = map(nunchuk.roll, -180, 180, 0, 180);
    servoRoll.write(servoRollValue);  //write the value to the servo
    servoPitch.write(servoPitchValue);  //write the value to the servo

  }


  delay(10);
}