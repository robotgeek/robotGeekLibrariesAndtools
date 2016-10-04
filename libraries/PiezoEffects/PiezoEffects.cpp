//Adapted from: https://github.com/bq/zowiLibs and other sources.

#include <Arduino.h>
#include "PiezoEffects.h"

PiezoEffects::PiezoEffects( int pinNumber )
{
  _speakerPin = pinNumber;
  pinMode( _speakerPin, OUTPUT );
}

PiezoEffects::PiezoEffects( int pinNumber, int ledA, int ledB )
{
  _speakerPin = pinNumber;
  pinMode( _speakerPin, OUTPUT );
  _ledPinA = ledA;
  _ledPinB = ledB;
  pinMode( _ledPinA, OUTPUT );
  pinMode( _ledPinB, OUTPUT );
  _flashLEDs = true;
}

void PiezoEffects::play( int soundID )
{
  switch( soundID )
  {
  case soundUp:
    _tone( note_C7, 50, 0 );
    _tone( note_D7, 50, 0 );
    _tone( note_E7, 50, 0 );
    _tone( note_F7, 50, 0 );
    _tone( note_G7, 50, 0 );
    _tone( note_A7, 50, 0 );
    _tone( note_B7, 50, 0 );
    _tone( note_C8, 50, 0 );
    break;
  case soundDown:
    _tone( note_C8, 50, 0 );
    _tone( note_B7, 50, 0 );
    _tone( note_A7, 50, 0 );
    _tone( note_G7, 50, 0 );
    _tone( note_F7, 50, 0 );
    _tone( note_E7, 50, 0 );
    _tone( note_D7, 50, 0 );
    _tone( note_C7, 50, 0 );
    break;
  case soundBeeps:
    _tone( note_A7, 100, 0 );
    _tone( note_G7, 100, 0 );
    _tone( note_E7, 100, 0 );
    _tone( note_C7, 100, 0 );
    _tone( note_D7, 100, 0 );
    _tone( note_B7, 100, 0 );
    _tone( note_F7, 100, 0 );
    _tone( note_C8, 100, 0 );
    _tone( note_A7, 100, 0 );
    _tone( note_G7, 100, 0 );
    _tone( note_E7, 100, 0 );
    _tone( note_C7, 100, 0 );
    _tone( note_D7, 100, 0 );
    _tone( note_B7, 100, 0 );
    _tone( note_F7, 100, 0 );
    _tone( note_C8, 100, 0 );
    break;

  case soundWhistle:
    for (int i = 1000; i < 5000; i = i * 1.05)
    {
      _tone(i, 10, 0);
    }
    delay(200);

    for (int i = 1000; i < 3000; i = i * 1.03)
    {
      _tone(i, 10, 0);
    }
    for (int i = 3000; i > 1000; i = i * .97)
    {
      _tone(i, 10, 0);
    }
    break;

  case soundOhh:
    for (int i = 1000; i < 2000; i = i * 1.02)
    {
      _tone(i, 10, 0);
    }
    for (int i = 2000; i > 1000; i = i * .98)
    {
      _tone(i, 10, 0);
    }
    break;
  case soundUhoh:
    for (int i = 1000; i < 1044; i = i * 1.01)
    {
      _tone(i, 30, 0);
    }
    delay(100);
    for (int i = 1244; i > 1108; i = i * .99)
    {
      _tone(i, 30, 0);
    }
    break;
  case soundLaugh:
    for (int i = 1000; i < 2000; i = i * 1.10)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i > 500; i = i * .90)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i < 2000; i = i * 1.10)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i > 500; i = i * .90)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i < 2000; i = i * 1.10)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i > 500; i = i * .90)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i < 2000; i = i * 1.10)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    for (int i = 1000; i > 500; i = i * .90)
    {
      _tone(i, 10, 0);
    }
    delay(50);
    break;

  case soundConnection:
    _tone(note_E5, 50, 30);
    _tone(note_E6, 55, 25);
    _tone(note_A6, 60, 10);
    break;

  case soundDisconnection:
    _tone(note_E5, 50, 30);
    _tone(note_A6, 55, 25);
    _tone(note_E6, 50, 10);
    break;

  case soundButtonPushed:
    bendTones (note_E6, note_G6, 1.03, 20, 2);
    delay(30);
    bendTones (note_E6, note_D7, 1.04, 10, 2);
    break;

  case soundMode1:
    bendTones (note_E6, note_A6, 1.02, 30, 10); //1318.51 to 1760
    break;

  case soundMode2:
    bendTones (note_G6, note_D7, 1.03, 30, 10); //1567.98 to 2349.32
    break;

  case soundMode3:
    _tone(note_E6, 50, 100); //D6
    _tone(note_G6, 50, 80); //E6
    _tone(note_D7, 300, 0); //G6
    break;

  case soundSurprise:
    bendTones(800, 2150, 1.02, 10, 1);
    bendTones(2149, 800, 1.03, 7, 1);
    break;

  case soundOhOoh:
    bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
    delay(200);

    for (int i = 880; i < 2000; i = i * 1.04)
    {
      _tone(note_B5, 5, 10);
    }
    break;

  case soundOhOoh2:
    bendTones(1880, 3000, 1.03, 8, 3);
    delay(200);

    for (int i = 1880; i < 3000; i = i * 1.03)
    {
      _tone(note_C6, 10, 10);
    }
    break;

  case soundCuddly:
    bendTones(700, 900, 1.03, 16, 4);
    bendTones(899, 650, 1.01, 18, 7);
    break;

  case soundSleeping:
    bendTones(100, 500, 1.04, 10, 10);
    delay(500);
    bendTones(400, 100, 1.04, 10, 1);
    break;

  case soundHappy:
    bendTones(1500, 2500, 1.05, 20, 8);
    bendTones(2499, 1500, 1.05, 25, 8);
    break;

  case soundSuperHappy:
    bendTones(2000, 6000, 1.05, 8, 3);
    delay(50);
    bendTones(5999, 2000, 1.05, 13, 2);
    break;

  case soundHappyShort:
    bendTones(1500, 2000, 1.05, 15, 8);
    delay(100);
    bendTones(1900, 2500, 1.05, 10, 8);
    break;

  case soundSad:
    bendTones(880, 669, 1.02, 20, 200);
    break;

  case soundConfused:
    bendTones(1000, 1700, 1.03, 8, 2);
    bendTones(1699, 500, 1.04, 8, 3);
    bendTones(1000, 1700, 1.05, 9, 10);
    break;

  case soundInsect1:
    bendTones(1600, 3000, 1.02, 2, 15);
    break;

  case soundInsect2:
    bendTones(2000, 6000, 1.02, 2, 20);
    break;

  case soundInsect3:
    bendTones(1600, 4000, 1.02, 2, 20);
    bendTones(4000, 3000, 1.02, 2, 20);
    break;

  }
}

