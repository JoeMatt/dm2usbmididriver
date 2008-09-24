/*
 *  TraktorEQConfiguration.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/14/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#ifndef __TraktorEQConfiguration_h__
#define __TraktorEQConfiguration_h__

#include <Carbon/Carbon.h>
#include "TraktorConfiguration.h"

class DM2USBMIDIDriver;
class TraktorConfiguration;

class TraktorEQMode : public TraktorModeInterface {
public:
	
	TraktorEQMode();

	/*** LED Buttons ***/
/*	void buttonRight1Clicked(DM2USBMIDIDriver * dm2);
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
*/	
	/**** Rings *****/
//	void leftRingSpun(DM2USBMIDIDriver * dm2);
//	void rightRingSpun(DM2USBMIDIDriver * dm2);
	
	/** Other Buttons ***/
//	void leftClicked(DM2USBMIDIDriver * dm2);
//	void rightClicked(DM2USBMIDIDriver * dm2);

};

#endif