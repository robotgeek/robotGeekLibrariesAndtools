/****************************************************************************	
 *                  Automatic Plant Watering System Demo                    *
 *                                                                          *
 * This demonstration shows the use of a Real Time Clock in conjunction     *
 * with moisture sensors to activate a pump that will intelligently water   *
 * plants!                                                                  *
 *                                                                          *
 * Project Parts list:                                                      *
 * - 1 x RobotGeek Relay (http://www.robotgeek.com/robotgeek-relay)         *
 * - 1 x RobotGeek LED (http://www.robotgeek.com/robotgeek-led-driver)      *
 * - 3 x DFRobot Moisture sensor (http://www.dfrobot.com/index.php?route=product/product&product_id=1385#.V4PAqPkrJhE)
 * - 1 x Grove RTC (http://www.seeedstudio.com/wiki/Grove_-_RTC)            *
 * - 1 x DC Liquid Pump (http://www.robotgeek.com/large-liquid-pump)        *
 * - 1 x 9mm Push Button (http://www.robotgeek.com/9mm-push-button)         *
 * - Clear Silicone Tubing (http://www.robotgeek.com/silicone_tubing)       *
 * - 4 x 4-Outlet Splitter (https://www.amazon.com/Outlets-Control-Splitter-Lever-Valve/dp/B00O9W96PU/ref=sr_1_41)
 * - 1 x 12V5A Power supply (http://www.robotgeek.com/p/power-supply-12vdc-5a.aspx)
 * - 1 x DC Power Squid (http://www.robotgeek.com/dc-squid)                 *
 *                                                                          *
 * AIO-0 - DFRobot Moisture Sensor                                          *
 * AIO-1 - DFRobot Moisture Sensor                                          *
 * AIO-2 - DFRobot Moisture Sensor                                          *
 * DIO-4 - RobotGeek Relay with Pump                                        *
 * DIO-7 - RobotGeek LED Driver                                             *
 * I2C   - Grove RTC                                                        *
 *                                                                          *
 ****************************************************************************/
 
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;               //define a object of DS1307 class

const int RELAY      = 4;   // Relay set to digital pin 4
const int LED        = 7;   // LED on digital pin 7
const int MOISTURE_1 = A0;  // Analog input pin that the potentiometer is attached to
const int MOISTURE_2 = A1;  // Analog input pin that the potentiometer is attached to
const int MOISTURE_3 = A2;  // Analog input pin that the potentiometer is attached to

int moist1Value = 0;        // value read from the pot
int moist2Value = 0;        // value read from the pot
int moist3Value = 0;        // value read from the pot
int moistAvg    = 0;        // average of all sensor values

// if your plants seem like they're getting over watered, raise the dry limit (eg: dryLimit = 450;)
// if your plants seem like they're not getting enough water, lower the dry limit (eg: dryLimit = 400;)
// by default it is set to 420 based on testing with our tomatoes, but test it out and set it to what works best for your plants
int dryLimit    = 420;      // how dry you will allow your plants to be on average

void setup()
{
  pinMode(RELAY, OUTPUT);   // set relay pin to output
  pinMode(LED, OUTPUT);     // set led pin to output
	clock.begin();            // start reading the RTC
  Serial.begin(9600);       // start the serial at 9600 baud
}
void loop()
{
	timedRelay();             // we will be doing everything in the timedRelay function
}

// here's where the magic happens:
void timedRelay()
{
	clock.getTime(); //grab the time from the RTC every clock cycle

  // Check every minute to see that the moisture level is where you want it, water if it's too dry
  switch (clock.second) // When the time on the RTC reads a value in seconds
  {
    case 30: // at the 30 second mark
      delay(2);
      // read the analog value of the first sensor:
      moist1Value = analogRead(MOISTURE_1);
      // print the results to the serial monitor:
      Serial.print("sensor 0 = ");
      Serial.print(moist1Value);
      Serial.println("  ");
      delay(2);
      // read the analog value of the second sensor:
      moist2Value = analogRead(MOISTURE_2);
      // print the results to the serial monitor:
      Serial.print("sensor 1 = ");
      Serial.print(moist2Value);
      Serial.println("  ");
      delay(2);
      // read the analog value of the third sensor:
      moist3Value = analogRead(MOISTURE_3);
      // print the results to the serial monitor:
      Serial.print("sensor 2 = ");
      Serial.print(moist3Value);
      Serial.println("  ");
      delay(2);
      // average all of those values to determine if all the plants in the system are too dry.
      moistAvg = (moist1Value + moist2Value + moist3Value)/3;
      Serial.print("sensor average = ");
      Serial.print(moistAvg);
      Serial.println("  ");
      delay(2);
      
      // if the plants are on average too dry, run the pump for 10 seconds.
      if(moistAvg >= dryLimit)
      {
        digitalWrite(LED, HIGH);     // turn the LED on (HIGH is the voltage level)
        digitalWrite(RELAY, HIGH);   // turn the Relay on (HIGH is the voltage level)
        delay(10000);                // wait for 10 seconds
        digitalWrite(RELAY, LOW);    // turn the Relay off by making the voltage LOW
        digitalWrite(LED, LOW);      // turn the LED off by making the voltage LOW
        delay(1000);                 // wait for 1 second
      }
      delay(1000); // let the second pass to avoid multiple readings over serial
  }

  // Once a day at 11:00:01, water the plants regardless of moisture levels indicated
	switch (clock.hour)
	{
		case 11: //at 11AM
      switch (clock.minute)
      {
        case 0: //at 0 minutes
          switch (clock.second)
          {
            case 1: //at 1 second
              digitalWrite(LED, HIGH);     // turn the LED on (HIGH is the voltage level)
              digitalWrite(RELAY, HIGH);   // turn the Relay on (HIGH is the voltage level)
              delay(10000);                // wait for 10 seconds
              digitalWrite(LED, LOW);      // turn the LED off by making the voltage LOW
              digitalWrite(RELAY, LOW);    // turn the Relay off by making the voltage LOW
              delay(1000);                 // wait for 1 second
          }
      }
	}
}
