/**********************************
 * RFIDuino Hello World 3
 *
 * This Project is designed to look
 * for a  RFID tag, and send that data
 * to the Arduino's Serial Port.
 * This will allow the user to see the ID
 * for an RFID tag.
 * This code can also be used to send 
 * data over XBees. 
 *
 * User Output pins
 *    myRFIDuino.led1 - Red LED
 *    myRFIDuino.led2 - Green LED
 *    myRFIDuino.buzzer - Buzzer
 *
 ***************************************************************************/

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
  //begin serial communicatons at 9600 baud and print a startup message
  Serial.begin(9600);
  Serial.println("Welcome to the RFIDuino Serial Example. Please swipe your RFID Tag.");


  //The RFIDUINO hardware pins and user outputs(Buzzer / LEDS) are all initialized via pinMode in the library
}

void loop()
{   
    tagCheck = myRFIDuino.decodeTag(tagData); //run the decodetag to check for the tag  
    if (tagCheck==true)   //if a 'true' is returned from the decodetag function, a tag was successfuly scanned 
    { 
      readCount++;      //increase count since the Arduino has successfully scanned a tag once
            
      if(readCount==1)//if the arduino has only read a tag only one time, proceed
      {
        myRFIDuino.transferToBuffer(tagData, tagDataBuffer);  //place the data that was read into the buffer to compare against the next read
      }
      
      else if(readCount > 1)//if we see a tag more than one time, proceed
      {
        verifyRead = myRFIDuino.compareTagData(tagData, tagDataBuffer); //run the compareTagData function to compare the data in the buffer (the last read) with the data from the current read
        if (verifyRead == true)  //if a 'true' is returned by compareTagData, the current read matches the last read
        {
           Serial.print("RFID Tag ID:");
           for(int n=0;n<5;n++)
           {
             Serial.print(tagData[n],DEC);
             if(n<4)//only print the comma on the first 4 nunbers
             {
               Serial.print(",");
             }
           }
           Serial.print("\n\r");//return character for next line
             
          digitalWrite(myRFIDuino.led2,HIGH);     //turn green LED on
          digitalWrite(myRFIDuino.buzzer, HIGH);   //turn the buzzer on
          delay(1000);                  //wait for 1 second
          digitalWrite(myRFIDuino.buzzer, LOW);    //turn the buzzer off
          digitalWrite(myRFIDuino.led2,LOW);      //turn the green LED off
        }
        readCount=0;//because a tag has been  read more than once, reset the readCount to '0' for the next tag
      }        
    }     
 }// end loop()
 
 
  
  

