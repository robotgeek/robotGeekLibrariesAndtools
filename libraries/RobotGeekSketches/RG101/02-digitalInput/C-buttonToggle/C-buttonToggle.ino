/*****************************************************************************************
 *    RG 101 - Digital Input     _____
 *     Button Toggle            |  _  |
 *                              | |_| |
 *                              |_____| 
 *           
 *  This code will toggle an LED whenever the button is pressed. It will use a technique
 *  called 'debouncing' to make sure the button has been pressed.
 *  
 * For a more in depth explanation of wiring,  this code and more information on using 
 * Digital outputs and Arduino check out our Digital Output Tutorial
 * http://learn.robotgeek.com/robotgeek-101-1/230-digital-input-primer.html
 *  
 * Important Functions
 *  pinMode()
 *  digitalRead()
 *  digitalWrite()
 *  millis()
 *  
 *  Code based on Arduino.cc debounce coude
 *  https://www.arduino.cc/en/Tutorial/Debounce
 *****************************************************************************************/

const int BUTTON_PIN = 2;      //pin number for the button - this is 'const' since it will not change during code, and saves Arduino memory
const int LED_PIN = 4;         //pin number for the LED - this is 'const' since it will not change during code, and saves Arduino memory
const int DEBOUNCE_DELAY = 50; //minimum time(ms) for button press - increase if output is flickering or not working as expected

//boolean variables store the stated for Digital I/O
bool buttonState;           //holds the current state of the button, HIGH or LOW
bool ledState = HIGH;       //holds the current state of the LED, HIGH or LOW
bool lastButtonState;       //holds the last known state of the button, HIGH or LOW
bool tempButtonState;       //holds a temporary read of the button state

unsigned long lastTransitionTime;   //last time a transition was noticed

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  pinMode(BUTTON_PIN, INPUT);  //set button pin to input 
  pinMode(LED_PIN, OUTPUT);    //set led pin to output 
  
  // set initial LED state
  digitalWrite(LED_PIN, ledState); //set led to the current led state in memory
  
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  tempButtonState = digitalRead(BUTTON_PIN);  //read the button pin into a temporary variable for examination

    //if the temporary state we just read is different from the read on the last loop, proceed
    if(tempButtonState != lastButtonState)
    {
      lastTransitionTime = millis();  //because the read from this loop is different from the last loop, reset the variable keeping track of the last transition
    }

    //find the difference between the last transition time and the current time. If this time is more than DEBOUNCE_DELAY, then the button has stayed on its current output for an acceptable amount of time and we can proceed
    if((millis() - lastTransitionTime) > DEBOUNCE_DELAY)
    {
      //if the temporary button state is different from the last known button state, proceed
      if(tempButtonState != buttonState)
      {
        buttonState = tempButtonState;//change the button state to the temporary variables value, the last read

        //if the current button state is high, the button is pressed
        if(buttonState == HIGH)
        {
          ledState = !ledState;             //change the state of the led in memory using the ! operator to toggle it. HIGH becomes LOW and LOW becomes HIGH
          digitalWrite(LED_PIN, ledState);  //write the led state from memory to the physical pin
        }
        else
        {
          //you can put code here if you want something to happen when you let go of the button
        }
      }
      
    }
    
  lastButtonState = tempButtonState;  //store the temporary variable as the last button state
   
  
}//go back to the first line in loop()
