//Arm 5
//Sequence 6
//Mode 2
//Orientation 1
//DIO 1
#include "Kinematics.h"
#include "GlobalArm.h"
extern void IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable);
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int playState1 = 0; // 0 = stopped 1 = playing
volatile int playState2 = 0; // 0 = stopped 1 = playing
volatile int playState3 = 0; // 0 = stopped 1 = playing
volatile int playState4 = 0; // 0 = stopped 1 = playing

void playSequence1()
{
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  delay(500);
  Serial.println("Sequencing Mode Active."); 
  Serial.println("Press Pushbutton  to stop");
  playState1 = 1;  //set playState to 1 as the sequence is now playing
    g_bIKMode = IKM_CYLINDRICAL;
    //###########################################################//
    // SEQUENCE 1
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1500 , 150 , 225 , 0 , 0 , 1500 , 816 , 500, playState1);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 2
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1987 , 200 , 225 , 0 , 0 , 1500 , 1776 , 1000, playState1);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 3
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1987 , 200 , 114 , 0 , 0 , 1500 , 816 , 500, playState1);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 4
    //###########################################################// 
    //DIO64
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1987 , 200 , 114 , 0 , 0 , 1500 , 880 , 5000, playState1);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 5
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1987 , 200 , 225 , 0 , 0 , 1500 , 880 , 500, playState1);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 6
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1987 , 200 , 225 , 0 , 0 , 1500 , 848 , 500, playState1);
    //###########################################################// 

 delay(100);
 Serial.println("Pausing Sequencing Mode."); 
 delay(500);
 //uncomment this to  put the arm in sleep position after a sequence
 //PutArmToSleep();
}


void playSequence2()
{
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  delay(500);
  Serial.println("Sequencing Mode Active."); 
  Serial.println("Press Pushbutton  to stop");
  playState2 = 1;  //set playState to 1 as the sequence is now playing
    g_bIKMode = IKM_CYLINDRICAL;
    //###########################################################//
    // SEQUENCE 1
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1500 , 150 , 225 , 0 , 0 , 1500 , 816 , 500, playState2);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 2
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1622 , 182 , 225 , 0 , 0 , 1500 , 1776 , 1000, playState2);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 3
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1690 , 185 , 114 , 0 , 0 , 1500 , 816 , 1000, playState2);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 4
    //###########################################################// 
    //DIO64
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1690 , 185 , 114 , 0 , 0 , 1500 , 816 , 5000, playState2);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 5
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1690 , 172 , 225 , 0 , 0 , 1500 , 816 , 500, playState2);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 6
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1628 , 163 , 225 , 0 , 0 , 1500 , 848 , 500, playState2);
    //###########################################################// 

 delay(100);
 Serial.println("Pausing Sequencing Mode."); 
 delay(500);
 //uncomment this to  put the arm in sleep position after a sequence
 //PutArmToSleep();
}


void playSequence3()
{
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  delay(500);
  Serial.println("Sequencing Mode Active."); 
  Serial.println("Press Pushbutton  to stop");
  playState3 = 1;  //set playState to 1 as the sequence is now playing
    g_bIKMode = IKM_CYLINDRICAL;
    //###########################################################//
    // SEQUENCE 1
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1500 , 150 , 225 , 0 , 0 , 1500 , 816 , 500, playState3);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 2
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1322 , 176 , 225 , 0 , 0 , 1500 , 1776 , 1000, playState3);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 3
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1343 , 174 , 106 , 0 , 0 , 1500 , 816 , 1000, playState3);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 4
    //###########################################################// 
    //DIO64
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1332 , 176 , 106 , 0 , 0 , 1500 , 816 , 5000, playState3);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 5
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1330 , 172 , 225 , 0 , 0 , 1500 , 816 , 500, playState3);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 6
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1320 , 163 , 225 , 0 , 0 , 1500 , 848 , 500, playState3);
    //###########################################################// 

 delay(100);
 Serial.println("Pausing Sequencing Mode."); 
 delay(500);
 //uncomment this to  put the arm in sleep position after a sequence
 //PutArmToSleep();
}

void playSequence4()
{
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  delay(500);
  Serial.println("Sequencing Mode Active."); 
  Serial.println("Press Pushbutton  to stop");
  playState4 = 1;  //set playState to 1 as the sequence is now playing
    g_bIKMode = IKM_CYLINDRICAL;
    //###########################################################//
    // SEQUENCE 1
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1500 , 150 , 225 , 0 , 0 , 1500 , 816 , 500, playState4);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 2
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(965 , 200 , 225 , 0 , 0 , 1500 , 1776 , 1000, playState4);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 3
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(955 , 200 , 106 , 0 , 0 , 1500 , 816 , 1000, playState4);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 4
    //###########################################################// 
    //DIO64
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(955 , 200 , 106 , 0 , 0 , 1500 , 816 , 5000, playState4);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 5
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(963 , 200 , 225 , 0 , 0 , 1500 , 816 , 500, playState4);
    //###########################################################// 

    //###########################################################//
    // SEQUENCE 6
    //###########################################################// 
    //DIO0
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    IKSequencingControl(1085 , 163 , 225 , 0 , 0 , 1500 , 848 , 500, playState4);
    //###########################################################// 

 delay(100);
 Serial.println("Pausing Sequencing Mode."); 
 delay(500);
 //uncomment this to  put the arm in sleep position after a sequence
 //PutArmToSleep();
}
