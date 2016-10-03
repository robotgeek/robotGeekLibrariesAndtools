#include <PiezoEffects.h>

const int speakerPin = 13; //Digital Pin 13
const int firstLED = 2; //Digital Pin 2
const int secondLED = 4; //Digital Pin 4

//Instantiating mySounds with LED pins specified will automatically set pinMode and enable LED flashing
PiezoEffects mySounds( speakerPin, firstLED, secondLED );

void setup()
{
	//You can also switch LED pins at runtime. Be careful to have first set pinMode in this situation.
	//mySounds.setLEDPins( firstLED, secondLED );
}

void loop()
{
	mySounds.play( soundUp );

	mySounds.toggleFlashingLEDs(); //Turn LED flashing off

	mySounds.play( soundDown );
	mySounds.play( soundWhistle );
	mySounds.play( soundLaugh );

	mySounds.toggleFlashingLEDs(); //Turn LED flashing back on

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
