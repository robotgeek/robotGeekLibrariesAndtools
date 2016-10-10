/****************************************************************************************************
* rfiduino.h - RFIDuino Library Header File
*
* RFIDuino Library v1.2 by TrossenRobotics / RobotGeek
*
*	This Library enables a Geekduino/Arduino to work with the RobotGeek RFIDuino Shield.
*	Using the sheild and this library a user can detect a card, read/decode the card,
*	compare the read to previous reads, and intearct with the inbord buzzer.
*
* Links
*    RFIDuino Getting Started Guide
*      http://learn.robotgeek.com/getting-started/41-rfiduino/142-rfiduino-getting-started-guide.html
*    RFIDuino Library Documentation
*      http://learn.robotgeek.com/41-rfiduino/144-rfiduino-library-documentation.html
*    RFIDuino Shield Product Page
*      http://www.robotgeek.com/rfiduino
*
*
* Trossen Robotics/RobotGeek.com
*
* Header file for the RFIDuino Library
*  http://learn.robotgeek.com/getting-started/41-rfiduino/142-rfiduino-getting-started-guide.html
*  http://learn.robotgeek.com/41-rfiduino/144-rfiduino-library-documentation.html
*
****************************************************************************************************/

#include "Arduino.h"

#ifndef RFIDuino_h //load header if we have not defined RFIDuino_h
#define RFIDuino_h //define RFIDuino_h, to prevent code being loaded if this library is loaded a second time

#define DELAYVAL    320   //384 //standard delay for manchster decode
#define TIMEOUT     1000  //standard timeout for manchester decode

class RFIDuino
{
	public:

		RFIDuino(float verison);
		//i/o
		void errorSound(); 					//play an error sound to the buzzer
		void successSound(); 				//play a sucess sound ot the buzzer

		//low level deocde functions
		bool decodeTag(unsigned char *buf);	//low level tag decode
		void transferToBuffer(byte *tagData, byte *tagDataBuffer);	//transfer data from one array to another
		bool compareTagData(byte *tagData1, byte *tagData2);			//compate 2 arrays

		//higher level tag scanning / reporting
		bool scanForTag(byte *tagData);

		//user output pin values, variables as they will change depending on which hardware is used
		int buzzer;
		int led1;
		int led2;

	private:

		//pins to connect Arduino to the EM4095 chip , variables as they will change depending on which hardware is used
		int demodOut;
		int shd;
		int mod;
		int rdyClk;

};

#endif
