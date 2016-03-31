/*
WiiClassic LED Code

*/

#include <Wire.h>       //include the Wire/I2C Library
#include <WiiClassy.h>  //include the WiiClassy Libary

WiiClassy classy = WiiClassy(); //start an instance of the WiiClassy Library

const int BUZZER_PIN = 3;
const int LEFT_STICK_MIN = 0;
const int LEFT_STICK_MAX = 63;
const int RIGHT_STICK_MIN = 0;
const int RIGHT_STICK_MAX = 31;
const int FREQ_MIN = 31;
const int FREQ_MAX = 65535;


int frequency;

void setup() 
{
  classy.init();  //start classy library
  delay(100);
  classy.update();  //read data from the classic controller
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() 
{
  
  classy.update();//read data from the classic controller
  
  //read the left joystick and then map it from 0-63 to 0-255 for the PWM led
  //pwmLEDValue = map(classy.leftStickY, LEFT_STICK_MIN, LEFT_STICK_MAX, PWM_MIN ,PWM_MAX);
  

  Serial.print(" left stick x: ");
  Serial.print(classy.leftStickX);
  
  Serial.print(" left stick y: ");
  Serial.print(classy.leftStickY);
  
  Serial.print(" right stick x: ");
  Serial.print(classy.rightStickX);
  
  Serial.print(" right stick y: ");
  Serial.print(classy.rightStickY);
  
  
  Serial.print("Buttons:");
  
  
  
  if (classy.leftShoulderPressed == true) {
    frequency = 30;
  }
  if (classy.rightShoulderPressed == true) {
    frequency = 1500;
  }
  if (classy.lzPressed == true) {
    frequency = 3000;
  }
  if (classy.rzPressed == true) {
    frequency = 4000;
  }
  if (classy.leftDPressed == true) {
    frequency = 5000;
  }
  
  if (classy.rightDPressed == true) {
    frequency = 7000;
  }
  
  if (classy.upDPressed == true) {
    frequency = 8000;
  }
  if (classy.downDPressed == true) {
    frequency = 9000;
  }
  
  if (classy.selectPressed == true) {
    frequency = 11000;
  }
  
  if (classy.homePressed == true) {
    frequency = 13000;
  }
  if (classy.startPressed == true) {
    frequency = 14000;
  }
  
  if (classy.xPressed == true) {
    frequency = 15000;
  }
  
  if (classy.yPressed == true) {
    frequency = 16000;
  }
  
  if (classy.aPressed == true) {
    frequency = 17000;
  }
  
  if (classy.bPressed == true) {
    frequency = 18000;
  }
  
  tone(BUZZER_PIN, frequency);
  
  
  

}
