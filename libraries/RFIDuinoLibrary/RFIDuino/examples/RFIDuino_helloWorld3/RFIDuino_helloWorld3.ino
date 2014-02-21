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
 **********************************/
 
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
  //begin serial communicatons at 9600 baud 
  Serial.begin(9600);
  Serial.println("Welcome to the RFIDuino Serial Example. Please swipe your RFID Tag.");

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
        verifyRead = myrfid.compareTagData(tagData, tagDataBuffer); //run the compareTagData function to compare the data in the buffer (the last read) with the data from the current read
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
             
          digitalWrite(G_LED,HIGH);     //turn green LED on
          digitalWrite(BUZZER, HIGH);   //turn the buzzer on
          delay(1000);                  //wait for 1 second
          digitalWrite(BUZZER, LOW);    //turn the buzzer off
          digitalWrite(G_LED,LOW);      //turn the green LED off
        }
        readCount=0;//because a tag has been  read twice, reset the readCount to '0' for the next tag
      }        
    }     
 }// end loop()
 
 
  
  

