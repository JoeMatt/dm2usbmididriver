/*
 *  TraktorConfiguration.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/6/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#ifndef __TraktorConfiguration_h__
#define __TraktorConfiguration_h__

#include <Carbon/Carbon.h>
#include "DM2Configuration.h"

class DM2USBMIDIDriver;
class DM2Configuration;
class TraktorEQMode;
class TraktorFXMode;
class TraktorMixMode;
class TraktorLoopMode;
class TraktorModeInterface;

class TraktorConfiguration : public DM2Configuration {
public:
	TraktorConfiguration();
	
	/** Mode Changers **/
	TraktorModeInterface * currentMode;
	TraktorEQMode * traktorEQMode;
	TraktorFXMode * traktorFXMode;
	TraktorMixMode * traktorMixMode;
	TraktorLoopMode * traktorLoopMode;

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
	/*** Other Buttons ****/
	void leftClicked(DM2USBMIDIDriver * dm2);
	void rightClicked(DM2USBMIDIDriver * dm2);
	
	void bottom1Clicked(DM2USBMIDIDriver * dm2);
	void bottom2Clicked(DM2USBMIDIDriver * dm2);
	void bottom3Clicked(DM2USBMIDIDriver * dm2);
	void bottom4Clicked(DM2USBMIDIDriver * dm2);
	
	void bottomAClicked(DM2USBMIDIDriver * dm2);
	void bottomBClicked(DM2USBMIDIDriver * dm2);

	/***** Analoug Inputs *****/
	void  leftRingSpun(DM2USBMIDIDriver * dm2);
	void rightRingSpun(DM2USBMIDIDriver * dm2);	
	void joystickYMoved(DM2USBMIDIDriver * dm2);
	/***** Input ****/
	void buttonReceived(int number, Bank * bank, int value, bool onMessage);
	
	/***** Utility Functions ******/
	 void readSettings();
	 void clearLEDAllBanks();

	 bool leftScratch;
	 bool rightScratch;
};

#endif