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
 ***********************************************/
 
#include <RFIDuino.h> //include the RFIDuino Library

//Define the pins for our outputs
#define   R_LED   3              //the Red LED on the RFIDuino shield
#define   G_LED  2               //the Green LED on the RFIDuino shield
#define   BUZZER 5

byte tagData[5];         //Holds the ID numbers from the tag
boolean tagCheck = false;     //true when a tag has been read, false otherwise
  
RFIDuino myrfid;   //initialize an RFIDuino object 

void setup()
{
  //Set LEDs and buzzer pins to ouput pin mode
  pinMode(R_LED,OUTPUT);
  pinMode(G_LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  
  //Set the output pins LOW to ensure that they are all 'off' on startup
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);
  digitalWrite(BUZZER, LOW);
}



void loop()
{     
    tagCheck = myrfid.decodeTag(tagData); //run the decodetag to check for the tag  
    if (tagCheck==true)   //if a '0' is returned from the decodetag function, a tag was succesffuly scanned 
    {
            digitalWrite(G_LED,HIGH);     //turn green LED on
            digitalWrite(BUZZER, HIGH);   //turn the buzzer on
            delay(1000);                  //wait for 1 second
            digitalWrite(BUZZER, LOW);    //turn the buzzer off
            digitalWrite(G_LED,LOW);      //turn the green LED off
   }  
}//end main loop
 
 
  
  

