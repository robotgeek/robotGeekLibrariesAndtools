/*
WiiClassic LED Code

*/

#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

const int BUZZER_PIN = 3;
const unsigned int FREQ_MIN = 31;
const unsigned int FREQ_MAX = 65535;

const int DEADBAND_LOW = 108;
const int DEADBAND_HIGH = 148;

int frequency = 300;

int frequencyIncrement;

int frequencyInterval = 1;

void setup() 
{
  nunchuk.init();  //start nunchuk library
  delay(100);
  nunchuk.update();  //read data from the classic controller
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() 
{
  
  nunchuk.update();//read data from the classic controller
  
  if(nunchuk.analogX > DEADBAND_HIGH || nunchuk.analogX < DEADBAND_LOW)
  {
    frequencyIncrement = map(nunchuk.analogX, 0, 255, -1*frequencyInterval, frequencyInterval );
    frequency = frequency + frequencyIncrement;
  }

//  if(nunchuk.pitch> DEADBAND_HIGH || nunchuk.pitch < DEADBAND_LOW)
//  {
//    frequencyIncrement = map(nunchuk.pitch, 0, 255, -1*frequencyInterval, frequencyInterval );
//    frequency = frequency + frequencyIncrement;
//  }

  
  if (nunchuk.zButton == true) 
  {
    frequency = 300;
  }
  if (nunchuk.cButton == true) 
  {
    frequency = 10000;
  }

  frequency = constrain(frequency, FREQ_MIN, FREQ_MAX);
  
  tone(BUZZER_PIN, frequency);
  
  
  

}