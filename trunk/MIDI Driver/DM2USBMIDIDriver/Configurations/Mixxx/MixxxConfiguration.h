/*
 *  MixxxConfiguration.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/5/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

/*
 * Capabilities : Everything from DM2Configuration
 *	Plus:
 *
 *	Changed:
 *		Only 1 bank
 */

#ifndef __MixxxConfiguration_h__
#define __MixxxConfiguration_h__

#include <Carbon/Carbon.h>
#include "DM2BasicBanks.h"

class DM2USBMIDIDriver;
class DM2BasicNoBanks;

class MixxxConfiguration : public DM2BasicNoBanks {
public:
	MixxxConfiguration();
	
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
	
	/*** Top Buttons ***/
	void stopClicked(DM2USBMIDIDriver * dm2);
	void playClicked(DM2USBMIDIDriver * dm2);
	void recClicked(DM2USBMIDIDriver * dm2);
	void top3Clicked(DM2USBMIDIDriver * dm2);
	void top2Clicked(DM2USBMIDIDriver * dm2);
	void top1Clicked(DM2USBMIDIDriver * dm2);
	
	/*** Bottom Buttons ****/
	void leftClicked(DM2USBMIDIDriver * dm2);
	void rightClicked(DM2USBMIDIDriver * dm2);
	
	void middleClicked(DM2USBMIDIDriver * dm2);
	
	void bottom1Clicked(DM2USBMIDIDriver * dm2);
	void bottom2Clicked(DM2USBMIDIDriver * dm2);
	void bottom3Clicked(DM2USBMIDIDriver * dm2);
	void bottom4Clicked(DM2USBMIDIDriver * dm2);
	
	void bottomAClicked(DM2USBMIDIDriver * dm2);
	void bottomBClicked(DM2USBMIDIDriver * dm2);
	
	/***** Analoug Inputs *****/
	void  leftRingSpun(DM2USBMIDIDriver * dm2);
	void rightRingSpun(DM2USBMIDIDriver * dm2);	
	
	void sliderMoved(DM2USBMIDIDriver * dm2);
	void joystickXMoved(DM2USBMIDIDriver * dm2);
	void joystickYMoved(DM2USBMIDIDriver * dm2);
	
	/***** Input ****/
	void buttonReceived(int number, Bank * bank, int value, bool onMessage);
	
	int leftRingCCValue,
	rightRingCCValue;
	
	/* I know this is dirty but wtf, the linux code is retarded any way */
	bool	middleLeftRingMoved,
			middleRightRingMoved,
			led8LeftRingMoved,
			led8RightRingMoved,
			led7LeftRingMoved,
			led7RightRingMoved,
			led6LeftRingMoved,
			led6RightRingMoved,
			led3LeftRingMoved,
			led3RightRingMoved,
			led2LeftRingMoved,
			led2RightRingMoved;
	
	/* Linux jog compaitablity */
	int jogmidival;

};

#endif