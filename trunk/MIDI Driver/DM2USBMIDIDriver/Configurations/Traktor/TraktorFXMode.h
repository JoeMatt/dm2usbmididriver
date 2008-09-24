/*
 *  TraktorFXMode.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/14/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#ifndef __TraktorFXMode_h__
#define __TraktorFXMode_h__

#include <Carbon/Carbon.h>
#include "TraktorModeInterface.h"

class DM2USBMIDIDriver;

class TraktorFXMode : public TraktorModeInterface {
public:
	
	TraktorFXMode(Bank * dm2bank);
	
	void setDefaults();
	/*** LED Buttons ***/
	void buttonRight1Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight2Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight3Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight4Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight5Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight6Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight7Clicked(DM2USBMIDIDriver * dm2);
	void buttonRight8Clicked(DM2USBMIDIDriver * dm2);
	
	void buttonLeft1Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft2Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft3Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft4Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft5Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft6Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft7Clicked(DM2USBMIDIDriver * dm2);
	void buttonLeft8Clicked(DM2USBMIDIDriver * dm2);
	
	/*** Input ***/
	void buttonReceived(int number, int value);
	
	/**** Rings *****/
	void leftRingSpun(DM2USBMIDIDriver * dm2);
	void rightRingSpun(DM2USBMIDIDriver * dm2);
	
	/** Other Buttons ***/
	void leftClicked(DM2USBMIDIDriver * dm2);
	void rightClicked(DM2USBMIDIDriver * dm2);
	
	/** FX specific **/
	void bottomAClicked(DM2USBMIDIDriver * dm2);
	void bottomBClicked(DM2USBMIDIDriver * dm2);

};

#endif