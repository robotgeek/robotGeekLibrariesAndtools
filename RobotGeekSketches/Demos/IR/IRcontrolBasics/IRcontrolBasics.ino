/********************************************************************************
 * RobotGeek Basic IR Control Example
 * 
 * This sketch will allow you to control a servo and two LEDs in different ways
 * using an InfraRed Remote, configured with the IRremoteWizard Sketch, defined in
 * remotes.h.
 * 
 * 
 * 
 ********************************************************************************/
#include <IRLib.h>
#include <Servo.h> 
#include "remotes.h"

/* Note: Servo library uses TIMER1. The default timer for IRLib on Arduino Uno
 * is TIMER2 so there is no conflict. However a default timer on Arduino Leonardo
 * is TIMER1 so you will have to modify the timer used to use TIMER3 or TIMER4
 * as specified in IRLibTimer.h. Also you will need to modify the input being used.
 */

const int LED_1 = 2;       // LED to be digitally controlled on pin 2
const int LED_2 = 5;       // LED for PWM control on pin 9
int brightness;        // how bright the LED is
int fadeAmount;        // how many points to fade the LED by

IRrecv My_Receiver(11);    // Receive Pin
IRdecode My_Decoder;       // decoder object
Servo triggerServo;        // create servo object to control a servo 
int triggerPos;            // variable to store the trigger servo position 
int Speed;                 // Number of degrees to move each time a left/right button is pressed

unsigned long lastCommand; // last command sent from IR remote
 
void setup() 
{ 
  My_Receiver.No_Output();        // Turn off any unused IR LED output circuit
  triggerServo.attach(6);         // attaches the servo on pin 3 to the servo object 
  triggerPos = 90;                // start at midpoint 90 degrees
  Speed = 3;                      // servo moves 3 degrees each time left/right is pushed
  triggerServo.write(triggerPos); // Set initial position
  My_Receiver.enableIRIn();       // Start the receiver

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  brightness = 0;                 // Start the LED LOW
  fadeAmount = 5;                 // set LED fade to 1
  
  Serial.begin(9600);             // start serial at 9600 baud
  Serial.println("startup");      // print a line when system is ready
  Serial.println(MY_PROTOCOL);    // print the remote protocol on startup
} 
 
void loop() 
{ 
    if (My_Receiver.GetResults(&My_Decoder)) // read signal from decoder object
    {
       My_Decoder.decode();
       if(My_Decoder.decode_type == MY_PROTOCOL) // if decoder is using the set protocol
       {
         Serial.println(lastCommand, HEX); // print last command to serial for debugging

         if(My_Decoder.value != REPEATING) // if the decoder value received is not the NEC Repeat code (0xFFFFFFFF)
         {
           lastCommand = My_Decoder.value; // variable lastCommand gets set to the decoder value
         }

         if(lastCommand == LEFT_BUTTON) // if the last command sent is the left arrow
         {
          triggerPos=min(180,triggerPos+Speed); // turn pan servo left
         }

         else if(lastCommand == RIGHT_BUTTON) // if the last command sent is the right arrow
         {
          triggerPos=max(0,triggerPos-Speed); // turn pan servo right
         }

         else if(lastCommand == SELECT_BUTTON) // if the last command sent is the select/enter button
         {
          triggerPos=90;  // center pan servo
         }

         else if(lastCommand == UP_BUTTON)  // if the last command sent is the up arrow
         {
          brightness = min((brightness + fadeAmount), 255); // Brighten LED
         }

         else if(lastCommand == DOWN_BUTTON) // if the last command sent is the down arrow
         {
          brightness = max((brightness - fadeAmount), 0); // Darken LED
         }

         else if(lastCommand == ONE_BUTTON) //if the last command sent is the 1 button
         {
           digitalWrite(LED_1, HIGH); // turn LED on
         }

         else if(lastCommand == TWO_BUTTON) //if the last command sent is the 2 button
         {
           digitalWrite(LED_1, LOW);  // turn LED off
         }

         else if(lastCommand == SPECIAL_2_BUTTON) // if the last command sent is the volume up button
         {
          Speed=min(10, Speed+1); // increase the speed of all servo movements
         }

         else if(lastCommand == SPECIAL_1_BUTTON) // if the last command sent is the volume down button
         {
          Speed=max(1, Speed-1); // decrease the speed of all servo movements
         }
        triggerServo.write(triggerPos); // tell servo to go to position in variable 'triggerPos'
        analogWrite(LED_2, brightness); // write the brightness of the LED 
       }
     My_Receiver.resume(); 
    }
}
