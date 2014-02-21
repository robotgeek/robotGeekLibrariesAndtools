/**********************************
 * RFIDuino Project 1
 *
 * This Project is designed to look
 * for a 'key' RFID tag.  A green light will flash, and
 * 3 notes will be played
 *
 * If a tag that is not the 'key' tag is present,
 * a red light is flashed and an 'error' sound is played.
 **********************************/

#include <RFIDuino.h> //include the RFIDuino Library

//Define the pins for our outputs
#define   R_LED   3              //the Red LED on the RFIDuino shield
#define   G_LED  2               //the Green LED on the RFIDuino shield
#define   BUZZER 5               //the Buzzer on the RFIDuino shield

byte tagData[5];                   //Holds the ID numbers from the tag
byte tagDataBuffer[5];             //A Buffer for verifying the tag data
byte keyTag[5] ={77,0,44,22,242};  //an array that will hold all of our 'key tags'. Key tags are treated differently from other tags read
int readCount = 0;                 //the number of times a tag has been read  
boolean verifyRead = false;        //true when a tag's ID matches a previous read, false otherwise
boolean tagCheck = false;          //true when a tag has been read, false otherwise
boolean verifyKey = false;         //true when a verified tag has been determined to match the key tag, false otherwise

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
    if (tagCheck==true)   //if a 'true' is returned from the decodetag function, a tag was succesffuly scanned 
    { 
      readCount++;      //increase count since we've seen a tag
            
      if(readCount==1)//if have read a tag only one time, proceed
      {
        myrfid.transferToBuffer(tagData, tagDataBuffer);  //place the data from the current tag read into the buffer for the next read
      }
      
      else if(readCount==2)//if we see a tag a second time, proceed
      {
        verifyRead = myrfid.compareTagData(tagData, tagDataBuffer); //run the comparetagData function to compare the data in the buffer (the last read) with the data from the current read
        if (verifyRead == true)  //if a 'true' is returned by comparetagData, the current read matches the last read
        {
          
          verifyKey = myrfid.compareTagData(tagData, keyTag);//run the comparetagData to check the tag just read against the 'key' tag we defined.
          if(verifyKey == true)//if a 'true' is returned by comparetagData, the current read is a key tag
          {                       
            digitalWrite(G_LED,HIGH);          //turn green LED on
            myrfid.successSound(BUZZER);       //Play a 'success' sound from the buzzer, 3 notes acsending 
            delay(250);                        //wait for a period before turning off the LED
            digitalWrite(G_LED,LOW);           //turn the green LED off
          }
        
          else//otherwise the tag is not a key tag
          {        
            digitalWrite(R_LED,HIGH);  //turn red LED on
            myrfid.errorSound(BUZZER); //Play a 'erro' sound from the buzzer, 3 notes acsending 
            delay(250);                //wait for a period before turning off the LED
            digitalWrite(R_LED,LOW);   //turn the red LED off        
          }
        
        readCount=0;//because a tag has been  read twice, reset the readCount to '0' for the next tag
      }        
    }     
   
  }       
}//end loop()
 
 
  
  

