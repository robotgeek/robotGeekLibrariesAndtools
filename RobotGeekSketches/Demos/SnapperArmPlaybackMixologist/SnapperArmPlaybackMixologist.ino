/***********************************************************************************
 * _}--\   RobotGeek Robotic Arm Mixologist    /--{_
 *      |       Analog IK Control Code        |
 *   __/ ___                               ___ \__
 *  |__||___|                             |___||__|
 *
 *
 *  This sketch can also be used to play back one of 4 pre-programmed sequences that 
 *  were generated in ArmLink and altered. This code is activated by serial terminal
 *  or pushbutton.
 *
 *  Snapper Arm Getting Started Guide
 *    http://learn.robotgeek.com/getting-started/33-robotgeek-snapper-robot-arm/63-robotgeek-snapper-arm-getting-started-guide.html
 *   Playback using Arm Link software
 *     http://learn.trossenrobotics.com/20-interbotix/robot-arms/143-arm-link-sequence-playback.html
 *    Using the IK Firmware
 *    http://learn.robotgeek.com/demo-code/demo-code/154-robotgeek-snapper-joystick-inverse-kinematics-demo.html
 *
 *  WIRING
 *    Servos
 *      Digital I/O 3 - Base Rotation - Robot Geek Servo 
 *      Digital I/O 5 - Shoulder Joint - Robot Geek Servo 
 *      Digital I/O 6 - Elbow Joint - Robot Geek Servo 
 *      Digital I/O 9 - Wrist Joint - Robot Geek Servo 
 *      Digital I/O 10 - Gripper Servo -  Not used for this sketch, but included
 *    Digital Inputs
 *      Digital 2 - Button 1
 *    Digital Outputs
 *      Digital 4 - LED 1
 *      Digital 7 - LED 2
 *      Digital 8 - LED 3
 *      Digital 12 - LED 4
 *    Analog Inputs
 *      Analog 0 - Joystick 1
 *    I2C
 *      RobotGeek LCD Screen
 *
 * 
 *
 *
 *  NOTES
 *
 *    SERVO POSITIONS
 *      The servos' positions will be tracked in microseconds, and written to the servos
 *      using .writeMicroseconds()
 *        http://arduino.cc/en/Reference/ServoWriteMicroseconds
 *      For RobotGeek servos, 600ms corresponds to fully counter-clockwise while
 *      2400ms corresponds to fully clock-wise. 1500ms represents the servo being centered 
 *
 *      For the 9g servo, 900ms corresponds to fully counter-clockwise while
 *      2100ms corresponds to fully clock-wise. 1500ms represents the servo being centered 
 *
 *
 *  This code is a Work In Progress and is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 * Sources used:
 * https://github.com/KurtE
 * 
 * http://www.circuitsathome.com/mcu/robotic-arm-inverse-kinematics-on-arduino
 * 
 * Application Note 44 - Controlling a Lynx6 Robotic Arm 
 * http://www.micromegacorp.com/appnotes.html
 * http://www.micromegacorp.com/downloads/documentation/AN044-Robotic%20Arm.pdf
 * 
 * 
 *   This code is a Work In Progress and is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *   
 ***********************************************************************************/
#define ROBOT_GEEK_9G_GRIPPER 1
#define ROBOT_GEEK_PARALLEL_GRIPPER 2

//The 9G gripper is the gripper with the small blue 9g servo
//The Parralle gripper has a full robotgeek servo and paralle rails
//Uncomment one of the following lines depending on which gripper you are using.
//#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER
#define GRIPPER_TYPE ROBOT_GEEK_PARALLEL_GRIPPER

#ifndef GRIPPER_TYPE
   #error YOU HAVE TO SELECT THE GRIPPER YOU ARE USING! Uncomment the correct line above for your gripper
#endif

#include <ServoEx.h>
#include <Wire.h> 
#include <RobotGeekLCD.h>


//kinematics file - local
#include "Kinematics.h"

//armSequence
#include "armSequence.h"

