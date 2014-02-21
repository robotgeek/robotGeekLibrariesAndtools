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
 ***********************************************/
 
#include <RFIDuino.h> //include the RFIDuino Library

//Define the pins for our outputs
#define   R_LED   3              //the Red LED on the RFIDuino shield
#define   G_LED  2               //the Green LED on the RFIDuino shield
#define   BUZZER 5               //the Buzzer on the RFIDuino shield

byte tagData[5];         //Holds the ID numbers from the tag
byte tagDataBuffer[5];  //A Buffer for verifying the tag data

int readCount = 0;        //the number of times a tag has been read
boolean verifyRead = false;     ////true when a tag's ID matches a previous read, false otherwise
boolean tagCheck = false;        ////true when a tag has been read, false otherwise
  
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
    if (tagCheck==true)   //if a 'true is' returned from the decodetag function, a tag was succesffuly scanned 
    { 
      readCount++;      //increase count since we've seen a tag
            
      if(readCount==1)//if have read a tag only one time, proceed
      {
        myrfid.transferToBuffer(tagData, tagDataBuffer);  //place the data from the current tag read into the buffer for the next read
      }
      
      else if(readCount==2)//if we see a tag a second time, proceed
      {
        verifyRead = myrfid.compareTagData(tagData, tagDataBuffer); //run the checkBuffer function to compare the data in the buffer (the last read) with the data from the current read
        
        if (verifyRead ==true)  //if a 'true' is returned by compareTagData, the current read matches the last read
        {
            digitalWrite(G_LED,HIGH);     //turn green LED on
            digitalWrite(BUZZER, HIGH);   //turn the buzzer on
            delay(1000);                  //wait for 1 second
            digitalWrite(BUZZER, LOW);    //turn the buzzer off
            digitalWrite(G_LED,LOW);      //turn the green LED off
        }

        readCount=0;//because a tag has been succesfully verified, reset the readCount to '0' for the next tag
      }        
    }  
}//end main loop
 
 
  
  

