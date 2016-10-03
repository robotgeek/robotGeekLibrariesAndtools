#include <PiezoEffects.h>

PiezoEffects mySounds( 13 );

void setup() {}

void loop()
{
	mySounds.play( soundUp );
	mySounds.play( soundDown );
	mySounds.play( soundWhistle );
	mySounds.play( soundLaugh );
	mySounds.play( soundOhh );
	mySounds.play( soundUhoh );
	mySounds.play( soundBeeps );
	mySounds.play( soundConnection );
	mySounds.play( soundDisconnection );
	mySounds.play( soundButtonPushed );
	mySounds.play( soundMode1 );
	mySounds.play( soundMode2 );
	mySounds.play( soundMode3 );
	mySounds.play( soundSurprise );
	mySounds.play( soundOhOoh );
	mySounds.play( soundOhOoh2 );
	mySounds.play( soundCuddly );
	mySounds.play( soundSleeping );
	mySounds.play( soundHappy );
	mySounds.play( soundSuperHappy );
	mySounds.play( soundHappyShort );
	mySounds.play( soundSad );
	mySounds.play( soundConfused );
	mySounds.play( soundInsect1 );
	mySounds.play( soundInsect2 );
	mySounds.play( soundInsect3 );
}
