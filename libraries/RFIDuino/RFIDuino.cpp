/****************************************************************************************************
* rfiduino.cpp - RFIDuino Library CPP File
*
* RFIDuino Library v1.2 by TrossenRobotics / RobotGeek
*
* This Library enables a Geekduino/Arduino to work with the RobotGeek RFIDuino Shield.
* Using the sheild and this library a user can detect a card, read/decode the card,
* compare the read to previous reads, and intearct with the inbord buzzer.
*
* Links
*    RFIDUino Getting Started Guide
*      http://learn.robotgeek.com/getting-started/41-rfiduino/142-rfiduino-getting-started-guide.html
*    RFIDUino Library Documentation
*      http://learn.robotgeek.com/41-rfiduino/144-rfiduino-library-documentation.html
*    RFIDUino Shield Product Page
*      http://www.robotgeek.com/rfiduino
*
*
****************************************************************************************************/
#include "Arduino.h"
#include "RFIDuino.h"

//initialize the RFIDuino object and set the pins correctlly based on hardware version
RFIDuino::RFIDuino(float version)
{
  //original RFIDuino (4-pin antenna, no printed version number)
  if (version == 1.1)
  {
    //User Accessible Output
    buzzer = 5;
    led1 = 3;
    led2 = 2;

    //RFID related pins
    demodOut = 8;
    shd = 7;
    mod = 6;
    rdyClk = 4;
  }
  //RFIDuino 1.2 (2-pin antenna, "Rev 1.2" printed version number)
  else if (version == 1.2)
  {
    //User Accessible Output
    buzzer = 5;
    led1 = 8;
    led2 = 4;

    //RFID related pins
    demodOut = 3;
    shd = 7;
    mod = 6;
    rdyClk = 2;
  }
  else
  {
    while(1); //TODO: prevent this from happening
  }

  //set pin modes on RFID pins
  pinMode(mod, OUTPUT);
  pinMode(shd, OUTPUT);
  pinMode(demodOut, INPUT);
  pinMode(rdyClk, INPUT);

  //set pins for User Acccessible Output
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //set user outputs to LOW
  digitalWrite(buzzer, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  //set shd and MOD low to prepare for reading
  digitalWrite(shd, LOW);
  digitalWrite(mod, LOW);
}

//Manchester decode. Supply the function an array to store the tags ID in
bool RFIDuino::decodeTag(unsigned char *buf)
{
  unsigned char i = 0;
  unsigned short timeCount;
  unsigned char timeOutFlag = 0;
  unsigned char row, col;
  unsigned char row_parity;
  unsigned char col_parity[5];
  unsigned char dat;
  unsigned char searchCount = 0;
  unsigned char j;
  while(1)
  {
    timeCount = 0;
    while(0 == digitalRead(demodOut)) //watch for demodOut to go low
    {

      if(timeCount >= TIMEOUT) //if we pass TIMEOUT milliseconds, break out of the loop
      {
        break;
      }
      else
      {
        timeCount++;
      }
    }

    if (timeCount >= 600)
    {
      return false;
    }
    timeCount = 0;

    delayMicroseconds(DELAYVAL);
    if(digitalRead(demodOut))
    {
      for(i = 0; i < 8; i++) // 9 header bits
      {
        timeCount = 0; //restart counting
        while(1 == digitalRead(demodOut)) //while DEMOD out is high
        {
          if(timeCount == TIMEOUT)
          {
            timeOutFlag = 1;
            break;
          }
          else
          {
            timeCount++;
          }
        }

        if(timeOutFlag)
        {
          break;
        }
        else
        {
          delayMicroseconds(DELAYVAL);
          if( 0 == digitalRead(demodOut) )
          {
            break;
          }
        }
      }//end for loop

      if(timeOutFlag)
      {
        timeOutFlag = 0;
        return false;
      }

      if(i == 8) //Receive the data
      {
        timeOutFlag = 0;
        timeCount = 0;
        while(1 == digitalRead(demodOut))
        {
          if(timeCount == TIMEOUT)
          {
            timeOutFlag = 1;
            break;
          }
          else
          {
            timeCount++;
          }

          if(timeOutFlag)
          {
            timeOutFlag = 0;
            return false;
          }
        }

        col_parity[0] = col_parity[1] = col_parity[2] = col_parity[3] = col_parity[4] = 0;
        for(row = 0; row < 11; row++)
        {
          row_parity = 0;
          j = row >> 1;

          for(col = 0, row_parity = 0; col < 5; col++)
          {
            delayMicroseconds(DELAYVAL);
            if(digitalRead(demodOut))
            {
              dat = 1;
            }
            else
            {
              dat = 0;
            }

            if(col < 4 && row < 10)
            {
              buf[j] <<= 1;
              buf[j] |= dat;
            }

            row_parity += dat;
            col_parity[col] += dat;
            timeCount = 0;
            while(digitalRead(demodOut) == dat)
            {
              if(timeCount == TIMEOUT)
              {
                timeOutFlag = 1;
                break;
              }
              else
              {
                timeCount++;
              }
            }
            if(timeOutFlag)
            {
              break;
            }
          }

          if(row < 10)
          {
            if((row_parity & 0x01) || timeOutFlag) //Row parity
            {
              timeOutFlag = 1;
              break;
            }
          }
        }

        if( timeOutFlag || (col_parity[0] & 0x01) || (col_parity[1] & 0x01) || (col_parity[2] & 0x01) || (col_parity[3] & 0x01) ) //Column parity
        {
          timeOutFlag = 0;
          return false;
        }
        else
        {
          return true;
        }

      }//end if(i==8)

      return false;

    }//if(digitalRead(demodOut))
  } //while(1)
};

//use the tone() function to play an 'error' sound, a single tone repeated 3 times
void RFIDuino::errorSound()
{
  tone(buzzer, 1300, 500);
  delay(250);
  noTone(buzzer);
  delay(250);

  tone(buzzer, 1300, 1000);
  delay(250);
  noTone(buzzer);
  delay(250);

  tone(buzzer, 1300, 1000);
  delay(250);
  noTone(buzzer);
  delay(250);

};

//use the tone() function to play an 'success' sound, 3 ascending tones
void RFIDuino::successSound()
{
  tone(buzzer, 3500, 1000);
  delay(165);
  noTone(buzzer);

  tone(buzzer, 4000, 1000);
  delay(165);
  noTone(buzzer);

  tone(buzzer, 4500, 1000);
  delay(165);
  noTone(buzzer);
  delay(165);
};

//function to compare 2 byte arrays. Returns true if the two arrays match, false of any numbers do not match
bool RFIDuino::compareTagData(byte *tagData1, byte *tagData2)
{
  for(int j = 0; j < 5; j++)
  {
    if (tagData1[j] != tagData2[j])
    {
      return false; //if any of the ID numbers are not the same, return a false
    }
  }

  return true;  //all id numbers have been verified
}

//function to transfer one byte array to a secondary byte array.
//source -> tagData
//destination -> tagDataBuffer
void RFIDuino::transferToBuffer(byte *tagData, byte *tagDataBuffer)
{
  for(int j = 0; j < 5; j++)
  {
    tagDataBuffer[j] = tagData[j];
  }
}

bool RFIDuino::scanForTag(byte *tagData)
{
  static byte tagDataBuffer[5];      //A Buffer for verifying the tag data. 'static' so that the data is maintained the next time the loop is called
  static int readCount = 0;          //the number of times a tag has been read. 'static' so that the data is maintained the next time the loop is called
  boolean verifyRead = false; //true when a tag's ID matches a previous read, false otherwise
  boolean tagCheck = false;   //true when a tag has been read, false otherwise

  tagCheck = decodeTag(tagData); //run the decodetag to check for the tag
  if (tagCheck == true) //if 'true' is returned from the decodetag function, a tag was succesfully scanned
  {
    readCount++;      //increase count since we've seen a tag

    if(readCount == 1) //if have read a tag only one time, proceed
    {
      transferToBuffer(tagData, tagDataBuffer);  //place the data from the current tag read into the buffer for the next read
    }
    else if(readCount == 2) //if we see a tag a second time, proceed
    {
      verifyRead = compareTagData(tagData, tagDataBuffer); //run the checkBuffer function to compare the data in the buffer (the last read) with the data from the current read

      if (verifyRead == true) //if a 'true' is returned by compareTagData, the current read matches the last read
      {
        readCount = 0; //because a tag has been succesfully verified, reset the readCount to '0' for the next tag
        return true;
      }
    }
  }
  else
  {
    return false;
  }
}