void PiezoEffects::_tone( float noteFrequency, long noteDuration, int silentDuration )
{
  int x;
  float microsecondsPerWave = 1000000 / noteFrequency;
  float millisecondsPerCycle = 1000 / (microsecondsPerWave * 2);
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x = 0; x < loopTime; x++)
  {
    if ( _flashLEDs )
    {
      digitalWrite(_ledPinA, HIGH);
      digitalWrite(_ledPinB, HIGH);
    }
    digitalWrite(_speakerPin, HIGH);
    delayMicroseconds(microsecondsPerWave);
    if ( _flashLEDs )
    {
      digitalWrite(_ledPinA, LOW);
      digitalWrite(_ledPinB, LOW);
    }
    digitalWrite(_speakerPin, LOW);
    delayMicroseconds(microsecondsPerWave);
  }

  if ( silentDuration )
  {
    delay(noteDuration); //milliseconds to microseconds
    delay(silentDuration);
  }
}

void PiezoEffects::bendTones( float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration )
{
  //Examples:
  //  bendTones (880, 2093, 1.02, 18, 1);
  //  bendTones (note_A5, note_C7, 1.02, 18, 0);

  if(silentDuration == 0)
  {
    silentDuration = 1;
  }

  if(initFrequency < finalFrequency)
  {
    for (int i = initFrequency; i < finalFrequency; i = i * prop)
    {
      _tone(i, noteDuration, silentDuration);
    }
  }
  else
  {
    for (int i = initFrequency; i > finalFrequency; i = i / prop)
    {
      _tone(i, noteDuration, silentDuration);
    }
  }
}

void PiezoEffects::setLEDPins( int pinA, int pinB )
{
  _ledPinA = pinA;
  _ledPinB = pinB;
}

bool PiezoEffects::toggleFlashingLEDs()
{
  _flashLEDs = !_flashLEDs;
  return _flashLEDs;
}
