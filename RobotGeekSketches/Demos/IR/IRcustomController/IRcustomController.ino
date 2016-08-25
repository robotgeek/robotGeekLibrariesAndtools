/*                                    Custom IR Controller
 *                                   _______________________
 * 
 *  This demonstration script allows you to send IR commands to a device using an interface
 *  customized to your liking. The default interface has two joysticks, two face buttons,
 *  and two trigger buttons, an arrangement well suited for robotic rovers, crawlers,
 *  turrets, and arms.
 *  
 *  ---------------------------------------
 *  
 *  AIO-0 - Left Joystick Horizontal Axis
 *  AIO-1 - Left Joystick Vertical Axis
 *  AIO-2 - Right Joystick Horizontal Axis
 *  AIO-3 - Right Joystick Vertical Axis
 *  DIO-2 - Left Face Button
 *  DIO-4 - Right Face Button
 *  DIO-7 - Left Trigger Button
 *  DIO-8 - Right Trigger Button
 *  DIO-3 - IR Transmitter
 *  
 *  ---------------------------------------
 * 
 */
#include <IRLib.h>

IRsend My_Sender;
const int Set_Protocol = NEC;
//Left Joystick
  const unsigned long  L_JOY_RIGHT_ARROW = 0xFFC23D; 
  const unsigned long  L_JOY_LEFT_ARROW = 0xFF22DD; 
  const unsigned long  L_JOY_UP_ARROW = 0xFF629D; 
  const unsigned long  L_JOY_DOWN_ARROW = 0xFFA857; 
//Right Joystick
  const unsigned long  R_JOY_RIGHT_ARROW = 0xFD50AF; 
  const unsigned long  R_JOY_LEFT_ARROW = 0xFD10EF; 
  const unsigned long  R_JOY_UP_ARROW = 0xFDA05F; 
  const unsigned long  R_JOY_DOWN_ARROW = 0xFDB04F; 
//Buttons
  const unsigned long  L_FACE_BUTTON = 0xFF02FD; 
  const unsigned long  R_FACE_BUTTON = 0xFF6897; 
  const unsigned long  L_TRIGGER_BUTTON = 0xFFB04F;
  const unsigned long  R_TRIGGER_BUTTON = 0xFF52AD;

const int H_JOY_L_PIN = A0;       //Left Horizontal Joystick Analog Pin
const int V_JOY_L_PIN = A1;       //Left Vertical Joystick Analog Pin 
const int H_JOY_R_PIN = A2;       //Right Horizontal Joystick Analog Pin
const int V_JOY_R_PIN = A3;       //Right Vertical Joystick Analog Pin 

const int PUSHBUTTON_FACE_L = 2;  //Pushbutton Digital Pin
const int PUSHBUTTON_FACE_R = 4;  //Pushbutton Digital Pin
const int PUSHBUTTON_TRIGGER_L = 7;  //Pushbutton Digital Pin
const int PUSHBUTTON_TRIGGER_R = 8;  //Pushbutton Digital Pin

//deadband values for the joysticks - values between DEADBANDLOW and DEADBANDHIGH will be ignored
const int DEADBANDLOW = 480;   //lower deadband value for the joysticks  
const int DEADBANDHIGH = 540;  //upper deadband value for the joysticks  

//State Variables
int buttonState1;             // the current state of the pushbuton
int lastButtonState1 = LOW;   // the previous reading from the input pin
int buttonState2;             // the current state of the pushbuton
int lastButtonState2 = LOW;   // the previous reading from the input pin
int buttonState3;             // the current state of the pushbuton
int lastButtonState3 = LOW;   // the previous reading from the input pin
int buttonState4;             // the current state of the pushbuton
int lastButtonState4 = LOW;   // the previous reading from the input pin