//set USE_BUTTON to FALSE if you do not have a button attached to the Geekduino
#define USE_BUTTON true

//set BUTTON TRUE to HIGH for a button with built in pullup resistor like the RobotGeek Pushbutton.
//set BUTTON TRUE to LOW for a simple 2-pin pushbutton.
#define BUTTON_TRUE HIGH
#define BUTTON1_PIN 2
#define JOYSTICK_PIN 0
#define LED1 4
#define LED2 7
#define LED3 8
#define LED4 12
//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 482   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 542  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

int drinkSelectCounter = 1;
int buttonState1;     
int JSValue; 
boolean joyUp = 0;
boolean joyDown = 0;

// LCD Screen
long previousMillis = 0;        // will store last time LCD was updated
long interval = 100;           // interval at which to update LCD (milliseconds)

// This is where we pull the names for the drinks, as well as other things to be displayed on the LCD screen
String drinkLine[12] = {"Select Drink:",
                        "Red", 
                        "Green",
                        "Blue",
                        "Yellow",
                        "Red and Green",
                        "Red and Blue",
                        "Red and Yellow",
                        "Green and Blue",
                        "Green and Yellow",
                        "Blue and Yellow",
                        "Please Wait..."
                        };

ServoEx    ArmServo[5]; //Start the servo object with 5 attachable servos
RobotGeekLCD lcd; //Start the LCD object

//===================================================================================================
// Setup 
//===================================================================================================
void setup(){
  // Attach servo and set limits
  ArmServo[BAS_SERVO].attach(3, BASE_MIN, BASE_MAX);
  ArmServo[SHL_SERVO].attach(5, SHOULDER_MIN, SHOULDER_MAX);
  ArmServo[ELB_SERVO].attach(6, ELBOW_MIN, ELBOW_MAX);
  ArmServo[WRI_SERVO].attach(9, WRIST_MIN, WRIST_MAX);
  ArmServo[GRI_SERVO].attach(10, GRIPPER_MIN, GRIPPER_MAX);

  // initialize pin 2 on interupt 0
  attachInterrupt(0, stateChange, CHANGE);  
  // initialize the pins for the pushbutton as inputs:  

  // set inputs
  pinMode(BUTTON1_PIN, INPUT);     
  pinMode(JOYSTICK_PIN, INPUT);

  // set outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // send arm to default X,Y,Z coord
  doArmIK(true, g_sIKX,g_sIKY,g_sIKZ,g_sIKGA);
  MoveArmTo(sBase, sShoulder, sElbow, sWrist, sWristRot, sGrip, sDeltaTime, true);

  SetServo(sDeltaTime);

  // start serial
  Serial.begin(9600);
  Serial.println("Starting Playback Demo");
  Serial.println("Send '1' through '0' to start or push the button to start the playback");
  delay(500);

  // initlaize the lcd object - this sets up all the variables and IIC setup for the LCD object to work
  lcd.init();
  // Print a message to the LCD.
  lcd.print("Mix it up!");
  //light show!
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED4, LOW);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  delay(100);
}


