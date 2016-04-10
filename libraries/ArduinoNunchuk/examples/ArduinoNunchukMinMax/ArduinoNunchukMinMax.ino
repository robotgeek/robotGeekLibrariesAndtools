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

unsigned long lastReportTime;
int reportInterval = 1000;

int joyXMin = 10000;
int joyXMax;
int joyYMin = 10000;
int joyYMax;

int accXMin = 10000;
int accXMax;
int accYMin = 10000;
int accYMax;
int accZMin = 10000;
int accZMax;

int pitchMin = 10000;
int pitchMax;
int rollMin = 10000;
int rollMax;



void setup()
{
  Serial.begin(9600);  //start serial at 9600 bps
  nunchuk.init();      //initialize nunchuk instance. Nunchuk must be plugged in at startup for it to work.
  delay(100);          //short wait before initial read
  nunchuk.update();    //try to update local nunchuk variables from the nunchuk
}

void loop()
{
  nunchuk.update();    //try to update local nunchuk variables from the nunchuk

  if(nunchuk.analogX == 0)
  {
    Serial.println("ZERO");
  }

  joyXMax = max(joyXMax,nunchuk.analogX);
  joyXMin = min(joyXMin,nunchuk.analogX);
  joyYMax = max(joyYMax,nunchuk.analogY);
  joyYMin = min(joyYMin,nunchuk.analogY);

  accXMax = max(accXMax,nunchuk.accelX);
  accXMin = min(accXMin,nunchuk.accelX);
  accYMax = max(accYMax,nunchuk.accelY);
  accYMin = min(accYMin,nunchuk.accelY);
  accZMax = max(accZMax,nunchuk.accelZ);
  accZMin = min(accZMin,nunchuk.accelZ);
  
  rollMax = max(rollMax,nunchuk.roll);
  rollMin = min(rollMin,nunchuk.roll);
  pitchMax = max(pitchMax,nunchuk.pitch);
  pitchMin = min(pitchMin,nunchuk.pitch);

  
  if(millis() - lastReportTime > reportInterval)
  {
      
    //print all nunchuk data
    Serial.print("Joy X Min:" );
    Serial.print(joyXMin);
    Serial.print(" Joy X Max:" );
    Serial.print(joyXMax);
    Serial.print(" Joy Y Min:" );
    Serial.print(joyYMin);
    Serial.print(" Joy Y Max:" );
    Serial.print(joyYMax);
  
    Serial.print(" Acc X Min:" );
    Serial.print(accXMin);
    Serial.print(" Acc X Max:" );
    Serial.print(accXMax);
    Serial.print(" Acc Y Min:" );
    Serial.print(accYMin);
    Serial.print(" Acc Y Max:" );
    Serial.print(accYMax);
    Serial.print(" Acc Z Min:" );
    Serial.print(accZMin);
    Serial.print(" Acc Z Max:" );
    Serial.print(accZMax);
  
    Serial.print(" Roll Min:" );
    Serial.print(rollMin);
    Serial.print(" Roll Max:" );
    Serial.print(rollMax);  
    Serial.print(" pitch Min:" );
    Serial.print(pitchMin);
    Serial.print(" pitch Max:" );
    Serial.println(pitchMax);

    lastReportTime = millis();
  }
  
  delay(20); //delay to slow serial monitor
}
