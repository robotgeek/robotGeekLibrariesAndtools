/* Example program for from IRLib – an Arduino library for infrared encoding and decoding
 * IRhexSerial
 */
#include <IRLib.h>
/* Note: Servo library uses TIMER1. The default timer for IRLib on Arduino Uno
 * is TIMER2 so there is no conflict. However a default timer on Arduino Leonardo
 * is TIMER1 so you will have to modify the timer used to use TIMER3 or TIMER4
 * as specified in IRLibTimer.h. Also you will need to modify the input being used.
 */
// Set your protocol
#define MY_PROTOCOL NEC


IRrecv My_Receiver(11); //Receive Pin
IRdecode My_Decoder; 
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("Press some buttons - Receive Hex values");
  My_Receiver.No_Output();//Turn off any unused IR LED output circuit
  My_Receiver.enableIRIn(); // Start the receiver
} 
 
void loop() 
{ 
    if (My_Receiver.GetResults(&My_Decoder)) {
       My_Decoder.decode();
       if(My_Decoder.decode_type==MY_PROTOCOL) {
          Serial.println(My_Decoder.value, HEX);
       }
     My_Receiver.resume();
    }
}

