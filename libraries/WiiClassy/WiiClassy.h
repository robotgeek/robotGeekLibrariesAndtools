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

#ifndef WiiClassy_H
#define WiiClassy_H

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
	bool leftShoulderPressed;
	bool rightShoulderPressed;
	bool lzPressed;
	bool rzPressed;
	bool leftDPressed;
	bool rightDPressed;
	bool upDPressed;
	bool downDPressed;
	bool selectPressed;
	bool homePressed;
	bool startPressed;
	bool xPressed;
	bool yPressed;
	bool aPressed;
	bool bPressed;
	int rightShoulderPressure;
	int leftShoulderPressure;
	int leftStickX;
	int leftStickY;
	int rightStickX;
	int rightStickY;
  
    void init();    
    void init(int initUpdateInterval);    
    void update();
    
  private:  
    void _sendByte(int data, int location);
	bool _PressedRowBit(int data, int location);
    unsigned char cnt;
    int status[4];              // array to store wiiclassic output
    int buttons[2];
    int lastButtons[2];	
	unsigned long lastReadTime;
	int updateInterval;

};

#endif
