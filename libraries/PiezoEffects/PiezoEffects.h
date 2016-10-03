#ifndef PIEZOEFFECTS_H
#define PIEZOEFFECTS_H

#include "NoteFreqs.h"

enum SoundIDs
{
	soundUp,
	soundDown,
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
		void play( int soundID );

	private:
		int _speakerPin;
		void _tone( float noteFrequency, long noteDuration, int silentDuration );
		void bendTones( float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration );
};

#endif
