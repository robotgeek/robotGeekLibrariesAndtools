/*
 * WiiClassy.cpp - Improved Wii Classic/Pro library for Arduino
 * 		Works with 3rd party controllers using unencrypted comm
 * 
 *
 * Based on the following projects/websites:
 *	 http://playground.arduino.cc/Main/WiiClassicController10
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 * 	 http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *	 http://www.wiili.org/index.php/Wiimote/Extension_Controllers/Classic_Controller
 */

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <Wire.h>
#include "WiiClassy.h"

#define ADDRESS 0x52
#define DEFAULT_UPDATE_INTERVAL 33
//#define REPORT_ON_HOLD

//initialize with manually update interval
void WiiClassy::init( int initUpdateInterval)
{      
  updateInterval = initUpdateInterval;  //set the update interval manually
  Wire.begin();
  cnt = 0;
   // transmit to device (byte)0x52
  WiiClassy::_sendByte(0x55, 0xF0);
  WiiClassy::_sendByte(0x00, 0xFB); 
  Wire.endTransmission ();    // stop transmitting
  // Set button bytes to default of 11111111, all buttons are 0 upon press.
  lastButtons[0] = (unsigned char)0xff;
  lastButtons[1] = (unsigned char)0xff;
  buttons[0] = (unsigned char)0xff;
  buttons[1] = (unsigned char)0xff;
  
  WiiClassy::update();
}


//initialize with default update interval
void WiiClassy::init()
{  
  init(DEFAULT_UPDATE_INTERVAL);
}



    
void WiiClassy::update()
{ 
  if(millis() - lastReadTime > updateInterval)
  {

    Wire.requestFrom (ADDRESS, 6); //request data from wii classic
    
  	while (Wire.available ()) {
      // read byte as an integer
  		if (cnt < 4) {
  			status[cnt] = Wire.read();
  		} else {
  			lastButtons[cnt-4] = buttons[cnt-4];
  			buttons[cnt-4] = Wire.read();
  		}
  		cnt++;
      }
      if (cnt > 5) {
  		WiiClassy::_sendByte(0x00, 0x00);
  		cnt = 0;                   
       }
  	
  		//Reference for this found here: http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller
  		
    leftShoulderPressed = _PressedRowBit(0,5);
    rightShoulderPressed = _PressedRowBit(0,1);
    lzPressed = _PressedRowBit(1,7);
    rzPressed = _PressedRowBit(1,2);
    leftDPressed = _PressedRowBit(1,1);
    rightDPressed = _PressedRowBit(0,7);
    upDPressed = _PressedRowBit(1,0);
    downDPressed = _PressedRowBit(0,6);
    selectPressed = _PressedRowBit(0,4);
    homePressed = _PressedRowBit(0,3);
    startPressed = _PressedRowBit(0,2);
    xPressed = _PressedRowBit(1,3);
    yPressed = _PressedRowBit(1,5);
    aPressed = _PressedRowBit(1,4);
    bPressed = _PressedRowBit(1,6);
    rightShoulderPressure = (status[3] & (unsigned char)0x1f); //rightmost 5 bits
    leftShoulderPressure = ((status[2] & (unsigned char)0x60) >> 2) + ((status[3] & (unsigned char)0xe0) >> 5); //'leftish' bits
    leftStickX = (status[0] & (unsigned char)0x3f); //rightmost 6 bits
    leftStickY = (status[1] & (unsigned char)0x3f); //rightmost 6 bits      
    rightStickX = ((status[0] & (unsigned char)0xc0) >> 3) + ((status[1] & (unsigned char)0xc0) >> 5) +  ((status[2] & (unsigned char)0x80) >> 7); //bits. They're there.
    rightStickY = (status[2] & (unsigned char)0x1f);    //rightmost 5 bits  

    lastReadTime = millis();// update timer for next update
  }
}


 bool WiiClassy::_PressedRowBit(int row, int bit) {
        int mask = (1 << bit);
        #ifdef REPORT_ON_HOLD
        return (!(buttons[row] & mask )) && (lastButtons[row] & mask);
        #else
        return (!(buttons[row] & mask ));
        #endif
    }


void WiiClassy::_sendByte(int data, int location)	{  
  Wire.beginTransmission(ADDRESS);
  
  #if (ARDUINO >= 100)
    Wire.write(location);
    Wire.write(data);  
  #else
    Wire.send(location);
    Wire.send(data); 
  #endif
  
  Wire.endTransmission();
  delay(10);
}
