/********************************************************************************
 * RobotGeek RoboTurret IR Control Example
 * 
 * This sketch will allow you to control a RoboTurret with Foam Dart Gun accessory
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


IRrecv My_Receiver(11);    // Receive Pin
IRdecode My_Decoder;       // decoder object
Servo triggerServo;        // create servo object to control a servo 
Servo panServo;            // create servo object to control a servo 
Servo tiltServo;           // create servo object to control a servo 
int panPos;                // variable to store the pan servo position 
int tiltPos;               // variable to store the tilt servo position 
int triggerPos;            // variable to store the trigger servo position 
int Speed;                 // Number of degrees to move each time a left/right button is pressed
unsigned long lastCommand; // last command sent from IR remote
 
void setup() 
{ 
  My_Receiver.No_Output();        // Turn off any unused IR LED output circuit
  triggerServo.attach(3);         // attaches the servo on pin 3 to the servo object 
  panServo.attach(5);             // attaches the servo on pin 5 to the servo object 
  tiltServo.attach(6);            // attaches the servo on pin 6 to the servo object 
  triggerPos = 90;                // start at midpoint 90 degrees
  panPos = 90;                    // start at midpoint 90 degrees
  tiltPos = 90;                   // start at midpoint 90 degrees
  Speed = 3;                      // servo moves 3 degrees each time left/right is pushed
  triggerServo.write(triggerPos); // Set initial position
  panServo.write(panPos);         // Set initial position
  tiltServo.write(tiltPos);       // Set initial position
  My_Receiver.enableIRIn();       // Start the receiver
  
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
          panPos=min(180,panPos+Speed); // turn pan servo left
         }

         else if(lastCommand == RIGHT_BUTTON) // if the last command sent is the right arrow
         {
          panPos=max(0,panPos-Speed); // turn pan servo right
         }

         else if(lastCommand == SELECT_BUTTON) // if the last command sent is the select/enter button
         {
          panPos=90;  // center pan servo
          tiltPos=90; // center tilt servo
         }

         else if(lastCommand == UP_BUTTON)  // if the last command sent is the up arrow
         {
          tiltPos=min(180,tiltPos+Speed); // tilt servo aims up, tilts back
         }

         else if(lastCommand == DOWN_BUTTON) // if the last command sent is the down arrow
         {
          tiltPos=max(0,tiltPos-Speed); // tilt servo aims down, tilts forward
         }

         else if(lastCommand == ONE_BUTTON) //if the last command sent is the 1 button
         {
           digitalWrite(2, HIGH); // turn LED on
           delay(200);            // for 200ms
           digitalWrite(2, LOW);  // turn LED off
         }

         else if(lastCommand == TWO_BUTTON) //if the last command sent is the 2 button
         {
           triggerServo.write(113); // trigger servo to fire position
           delay(300);              // for 300ms
           triggerServo.write(90);  // trigger to neutral position
           delay(300);              // wait 300ms
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
        panServo.write(panPos);         // tell servo to go to position in variable 'panPos' 
        tiltServo.write(tiltPos);       // tell servo to go to position in variable 'tiltPos' 
       }
     My_Receiver.resume(); 
    }
}
