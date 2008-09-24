/*
 *  TraktorConfiguration.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/6/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "TraktorConfiguration.h"
#include "TraktorModeInterface.h"
#include "TraktorEQMode.h"
#include "TraktorFXMode.h"
#include "TraktorLoopMode.h"
#include "TraktorMixMode.h"
#include "DM2USBMIDI.h"

/*
 4 Differnt 'Modes'
 
 
	 -- Global
		 -Center 'Shift' button down
		 -Buttons 1-4 select window page, or not, maybe this should be done when changing the dm2's mode
			 or maybe have an 'auto follow' option and this would be the way
			 to manually select the page you're seeing any how
		 - buttons 123 + joystick - control the browser? and load tracks?
		 - Transport buttons - i dunni, control radio and or other shit, maybe make this an option also
		 - A-B buttons - I dunno, they have a use in FX at least, not auto fade for christ sakes. Maybe the bpm clicker or something
 */


TraktorConfiguration::TraktorConfiguration() : DM2Configuration() , leftScratch(FALSE) , rightScratch(FALSE)
{	
	/*
	 DM2 calls TraktorConfiguration, which makes 4 'modes' which are of type TraktorModeInterface.
	 so, TraktorConfiguration owns the 4 banks of leds. TraktorModeInterface is of type DM2Config also though, so has it's own 4 banks.
 */
	traktorMixMode = new TraktorMixMode(bank1);
	traktorLoopMode = new TraktorLoopMode(bank2);
	traktorFXMode = new TraktorFXMode(bank3);
	traktorEQMode = new TraktorEQMode(bank4);
	currentMode = traktorMixMode;	
	currentBank = currentMode->myBank;
}

void TraktorConfiguration::readSettings()
{
}

void TraktorConfiguration::buttonRight1Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight1Clicked(dm2);
}
void TraktorConfiguration::buttonRight2Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight2Clicked(dm2);
}
void TraktorConfiguration::buttonRight3Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight3Clicked(dm2);
}
void TraktorConfiguration::buttonRight4Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight4Clicked(dm2);
}
void TraktorConfiguration::buttonRight5Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight5Clicked(dm2);
}
void TraktorConfiguration::buttonRight6Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight6Clicked(dm2);
}
void TraktorConfiguration::buttonRight7Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight7Clicked(dm2);
}
void TraktorConfiguration::buttonRight8Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonRight8Clicked(dm2);
}
void TraktorConfiguration::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft1Clicked(dm2);
}
void TraktorConfiguration::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft2Clicked(dm2);
}
void TraktorConfiguration::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft3Clicked(dm2);
}
void TraktorConfiguration::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft4Clicked(dm2);
}
void TraktorConfiguration::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft5Clicked(dm2);
}
void TraktorConfiguration::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft6Clicked(dm2);
}
void TraktorConfiguration::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft7Clicked(dm2);
}
void TraktorConfiguration::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){
	currentMode->buttonLeft8Clicked(dm2);
}


/*** Other Buttons ****/
void TraktorConfiguration::leftClicked(DM2USBMIDIDriver * dm2){
	currentMode->leftClicked(dm2);
}
void TraktorConfiguration::rightClicked(DM2USBMIDIDriver * dm2){
	currentMode->rightClicked(dm2);
}

void TraktorConfiguration::bottom1Clicked(DM2USBMIDIDriver * dm2){
	if( (currentMode == traktorLoopMode) && ( dm2->status.bottom_A || dm2->status.bottom_B ) ){
		currentMode->bottom1Clicked(dm2);
		return;}
	else if(dm2->status.bottom_1 == 0)
	{
		if(dm2->hasGrowl)
			dm2->MyGrowl_Notify(CFSTR("Traktor Mode Change"),CFSTR("Mixing Mode"),CFSTR("Traktor Mode Change"),NULL,0,FALSE,NULL);
		
		DM2Configuration::bottom1Clicked(dm2); // Changes currentBank
		currentMode = traktorMixMode;
	
	}
	makeBasicNote(dm2->status.bottom_1,kNOTE_TRAKTOR_GLOBAL_CHANGETO_MIX,dm2);
}