//Timing variables for button debouncing
long lastDebounceTime1 = 0;  // the last time the output pin was toggled. This variable is a 'long' because it may need to hold many milliseconds, and a 'long' will afford more space than an 'int'
long lastDebounceTime2 = 0;  // the last time the output pin was toggled. This variable is a 'long' because it may need to hold many milliseconds, and a 'long' will afford more space than an 'int'
long lastDebounceTime3 = 0;  // the last time the output pin was toggled. This variable is a 'long' because it may need to hold many milliseconds, and a 'long' will afford more space than an 'int'
long lastDebounceTime4 = 0;  // the last time the output pin was toggled. This variable is a 'long' because it may need to hold many milliseconds, and a 'long' will afford more space than an 'int'
int debounceDelay = 50;    // the amount of time that that a button must be held, for a reading to register (in milliseconds)

void setup()
{
  pinMode(PUSHBUTTON_FACE_L, INPUT);  //set the PUSHBUTTON Pin to an Input
  pinMode(PUSHBUTTON_FACE_R, INPUT);  //set the PUSHBUTTON Pin to an Input
  pinMode(PUSHBUTTON_TRIGGER_L, INPUT);  //set the PUSHBUTTON Pin to an Input
  pinMode(PUSHBUTTON_TRIGGER_R, INPUT);  //set the PUSHBUTTON Pin to an Input
  //Analog pins do not need to be initialized
}

