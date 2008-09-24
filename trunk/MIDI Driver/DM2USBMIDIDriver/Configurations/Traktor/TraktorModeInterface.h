/*
 *  TraktorModeInterface.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/14/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */
#ifndef __TraktorModeInterface_h__
#define __TraktorModeInterface_h__

#include "DM2Configuration.h"

class DM2USBMIDIDriver;

class TraktorModeInterface : public DM2Configuration{
public:
	TraktorModeInterface(Bank * dm2bank);
	
	Bank * myBank;
	/*** Initialiezer **/
	virtual void setDefaults()=0;
	/*** LED Buttons ***/
	virtual void buttonRight1Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight2Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight3Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight4Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight5Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight6Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight7Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonRight8Clicked(DM2USBMIDIDriver * dm2)=0;

	virtual void buttonLeft1Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft2Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft3Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft4Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft5Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft6Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft7Clicked(DM2USBMIDIDriver * dm2)=0;
	virtual void buttonLeft8Clicked(DM2USBMIDIDriver * dm2)=0;
	
	virtual void  leftClicked(DM2USBMIDIDriver * dm2)=0;
	virtual void rightClicked(DM2USBMIDIDriver * dm2)=0;
	
	//virtual void bottomAClicked(DM2USBMIDIDriver * dm2)=0;
	//virtual void bottomBClicked(DM2USBMIDIDriver * dm2)=0;
	
	virtual void  leftRingSpun(DM2USBMIDIDriver * dm2)=0;
	virtual void rightRingSpun(DM2USBMIDIDriver * dm2)=0;
	
	/*** Input ***/
	virtual void buttonReceived(int number, int value)=0;
	

};

#endif