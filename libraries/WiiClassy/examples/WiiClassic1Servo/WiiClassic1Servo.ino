#include "Wire.h"
#include "WiiClassy.h"
#include <Servo.h>

WiiClassy classy = WiiClassy();

int servo1Value = 90; //servo position

int leftStickXMapped; //value to hold the transformed joystick value 

Servo servo1;   //servo object

int spd = 10; //increase to incrase servo speed

void setup() 
{
  delay(100);
  classy.init(); //start the wii classic interface
  delay(100);
  classy.update(); //update the interface

  servo1.attach(3); //attach the servo on pin 3
  
}

void loop() 
{
  delay(20); // 1ms is enough to not overload the wii Classic, 100ms seems to ease the serial terminal a little
  classy.update();
    
  leftStickXMapped = map(classy.leftStickX, 0, 63, -spd, spd);  //the leftstickx value comes in as 0-63, it needs to be mapped to values from -spd to spd
  servo1Value = servo1Value + leftStickXMapped;  //add the mapped value to the servo value
  servo1Value = constrain(servo1Value, 0, 180);  //constrain the servo value to keep in between 0 and 180

  servo1.write(servo1Value);  //write the value to the servo
  
  

}
