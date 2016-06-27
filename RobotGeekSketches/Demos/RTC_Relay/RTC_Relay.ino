/****************************************************************************/	
//             Using a Real Time Clock - Relay Demonstration                //
/****************************************************************************/
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;//define a object of DS1307 class

const int RELAY = 4; //Relay set to digital pin 4

void setup()
{
  pinMode(RELAY, OUTPUT);
	clock.begin();
}
void loop()
{
	timedRelay();
}

void timedRelay()
{
	clock.getTime();

  switch (clock.second)
  {
    case 30: //when the clock reads 30 seconds (Once a minute at the halfway mark)
      digitalWrite(RELAY, HIGH);   // turn the Relay on (HIGH is the voltage level)
      delay(1000);              // wait for 1 second
      digitalWrite(RELAY, LOW);    // turn the Relay off by making the voltage LOW
      delay(1000);              // wait for 1 second
  }
  
	switch (clock.dayOfWeek)
	{
		case MON: //on Monday
      switch (clock.hour)
      {
        case 14: //at 2 o'clock
          switch (clock.minute)
          {
            case 30: //at 30 minutes
              switch (clock.second)
              {
                case 1: //at 1 second
                  digitalWrite(RELAY, HIGH);   // turn the Relay on (HIGH is the voltage level)
                  delay(5000);              // wait for 5 seconds
                  digitalWrite(RELAY, LOW);    // turn the Relay off by making the voltage LOW
                  delay(5000);              // wait for 5 seconds
              }
          }
      }
	}
}
