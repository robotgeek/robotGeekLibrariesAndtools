/*

Controlling a Solenoid with Arduino

This demo shows how to control a solenoid using pushbuttons and a relay with
your Arduino compatable controller.
 - The first button will hold the solenoid/relay on while it is held
 - The second button will hold the solenoid/relay on for 2 seconds
 
 
 The circuit:
 * RobotGeek Pushbutton - Digital Pin 2
 * RobotGeek Pushbutton - Digital Pin 4
 * RobotGeek Pushbutton - Digital Pin 7
 * RobotGeek Relay - Digital Pin 8
 * RobotGeek Relay - Digital Pin 12
 * RobotGeek Relay - Digital Pin 13
 
Products Used in this demo:
 - http://www.robotgeek.com/solenoids
 - http://www.robotgeek.com/robotgeek-geekduino-sensor-kit
 - http://www.robotgeek.com/robotGeek-pushbutton
 - http://www.robotgeek.com/robotgeek-relay

 */

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 2;     // the number of the pushbutton1 pin
const int button2Pin = 4;     // the number of the pushbutton2 pin
const int button3Pin = 7;     // the number of the pushbutton3 pin
const int relay1Pin =  8;      // the number of the Relay1 pin
const int relay2Pin =  12;      // the number of the Relay2 pin
const int relay3Pin =  13;      // the number of the Relay3 pin

// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status
int button3State = 0;         // variable for reading the pushbutton status

void setup() { 
  
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);     
  pinMode(button2Pin, INPUT);     
  pinMode(button3Pin, INPUT);    
  // initialize the relay pin as an output:
  pinMode(relay1Pin, OUTPUT);    
  pinMode(relay2Pin, OUTPUT);    
  pinMode(relay3Pin, OUTPUT);    
   
}

void loop(){
  
  // read the state of the pushbutton values:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  // check if the pushbutton1 is pressed.
  // if it is we turn on the small relay/solenoid
  if (button1State == HIGH) {     
    // turn relay on:    
    digitalWrite(relay1Pin, HIGH);  
  } 
  // When we let go of the button, turn off the relay
  else if ((button1State == LOW) && (digitalRead(relay1Pin) == HIGH)) {
    // turn relay off
    digitalWrite(relay1Pin, LOW); 
  }  
  
  // check if the pushbutton2 is pressed.
  // if it is we turn on the small relay/solenoid
  if (button2State == HIGH) {     
    // turn relay on:    
    digitalWrite(relay2Pin, HIGH);  
  } 
  // When we let go of the button, turn off the relay
  else if ((button2State == LOW) && (digitalRead(relay2Pin) == HIGH)) {
    // turn relay off
    digitalWrite(relay2Pin, LOW); 
  }  

  // check if the pushbutton3 is pressed.
  // if it is we turn on the small relay/solenoid
  if (button3State == HIGH) {     
    // turn relay on:    
    digitalWrite(relay3Pin, HIGH);  
  } 
  // When we let go of the button, turn off the relay
  else if ((button3State == LOW) && (digitalRead(relay3Pin) == HIGH)) {
    // turn relay off
    digitalWrite(relay3Pin, LOW); 
  }  

}
