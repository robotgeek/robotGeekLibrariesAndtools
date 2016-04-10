/*
WiiClassic LED Code

*/

#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

const int BUZZER_PIN = 3;
const int FREQ_MIN = 31;
const int FREQ_MAX = 65535;

const int DEADBAND_LOW = 120;
const int DEADBAND_HIGH = 136;

int frequency;

int frequencyIncrement;

int frequencyInterval = 1000;

void setup() 
{
  nunchuk.init();  //start classy library
  delay(100);
  nunchuk.update();  //read data from the classic controller
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() 
{
  
  nunchuk.update();//read data from the classic controller
  
  if(classy.analogX > DEADBAND_HIGH || classy.analogX < DEADBAND_LOW)
  {
    frequencyIncrement = map(classy.analogX, 0, 255, -1*frequencyInterval, frequencyInterval );
    frequency = frequency + frequencyIncrement;
  }

  if(classy.pitch> DEADBAND_HIGH || classy.pitch < DEADBAND_LOW)
  {
    frequencyIncrement = map(classy.pitch, 0, 255, -1*frequencyInterval, frequencyInterval );
    frequency = frequency + frequencyIncrement;
  }

  
  if (classy.zButton == true) 
  {
    frequency = 300;
  }
  if (classy.cButton == true) 
  {
    frequency = 10000;
  }

  
  tone(BUZZER_PIN, frequency);
  
  
  

}
