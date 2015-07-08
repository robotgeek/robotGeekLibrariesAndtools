/***********************************************
 * RFIDuino Hello World 1
 *
 * This Project is designed to look
 * for any RFID tag, and flash a 
 * green light/play sounds when that
 * tag is scanned.  
 * 
 * NOTE: This is tutorial code, and
 * should not be used for other purposes
 * as it does not have verification/buffering.
 * RFIDuino Hello World 2 implements verification
 * and is a better basis for projects.
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


byte tagData[5];          //Holds the ID numbers from the tag
boolean tagCheck = false; //true when a tag has been read, false otherwise
  

void setup()
{
  //The RFIDUINO hardware pins and user outputs are all initialized via pinMode in the library

}


void loop()
{     
    tagCheck = myRFIDuino.decodeTag(tagData); //run the decodetag to check for the tag. If a tag is read then the function will return 'true' and load the data into 'tagData'  
    if (tagCheck==true)   //if a 'true' is returned from the decodetag function, a tag was succesffuly scanned 
    {
            digitalWrite(myRFIDuino.led2,HIGH);      //turn green LED on
            digitalWrite(myRFIDuino.buzzer, HIGH);   //turn the buzzer on
            delay(1000);                         //wait for 1 second
            digitalWrite(myRFIDuino.buzzer, LOW);    //turn the buzzer off
            digitalWrite(myRFIDuino.led2,LOW);       //turn the green LED off
   }  
}//end main loop
 
 
  
  

