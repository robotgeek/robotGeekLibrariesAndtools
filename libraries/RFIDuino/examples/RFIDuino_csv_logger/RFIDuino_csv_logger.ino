/***************************************************************************
 * RFIDuino CSV Logger
 *
 * This demo uses the RFIDuino sheild, a Geekduino (or other Arduino Board)
 * and the RFIDuino library to scan for a tag. Once a tag is read, the ID of
 * the tag's lower 4 bytes are stored into a single 'long' variable. This 4-byte
 * tag ID is sent over the serial port to an application that will log and add a
 * time stamp.
 * 
 * The RFIDuino library is compatible with both versions of the RFIDuino shield
 * (1.1 and 1.2), but the user must initialize the library correctly. See 
 * 'HARDWARE VERSION' instructions near the beginning of the code.
 *
 * The RFIDuino Shield is designed to be used with 125khz EM4100 family tags. 
 * This includes any of the EM4102 tags sold by Trossen Robotics/ RobotGeek. 
 * The RFIDuino shield may not work with tags outside the EM4100 family
 *
 *
 * Links
 *    RFIDuino Logger Getting Started Guide
 *      http://learn.robotgeek.com/projects/277-rfid-logger.html
 *    RFIDUino Getting Started Guide
 *      http://learn.robotgeek.com/getting-started/41-rfiduino/142-rfiduino-getting-started-guide.html
 *    RFIDUino Library Documentation
 *      http://learn.robotgeek.com/41-rfiduino/144-rfiduino-library-documentation.html
 *    RFIDUino Shield Product Page
 *      http://www.robotgeek.com/rfiduino
 *  
 *
 * User Output pins
 *    myRFIDuino.led1 - Red LED
 *    myRFIDuino.led2 - Green LED
 *    myRFIDuino.buzzer - Buzzer
 *
 ***************************************************************************/
 
#include <RFIDuino.h> //include the RFIDuino Library

#define SERIAL_PORT Serial      //Serial port definition for Geekduino, Arduino Uno, and most Arduino Boards
//#define SERIAL_PORT Serial1   //Serial port defintion for Arduino Leonardo and other ATmega32u4 based boards

const int LOG_TO_EEPROM = 0;
const int ENABLE_BUZZER = 0;

/***************
* HARDWARE VERSION - MAKE SURE YOU HAVE SET THE CORRECT HARDWARE VERSION BELOW
* Version 1.1 has a 4-pin antenna port and no version marking
* Version 1.2 has a 2-pin antenna port and is marked 'Rev 1.2'
*****************/
//RFIDuino myRFIDuino(1.1);     //initialize an RFIDuino object for hardware version 1.1
RFIDuino myRFIDuino(1.2);   //initialize an RFIDuino object for hardware version 1.2

byte tagData[5]; //Holds the ID numbers from the tag  
unsigned long tagID; //the lower 4 byted of the tag ID

void setup()
{
  //begin serial communicatons at 9600 baud and print a startup message
  SERIAL_PORT.begin(9600);

  //The RFIDUINO hardware pins and user outputs(Buzzer / LEDS) are all initialized via pinMode() in the library initialization, so you don not need to to that manually
}

void loop()
{   
  //scan for a tag - if a tag is sucesfully scanned, return a 'true' and proceed
  if(myRFIDuino.scanForTag(tagData) == true)
  {
    tagID = ((long)tagData[1] << 24) + ((long)tagData[2] << 16) + ((long)tagData[3] << 8) + tagData[4]; //generate a 4-byte number from the last 4 unique digits of th eID

    //generate leading zeros for nice printing
    for(int i = 1; i < 9; i++)
    {
      if( tagID < pow(10,i) )
      {
        SERIAL_PORT.print('0');
      }
    }

    SERIAL_PORT.print(tagID); //print the 4-byte tag ID
    SERIAL_PORT.write(0x0A);//return character for next line 

    //turn buzzer /led on quickly          
    digitalWrite(myRFIDuino.led2,HIGH);     //turn green LED on
    digitalWrite(myRFIDuino.buzzer, HIGH);   //turn the buzzer on
    delay(100);                             //wait for 1 second
    digitalWrite(myRFIDuino.buzzer, LOW);    //turn the buzzer off
    digitalWrite(myRFIDuino.led2,LOW);      //turn the green LED off

    delay(1000); //delay to prevent the tag from printing time-after time
  }

 }// end loop()
 
 
  
  

