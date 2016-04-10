/*
 * WiiClassy.h - Improved Wii Nunchuk library for Arduino
 * 
 * Copyright 2011-2012 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following projects/websites:
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 * 
 */

#ifndef RGSharpIR_H
#define RGSharpIR_H

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class WiiClassy
{  
  public:  
 //   int getRawStatus[4];
 //	  int getRawButtons[2];
  	int sensorType;

  
    void init(int initPin, int initSensorType);    

    int getCm();
    int getIn();
    int getRaw();
    
  private:  
  	int analogPin;
	int rawValue;
	float distanceCM;
	float distanceIn;

};

#endif
