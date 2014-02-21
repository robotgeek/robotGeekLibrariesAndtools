/**********************************
 *rfiduino.h
 *
 *RFIDuino Library v1.0
 *
 *Trossen Robotics/RobotGeek.com
 *
 *Header file for the RFIDuino Library
 *http://www.trossenrobotics.com/rfiduino
 *http://www.trossenrobotics.com/rfiduino/library-documentation
 *
 **********************************/

#ifndef RFIDuino_h //load header if we have not defined RFIDuino_h
#define RFIDuino_h //define RFIDuino_h, to prevent code being loaded if this library is loaded a second time


#include "Arduino.h"

#define DELAYVAL    320  //384 //standard delay for manchster decode
#define TIMEOUT     1000  //standard timeout for manchester decoe

//Pin assingments for RFIDuino 1.0
#define   MOD     	   6 
#define   SHD     	   7 
#define   DEMOD_OUT    8  
#define   RDY_CLK      4  
#define   BUZZER 	   5

class RFIDuino
{
	public:
	RFIDuino();
	bool decodeTag(unsigned char *buf);
	void errorSound(int buzzer =BUZZER); 
	void successSound(int buzzer =BUZZER); 
	void transferToBuffer(byte *tag_data, byte *tag_data_buffer);
	bool compareTagData(byte *tag_data_1,byte *tag_data_2);
	
};




#endif
