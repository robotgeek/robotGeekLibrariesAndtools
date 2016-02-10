#include "Wire.h"
#include "WiiClassy.h"
#include <Servo.h>

WiiClassy classy = WiiClassy();

int servo1Value = 90; //servo position
int servo2Value = 90; //servo position
int servo3Value = 90; //servo position
int servo4Value = 90; //servo position
int servo5Value = 90; //servo position

int leftStickXMapped; //value to hold the transformed joystick value 
int rightStickXMapped; //value to hold the transformed joystick value 
int leftStickYMapped; //value to hold the transformed joystick value 
int rightStickYMapped; //value to hold the transformed joystick value 

Servo servo1;   //servo object
Servo servo2;   //servo object
Servo servo3;   //servo object
Servo servo4;   //servo object
Servo servo5;   //servo object

int spd = 10; //increase to increase servo speed

void setup() 
{
  delay(100);
  classy.init(); //start the wii classic interface
  delay(100);
  classy.update(); //update the interface

  servo1.attach(3); //attach the servo on pin 3
  servo2.attach(5); //attach the servo on pin 5
  servo3.attach(6); //attach the servo on pin 6
  servo4.attach(9); //attach the servo on pin 9
  servo5.attach(10); //attach the servo on pin 10
  
}

void loop() 
{
  delay(20); // 1ms is enough to not overload the wii Classic, 100ms seems to ease the serial terminal a little
  classy.update();
    
  leftStickXMapped = map(classy.leftStickX, 0, 63, -spd, spd);  //the leftstickx value comes in as 0-63, it needs to be mapped to values from -spd to spd
  servo1Value = servo1Value + leftStickXMapped;  //add the mapped value to the servo value
  servo1Value = constrain(servo1Value, 0, 180);  //constrain the servo value to keep in between 0 and 180

  servo1.write(servo1Value);  //write the value to the servo

  
    
  leftStickYMapped = map(classy.leftStickY, 0, 63, -spd, spd);  //the leftstickx value comes in as 0-63, it needs to be mapped to values from -spd to spd
  servo2Value = servo2Value + leftStickYMapped;  //add the mapped value to the servo value
  servo2Value = constrain(servo2Value, 0, 180);  //constrain the servo value to keep in between 0 and 180

  servo2.write(servo2Value);  //write the value to the servo


  
    
  rightStickXMapped = map(classy.rightStickX, 0, 31, -spd, spd);  //the leftstickx value comes in as 0-63, it needs to be mapped to values from -spd to spd
  servo3Value = servo3Value + rightStickXMapped;  //add the mapped value to the servo value
  servo3Value = constrain(servo3Value, 0, 180);  //constrain the servo value to keep in between 0 and 180

  servo3.write(servo3Value);  //write the value to the servo


  
    
  rightStickYMapped = map(classy.rightStickY, 0, 31, -spd, spd);  //the leftstickx value comes in as 0-63, it needs to be mapped to values from -spd to spd
  servo4Value = servo4Value + rightStickYMapped;  //add the mapped value to the servo value
  servo4Value = constrain(servo4Value, 0, 180);  //constrain the servo value to keep in between 0 and 180

  servo4.write(servo4Value);  //write the value to the servo

  
    
  if (classy.leftShoulderPressed) {
  servo5Value = servo5Value + spd;
  }
  if (classy.rightShoulderPressed) {
  
  servo5Value = servo5Value - spd;
  }

  servo5Value = constrain(servo5Value, 0, 110);  //constrain the servo value to keep in between 0 and 110 for the gripper

  servo5.write(servo5Value);  //write the value to the servo


  
  
  

}
