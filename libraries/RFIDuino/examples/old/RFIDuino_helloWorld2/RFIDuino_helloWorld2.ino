/***********************************************
 * RFIDuino Hello World 2
 *
 * This Project is designed to look
 * for any RFID tag, and flash a 
 * green light/play sounds when that
 * tag is scanned.  
 * This code implements a buffer to verify
 * tag reads are correct, and to remove
 * 'ghost reads'
 *

 * User Output pins
 *  myRFIDuino.led1 - Red LED
 *  myRFIDuino.led2 - Green LED
 *  myRFIDuino.buzzer - Buzzer
 *
 ***********************************************/
#include <RFIDuino.h> //include the RFIDuino Library



/***************
* HARDWARE VERSION - MAKE SURE YOU HAVE SET THE CORRECT HARDWARE VERSION BELOW
* Version 1.1 has a 4-pin antenna port and no version marking
* Version 1.2 has a 2-pin antenna port and is marked 'Rev 1.2'
*****************/
RFIDuino myRFIDuino(1.1);     //initialize an RFIDuino object for hardware version 1.1
//RFIDuino myRFIDuino(1.2);       //initialize an RFIDuino object for hardware version 1.2


byte tagData[5];            //Holds the ID numbers from the tag
byte tagDataBuffer[5];      //A Buffer for verifying the tag data
int readCount = 0;          //the number of times a tag has been read
boolean verifyRead = false; //true when a tag's ID matches a previous read, false otherwise
boolean tagCheck = false;   //true when a tag has been read, false otherwise
  

void setup()
{
  //The RFIDUINO hardware pins and user outputs(Buzzer / LEDS) are all initialized via pinMode in the library
}

void loop()
{   
    tagCheck = myRFIDuino.decodeTag(tagData); //run the decodetag to check for the tag  
    if (tagCheck==true)   //if a 'true is' returned from the decodetag function, a tag was succesffuly scanned 
    { 
      readCount++;      //increase count since we've seen a tag
            
      if(readCount==1)//if have read a tag only one time, proceed
      {
        myRFIDuino.transferToBuffer(tagData, tagDataBuffer);  //place the data from the current tag read into the buffer for the next read
      }
      
      else if(readCount==2)//if we see a tag a second time, proceed
      {
        verifyRead = myRFIDuino.compareTagData(tagData, tagDataBuffer); //run the checkBuffer function to compare the data in the buffer (the last read) with the data from the current read
        
        if (verifyRead ==true)  //if a 'true' is returned by compareTagData, the current read matches the last read
        {
            digitalWrite(myRFIDuino.led2,HIGH);     //turn green LED on
            digitalWrite(myRFIDuino.buzzer , HIGH);   //turn the buzzer on
            delay(1000);                  //wait for 1 second
            digitalWrite(myRFIDuino.buzzer , LOW);    //turn the buzzer off
            digitalWrite(myRFIDuino.led2,LOW);      //turn the green LED off
        }

        readCount=0;//because a tag has been succesfully verified, reset the readCount to '0' for the next tag
      }        
    }  
}//end main loop
 
 
  
  