void loop() 
{
  
  /************************** Button Reading and Debouncing *******************************/
  //When a user makes/breaks electrical contacts by pushing/releasing the pushbutton,
  //the signal can 'bounce' between LOW and HIGH. This may cause erratic behavior,
  //in this case toggling the laser on/off multiple times. To combat this, the sketch
  //will 'debounce' the button by reading multiple times over a period of time. If a 
  //button is read as 'high' for multiple successive reads, then the signal was an
  //actual button event.
  //See http://arduino.cc/en/Tutorial/Debounce
  
  int reading1 = digitalRead(PUSHBUTTON_FACE_L);  //read from the digital pin PUSHBUTTON - keep in mind that a HIGH reading might be a false reading, so it must be filtered through the debounce code

  //check if the current digitalRead() is different from the previous button state
  if (reading1 != lastButtonState1) 
  {
    lastDebounceTime1 = millis(); //a change was detected, so reset the debouncing timer by setting it to the current time
  } 

  //check if the amount of time that has passed between now and the lastDebounceTime is more than the
  //debounceDelay
  if ((millis() - lastDebounceTime1) > debounceDelay) 
  {
    //check if the button state has changed:
    if (reading1 != buttonState1) 
    {
      buttonState1 = reading1;  //the last digitalRead was correct, so set the butonState to the value of reading
      
      //check if the button's current state is HIGH(which signals the program to toggle the laser)
      if (buttonState1 == HIGH) 
      {
        My_Sender.send(NEC, L_FACE_BUTTON, 32); 
      }
    }
  }

  int reading2 = digitalRead(PUSHBUTTON_FACE_R);  //read from the digital pin PUSHBUTTON - keep in mind that a HIGH reading might be a false reading, so it must be filtered through the debounce code

  //check if the current digitalRead() is different from the previous button state
  if (reading2 != lastButtonState2) 
  {
    lastDebounceTime2 = millis(); //a change was detected, so reset the debouncing timer by setting it to the current time
  } 

  //check if the amount of time that has passed between now and the lastDebounceTime is more than the
  //debounceDelay
  if ((millis() - lastDebounceTime2) > debounceDelay) 
  {
    //check if the button state has changed:
    if (reading2 != buttonState2) 
    {
      buttonState2 = reading2;  //the last digitalRead was correct, so set the butonState to the value of reading
      
      //check if the button's current state is HIGH(which signals the program to toggle the laser)
      if (buttonState2 == HIGH) 
      {
        My_Sender.send(NEC, R_FACE_BUTTON, 32); 
      }
    }
  }


  int reading3 = digitalRead(PUSHBUTTON_TRIGGER_L);  //read from the digital pin PUSHBUTTON - keep in mind that a HIGH reading might be a false reading, so it must be filtered through the debounce code

  //check if the current digitalRead() is different from the previous button state
  if (reading3 != lastButtonState3) 
  {
    lastDebounceTime3 = millis(); //a change was detected, so reset the debouncing timer by setting it to the current time
  } 

  //check if the amount of time that has passed between now and the lastDebounceTime is more than the
  //debounceDelay
  if ((millis() - lastDebounceTime3) > debounceDelay) 
  {
    //check if the button state has changed:
    if (reading3 != buttonState3) 
    {
      buttonState3 = reading3;  //the last digitalRead was correct, so set the butonState to the value of reading
      
      //check if the button's current state is HIGH(which signals the program to toggle the laser)
      if (buttonState3 == HIGH) 
      {
        My_Sender.send(NEC, L_TRIGGER_BUTTON, 32); 
      }
    }
  }


  int reading4 = digitalRead(PUSHBUTTON_TRIGGER_R);  //read from the digital pin PUSHBUTTON - keep in mind that a HIGH reading might be a false reading, so it must be filtered through the debounce code

  //check if the current digitalRead() is different from the previous button state
  if (reading4 != lastButtonState4) 
  {
    lastDebounceTime4 = millis(); //a change was detected, so reset the debouncing timer by setting it to the current time
  } 

  //check if the amount of time that has passed between now and the lastDebounceTime is more than the
  //debounceDelay
  if ((millis() - lastDebounceTime4) > debounceDelay) 
  {
    //check if the button state has changed:
    if (reading4 != buttonState3) 
    {
      buttonState4 = reading4;  //the last digitalRead was correct, so set the butonState to the value of reading
      
      //check if the button's current state is HIGH(which signals the program to toggle the laser)
      if (buttonState4 == HIGH) 
      {
        My_Sender.send(NEC, R_TRIGGER_BUTTON, 32); 
      }
    }
  }
  
  lastButtonState1 = reading1;  //set the lastButtonState to the value of reading for the next loop
  lastButtonState2 = reading2;  //set the lastButtonState to the value of reading for the next loop
  lastButtonState3 = reading3;  //set the lastButtonState to the value of reading for the next loop
  lastButtonState4 = reading4;  //set the lastButtonState to the value of reading for the next loop

  /**************Servo Positions *******************************/
  //read the values from the joysticks
   int horizontalValueL = analogRead(H_JOY_L_PIN);
   int verticalValueL = analogRead(V_JOY_L_PIN);
   
     if(horizontalValueL < DEADBANDLOW)
     {
       My_Sender.send(NEC, L_JOY_RIGHT_ARROW, 32); 
       delay(10);
     }
    
     else if(horizontalValueL > DEADBANDHIGH)
     {
       My_Sender.send(NEC, L_JOY_LEFT_ARROW, 32);  
       delay(10);
     } 

     if(verticalValueL < DEADBANDLOW)
     {
       My_Sender.send(NEC, L_JOY_UP_ARROW, 32); 
       delay(10);
     }
    
     else if(verticalValueL > DEADBANDHIGH)
     {
       My_Sender.send(NEC, L_JOY_DOWN_ARROW, 32);  
       delay(10);
     }

   int horizontalValueR = analogRead(H_JOY_R_PIN);
   int verticalValueR = analogRead(V_JOY_R_PIN);
   
     if(horizontalValueR < DEADBANDLOW)
     {
       My_Sender.send(NEC, R_JOY_RIGHT_ARROW, 32); 
       delay(10);
     }
    
     else if(horizontalValueR > DEADBANDHIGH)
     {
       My_Sender.send(NEC, R_JOY_LEFT_ARROW, 32);  
       delay(10);
     } 

     if(verticalValueR < DEADBANDLOW)
     {
       My_Sender.send(NEC, R_JOY_UP_ARROW, 32); 
       delay(10);
     }
    
     else if(verticalValueR > DEADBANDHIGH)
     {
       My_Sender.send(NEC, R_JOY_DOWN_ARROW, 32);  
       delay(10);
     }

}

