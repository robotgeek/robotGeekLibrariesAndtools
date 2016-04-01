/*
 * ArduinoNunchuk Demo
 * 
 * Copyright 2011-2012 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 * 
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 9600

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(BAUDRATE);
  nunchuk.init();
}

void loop()
{
  nunchuk.update();
  
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
  Serial.print(" Z button:" );
  Serial.print(nunchuk.zButton, DEC);
  Serial.print(" C button:" );
  Serial.println(nunchuk.cButton, DEC);

  delay(500);
}
