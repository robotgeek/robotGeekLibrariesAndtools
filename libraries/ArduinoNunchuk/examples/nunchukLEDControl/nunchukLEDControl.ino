/*
Nunchuk LED Code

*/


#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

const int DIGTIAL_LED = 13;
const int PWM_LED = 3;



int pwmLEDValue;

void setup() 
{
  nunchuk.init();  //start classy library
  delay(100);
  nunchuk.update();  //read data from the classic controller
  pinMode(DIGTIAL_LED, OUTPUT);
  pinMode(PWM_LED, OUTPUT);
}

void loop() 
{
  
  nunchuk.update();//read data from the classic controller
  

  //the joystick is already 0-255, so we can write it directly to PWM

  analogWrite(PWM_LED, nunchuk.analogY);  //write the PWM value to the LED

  //if a is pressed, turn the digital LED on
  if (nunchuk.zButton  == true) 
  {
    digitalWrite(DIGTIAL_LED, HIGH);
  }
  
  //if b is pressed, turn the digital LED off
  if (nunchuk.cButton  == true) 
  {
    digitalWrite(DIGTIAL_LED, LOW);
  }
  
  

}