void TraktorConfiguration::bottom2Clicked(DM2USBMIDIDriver * dm2){
	if( (currentMode == traktorLoopMode) && ( dm2->status.bottom_A || dm2->status.bottom_B ) ){
		currentMode->bottom2Clicked(dm2);
		return;}
	else if(dm2->status.bottom_2 == 0)
	{
		if(dm2->hasGrowl)
			dm2->MyGrowl_Notify(CFSTR("Traktor Mode Change"),CFSTR("Loop Mode"),CFSTR("Traktor Mode Change"),NULL,0,FALSE,NULL);
		
		DM2Configuration::bottom2Clicked(dm2);
		currentMode = traktorLoopMode;
	}
	makeBasicNote(dm2->status.bottom_2,kNOTE_TRAKTOR_GLOBAL_CHANGETO_LOOP,dm2);
}
void TraktorConfiguration::bottom3Clicked(DM2USBMIDIDriver * dm2){
	if( (currentMode == traktorLoopMode) && ( dm2->status.bottom_A || dm2->status.bottom_B ) ){
		currentMode->bottom3Clicked(dm2);
		return;}
	else if(dm2->status.bottom_3 == 0)
	{
		if(dm2->hasGrowl)
			dm2->MyGrowl_Notify(CFSTR("Traktor Mode Change"),CFSTR("FX Mode"),CFSTR("Traktor Mode Change"),NULL,0,FALSE,NULL);

		DM2Configuration::bottom3Clicked(dm2);
		currentMode = traktorFXMode;
	}
	makeBasicNote(dm2->status.bottom_3,kNOTE_TRAKTOR_GLOBAL_CHANGETO_FX,dm2);	
}

void TraktorConfiguration::bottom4Clicked(DM2USBMIDIDriver * dm2){
	if( (currentMode == traktorLoopMode) && ( dm2->status.bottom_A || dm2->status.bottom_B ) ){
		currentMode->bottom4Clicked(dm2);
		return;}
	else if(dm2->status.bottom_4 == 0)
	{
		if(dm2->hasGrowl)
			dm2->MyGrowl_Notify(CFSTR("Traktor Mode Change"),CFSTR("EQ Mode"),CFSTR("Traktor Mode Change"),NULL,0,FALSE,NULL);

		DM2Configuration::bottom4Clicked(dm2);
		currentMode = traktorEQMode;
	}
	makeBasicNote(dm2->status.bottom_4,kNOTE_TRAKTOR_GLOBAL_CHANGETO_EQ,dm2);
}

void TraktorConfiguration::bottomAClicked(DM2USBMIDIDriver * dm2){
	currentMode->bottomAClicked(dm2);
}

void TraktorConfiguration::bottomBClicked(DM2USBMIDIDriver * dm2){
	currentMode->bottomBClicked(dm2);
}

/***** Analoug Inputs *****/
void TraktorConfiguration:: leftRingSpun(DM2USBMIDIDriver * dm2){
	currentMode->leftRingSpun(dm2);
}

void TraktorConfiguration::rightRingSpun(DM2USBMIDIDriver * dm2){
	currentMode->rightRingSpun(dm2);
}	
#define MIN(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })

void TraktorConfiguration::joystickYMoved(DM2USBMIDIDriver * dm2)
{
	dm2->noteBuf[0] = 0xB0;		
	dm2->noteBuf[1] = kNOTE_BASIC_CC_JOYSTICKY;													// Effect control 2
	
	float value = (float)dm2->calcJoystickYValue();				//should give us range of 0 to 127;	
	float range = 127.0;
	float middle = range/2.0;
	
	//a nice slowly growing expoential growth, should keep our range from 0 to 127 but slowly grow out of the middle position for finer tuning near the center.
	
	value -= middle;
	if(value>0.0)
	{
		value = powf(middle, (value/middle)) + .1*value;
	}
	else if(value<0.0)
	{//Why this no work?
		value = -1.0/powf(middle, (value/middle)) - .1*value ;
	}
	value += middle;

	//Get value back into range
	value = MIN(127.0,value);
	value = MAX(0.0,value);
	
	dm2->noteBuf[2] = (int) roundf(value);
}

/***** Input Handler ******/
void TraktorConfiguration::buttonReceived(int number, Bank * bank, int value, bool onMessage)
{
	/* Not using currentMode here bcs we can receive msg's for modes that aren't being displayed presently */
	switch(bank->bankNumber)
	{
		case 1:
			traktorMixMode->buttonReceived(number, value);
			break;
		case 2:
			traktorLoopMode->buttonReceived(number, value);
			break;
		case 3:
			traktorFXMode->buttonReceived(number, value);
			break;
		case 4:
			traktorEQMode->buttonReceived(number, value);
			break;
	}
}

void TraktorConfiguration::clearLEDAllBanks()
{
	traktorEQMode->setDefaults();
	traktorFXMode->setDefaults();
	traktorLoopMode->setDefaults();
	traktorMixMode->setDefaults();
}

