/*
WiiClassic LED Code

*/

#include <Wire.h>       //include the Wire/I2C Library
#include <WiiClassy.h>  //include the WiiClassy Libary

WiiClassy classy = WiiClassy(); //start an instance of the WiiClassy Library

const int DIGTIAL_LED = 13;
const int PWM_LED = 3;
const int LEFT_STICK_MIN = 0;
const int LEFT_STICK_MAX = 63;
const int RIGHT_STICK_MIN = 0;
const int RIGHT_STICK_MAX = 31;
const int PWM_MIN = 0;
const int PWM_MAX = 255;


int pwmLEDValue;

void setup() 
{
  classy.init();  //start classy library
  delay(100);
  classy.update();  //read data from the classic controller
  pinMode(DIGTIAL_LED, OUTPUT);
  pinMode(PWM_LED, OUTPUT);
}

void loop() 
{
  
  classy.update();//read data from the classic controller
  
  //read the left joystick and then map it from 0-63 to 0-255 for the PWM led
  pwmLEDValue = map(classy.leftStickY, LEFT_STICK_MIN, LEFT_STICK_MAX, PWM_MIN ,PWM_MAX);
  
  //uncomment the next line to use the right joystick
  //pwmLEDValue = map(classy.rightStickY), RIGHT_STICK_MIN, RIGHT_STICK_MAX, PWM_MIN ,PWM_MAX); 
  
  analogWrite(PWM_LED, pwmLEDValue);  //write the PWM value to the LED

  //if a is pressed, turn the digital LED on
  if (classy.aPressed  == true) 
  {
    digitalWrite(DIGTIAL_LED, HIGH);
  }
  
  //if b is pressed, turn the digital LED off
  if (classy.bPressed  == true) 
  {
    digitalWrite(DIGTIAL_LED, LOW);
  }
  
  

}
