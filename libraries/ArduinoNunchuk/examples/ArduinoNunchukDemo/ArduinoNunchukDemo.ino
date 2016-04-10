/*
 * ArduinoNunchuk Demo
 * 
 * 2016 Updated by TrossenRobotics/RobotGeek
 * 
 * Copyright 2011-2012 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 * 
 */

#include <Wire.h>            //include wire/IIC library
#include <ArduinoNunchuk.h>  //include nunchuk library

ArduinoNunchuk nunchuk = ArduinoNunchuk();  //start nunchuk instance

void setup()
{
  Serial.begin(9600);  //start serial at 9600 bps
  nunchuk.init();      //initialize nunchuk instance. Nunchuk must be plugged in at startup for it to work.
}

void loop()
{
  nunchuk.update();    //try to update local nunchuk variables from the nunchuk
  
  //print all nunchuk data
  Serial.print(" X Axis:" );
  Serial.print(nunchuk.analogX, DEC);
  Serial.print(" Y Axis:" );
  Serial.print(nunchuk.analogY, DEC);
  Serial.print(" Acc X:" );
  Serial.print(nunchuk.accelX, DEC);
  Serial.print(" Acc Y:" );
  Serial.print(nunchuk.accelY, DEC);
  Serial.print(" Acc Z:" );
  Serial.print(nunchuk.accelZ, DEC);
  Serial.print(" Pitch:" );
  Serial.print(nunchuk.pitch, DEC);
  Serial.print(" Roll:" );
  Serial.print(nunchuk.roll, DEC);
  Serial.print(" Z button:" );
  Serial.print(nunchuk.zButton, DEC);
  Serial.print(" C button:" );
  Serial.println(nunchuk.cButton, DEC);

  delay(20); //delay to slow serial monitor
}