void loop()
{
  // LCD
  unsigned long currentMillis = millis(); // Update currentMillis
  if(currentMillis - previousMillis > interval) 
    {
      // save the last time you updated the screen 
      previousMillis = currentMillis;   
      lcd.setCursor(0, 0);
      lcd.print(drinkLine[0]);
      lcd.print("               ");
      lcd.setCursor(0, 1);
      lcd.print(drinkLine[drinkSelectCounter]);
      lcd.print("               ");
    }


  //JOYSTICK
  JSValue = analogRead(JOYSTICK_PIN);
  //only update joystick if outside the deadzone (out of center position)
  if (JSValue > DEADBANDHIGH) //if the joystick value is greater than the high end of the deadband (moved out of center up)
  {
    joyUp = 1; // set the joystick moved up toggle high
  }
  else if (JSValue < DEADBANDLOW) //if the joystick value is less than the low end of the deadband (moved out of center down)
  {
    joyDown = 1; // set the joystick moved down toggle high
  }

  else // When the joystick is within the deadband
  {
    if (joyUp == 1) // if the joystick up toggle was moved to high
    {
      drinkSelectCounter = (drinkSelectCounter + 1); //add 1 to the drink select counter
    }
    else if (joyDown == 1) // if the joystick down toggle was moved to high
    {
      drinkSelectCounter = (drinkSelectCounter - 1); //subtract 1 from the drink select counter
    }
    //reset the joystick toggles after moving the counter, before next cycle
    joyUp = 0;
    joyDown = 0; 
  }
  
  drinkSelectCounter = constrain(drinkSelectCounter, 1, 10); //constrain the possible selection numbers for the drink counter

  // LEDs show which drinks are selected
  if (drinkSelectCounter == 1)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 2)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 3)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 4)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }
  else if (drinkSelectCounter == 5)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 6)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 7)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }
  else if (drinkSelectCounter == 8)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  }
  else if (drinkSelectCounter == 9)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }
  else if (drinkSelectCounter == 10)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }


  //If USE_BUTTON is TRUE then read from the button pin
  if(USE_BUTTON == true)
  { 
    //use digitalRead to store the current state of the pushbutton in one of the 'buttonState' variables
    buttonState1 = digitalRead(BUTTON1_PIN);
    
    //if the button has been pushed, run the sequence
    //the sequence will run until the button is pressed again.
    if (buttonState1 == BUTTON_TRUE) 
    {  
      lcd.setCursor(0, 1);
      lcd.print(drinkLine[11]);
      lcd.print("               ");
      if (drinkSelectCounter == 1)
      {
        digitalWrite(LED1, HIGH);
        playSequence1();
        digitalWrite(LED1, LOW);
      }
      else if (drinkSelectCounter == 2)
      {
        digitalWrite(LED2, HIGH);
        playSequence2();
        digitalWrite(LED2, LOW);
      }
      else if (drinkSelectCounter == 3)
      {
        digitalWrite(LED3, HIGH);
        playSequence3();
        digitalWrite(LED3, LOW);
      }
      else if (drinkSelectCounter == 4)
      {
        digitalWrite(LED4, HIGH);
        playSequence4();
        digitalWrite(LED4, LOW);
      }
      else if (drinkSelectCounter == 5)
      {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        playSequence1();
        playSequence2();
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
      }
      else if (drinkSelectCounter == 6)
      {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED3, HIGH);
        playSequence1();
        playSequence3();
        digitalWrite(LED1, LOW);
        digitalWrite(LED3, LOW);
      }
      else if (drinkSelectCounter == 7)
      {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED4, HIGH);
        playSequence1();
        playSequence4();
        digitalWrite(LED1, LOW);
        digitalWrite(LED4, LOW);
      }
      else if (drinkSelectCounter == 8)
      {
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        playSequence2();
        playSequence3();
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
      }      
      else if (drinkSelectCounter == 9)
      {
        digitalWrite(LED2, HIGH);
        digitalWrite(LED4, HIGH);
        playSequence2();
        playSequence4();
        digitalWrite(LED2, LOW);
        digitalWrite(LED4, LOW);
      }      
      else if (drinkSelectCounter == 10)
      {
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        playSequence3();
        playSequence4();
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
      }
      //At the end of every cycle, clear the line.
      digitalWrite(13, HIGH);
      delay(3000);
      digitalWrite(13, LOW);
    } 
  }

  
  //read a byte from the serial port
  int inByte = Serial.read();

  //if the character is '1' , run sequence 1
  if (inByte == '1') 
  {     
    playSequence1();
  } 
  //if the character is '2' , run sequence 2
  if (inByte == '2') 
  {     
    playSequence2();
  }  
  //if the character is '3' , run sequence 3
  if (inByte == '3') 
  {     
    playSequence3();
  } 
  //if the character is '4' , run sequence 4
  if (inByte == '4') 
  {     
    playSequence4();
  }   
  //if the character is '5' , run sequence 1 & 2
  if (inByte == '5') 
  {     
    playSequence1();
    playSequence2();
  }   
  //if the character is '6' , run sequence 1 & 3
  if (inByte == '6') 
  {     
    playSequence1();
    playSequence3();
  }   
  //if the character is '7' , run sequence 1 & 4
  if (inByte == '7') 
  {     
    playSequence1();
    playSequence4();
  }   
  //if the character is '8' , run sequence 2 & 3
  if (inByte == '8') 
  {     
    playSequence2();
    playSequence3();
  }   
  //if the character is '9' , run sequence 2 & 4
  if (inByte == '9') 
  {     
    playSequence2();
    playSequence4();
  }   
  //if the character is '0' , run sequence 3 & 4
  if (inByte == '0') 
  {     
    playSequence3();
    playSequence4();
  }   
  
}






