#ifndef PIEZOEFFECTS_H
#define PIEZOEFFECTS_H

#include "NoteFreqs.h"

enum SoundIDs
{
	soundUp,
	soundDown,
	soundOneBeep,
	soundWhistle,
	soundLaugh,
	soundOhh,
	soundUhoh,
	soundBeeps,
	soundConnection,
	soundDisconnection,
	soundButtonPushed,
	soundMode1,
	soundMode2,
	soundMode3,
	soundSurprise,
	soundOhOoh,
	soundOhOoh2,
	soundCuddly,
	soundSleeping,
	soundHappy,
	soundSuperHappy,
	soundHappyShort,
	soundSad,
	soundConfused,
	soundInsect1,
	soundInsect2,
	soundInsect3
};

class PiezoEffects
{
	public:
		PiezoEffects( int pinNumber );
		PiezoEffects( int pinNumber, int ledA, int ledB );
		void play( int soundID );

		bool toggleFlashingLEDs();
		void setLEDPins( int pinA, int pinB );

	private:
		int _speakerPin;
		bool _flashLEDs;
		int _ledPinA = -1;
		int _ledPinB = -1;
		void _tone( float noteFrequency, long noteDuration, int silentDuration );
		void bendTones( float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration );
};

#endif