//===================================================================================================
// SetServo: Writes Servo Position Solutions
//===================================================================================================
void SetServo(unsigned int DeltaTime)
{
  ServoGroupMove.start();
  ArmServo[BAS_SERVO].writeMicroseconds(Base + BAS_SERVO_ERROR);
  ArmServo[SHL_SERVO].writeMicroseconds(Shoulder + SHL_SERVO_ERROR);
  ArmServo[ELB_SERVO].writeMicroseconds(Elbow + ELB_SERVO_ERROR);
  ArmServo[WRI_SERVO].writeMicroseconds(Wrist + WRI_SERVO_ERROR);
  ArmServo[GRI_SERVO].writeMicroseconds(Gripper + GRI_SERVO_ERROR);
  ServoGroupMove.commit(DeltaTime);
}


/***********************************************************
 * IKSequencingControl()
 *    Function used to set parameters for the Arm
 *
 * The following variables are named for Cartesian mode -
 * however the data that will be held/sent will vary based on the current IK mode
 ****************************************************************************
 * Variable name | Cartesian Mode | Cylindrcal Mode | Backhoe Mode          |
 *_______________|________________|_________________|_______________________|
 *   x           |   x            |   base          |   base joint          |
 *   y           |   y            |   y             |   shoulder joint      |
 *   z           |   z            |   z             |   elbow joint         |
 *   GA          |  wristAngle    |  wristAngle     |   wrist angle joint   |
 *   gripper     |  gripper       |  gripper        |   gripper joint       |
 *
 * interpolate - the amount of time to complete a pose
 * pause - time ti pause after a pose is completed
 * enable - setting this to '1' makes the function work. Setting it to '0' bypasses the function. This can be usefull for breaking out of sequences
 *
 *
 **********************************************************/
 
void IKSequencingControl(float X, float Y, float Z, float GA, int grip, int interpolate, int pause, int enable ){
  if(enable == 1)
  {
    
    if(g_bIKMode == IKM_IK3D_CARTESIAN || g_bIKMode == IKM_IK3D_CARTESIAN_90)
    {
      
      doArmIK(true, X, Y, Z, GA); 
      
    }
    else if(g_bIKMode == IKM_CYLINDRICAL || g_bIKMode ==IKM_CYLINDRICAL_90)
    {  
      sBase = X;
      doArmIK(false, X, Y, Z, GA); 
      
    }
    else if(g_bIKMode == IKM_BACKHOE)
    {
      sBase = X;
      sShoulder = Y;
      sElbow = Z;
      sWrist = GA;
      
    }
    
    
    
    sGrip = grip;
    MoveArmTo(sBase, sShoulder, sElbow, sWrist, sWristRot, sGrip, sDeltaTime, true);
    SetServo(interpolate);
    delay(interpolate + pause);
  }
}

//overloaded function to accout for extra empty wrist rotate packet
void IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable ){
   IKSequencingControl( X, Y, Z, GA,  grip,interpolate,  pause,  enable );
}


void stateChange()
{
  if(playState1 == 1)
    {
      playState1 = 0;
    }
  if(playState2 == 1)
    {
      playState2 = 0;
    }
  if(playState3 == 1)
    {
      playState3 = 0;
    }
  if(playState4 == 1)
    {
      playState4 = 0;
    }
    
}

