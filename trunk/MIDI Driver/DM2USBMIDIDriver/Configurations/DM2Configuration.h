/*
 *  DM2Configuration.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/4/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */
/******** MIDI NOTE BREAKDOWN *************
*
*  CC Values: 0xB0
*   Slider     : 8
*   Joystick X : 12 
*   Joystick Y : 13
*
*	Note: Rings mimic M-Audio Xponent by using same CC # but different Channels
*	Left Ring	: 0xB0 : 22
*	Right Ring	: 0xB1 : 22
*
*  MIDI NOTES : 0x90/0x80 On/Off
*
*  Led Rings : 
*   Bank1 : 0-15
*   Bank2 : 16-31
*   Bank3 : 32-47
*   Bank4 : 48-63
*
*   stop   : 64
*   play   : 65
*   rec    : 66
*   top_3  : 67
*   top_2  : 68
*   top_1  : 69
*   right  : 70
*   left   : 71
*   middle : 72
*   bottom_B 73
*   bottom_A 74
*
*
 
	Capabilities:
		
		Send Note On/Off for
								LED buttons	(4 Banks)
								Middle Button
								Ring center buttons
								Transport contol buttons
								A & B buttons
								1, 2, & 3 Buttons
		Send CC's for
								Scratch Rings (Banks)
								Joystick
								Xfade
 
************************************************/

#ifndef __DM2Configuration_h__
#define __DM2Configuration_h__

#include <Carbon/Carbon.h>


# define makeBasicNotePacket(a,b,c) dm2->noteBuf[0] = a;\
								dm2->noteBuf[1] = b;\
								dm2->noteBuf[2] = c;

class DM2USBMIDIDriver;

class DM2Configuration
{
public:
	
	DM2Configuration();
	virtual ~DM2Configuration();
	
	CFStringRef name;
	
	/** banks **/
	struct Bank * bank1;
	struct Bank * bank2;
	struct Bank * bank3;
	struct Bank * bank4;
	struct Bank * currentBank;
	
	/*** Standard Buttons ***/
	virtual void stopClicked(DM2USBMIDIDriver * dm2);
	virtual void playClicked(DM2USBMIDIDriver * dm2);
	virtual void recClicked(DM2USBMIDIDriver * dm2);
	virtual void top3Clicked(DM2USBMIDIDriver * dm2);
	virtual void top2Clicked(DM2USBMIDIDriver * dm2);
	virtual void top1Clicked(DM2USBMIDIDriver * dm2);
	virtual void bottom1Clicked(DM2USBMIDIDriver * dm2);
	virtual void bottom2Clicked(DM2USBMIDIDriver * dm2);
	virtual void bottom3Clicked(DM2USBMIDIDriver * dm2);
	virtual void bottom4Clicked(DM2USBMIDIDriver * dm2);
	virtual void middleClicked(DM2USBMIDIDriver * dm2);
	virtual void bottomAClicked(DM2USBMIDIDriver * dm2);
	virtual void bottomBClicked(DM2USBMIDIDriver * dm2);
	virtual void leftClicked(DM2USBMIDIDriver * dm2);
	virtual void rightClicked(DM2USBMIDIDriver * dm2);
	
	/*** LED Buttons ***/
	virtual void buttonRight1Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight2Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight3Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight4Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight5Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight6Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight7Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonRight8Clicked(DM2USBMIDIDriver * dm2);
	
	virtual void buttonLeft1Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft2Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft3Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft4Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft5Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft6Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft7Clicked(DM2USBMIDIDriver * dm2);
	virtual void buttonLeft8Clicked(DM2USBMIDIDriver * dm2);
	
	/*** Analoug Controllers ***/
	virtual void sliderMoved(DM2USBMIDIDriver * dm2);
	virtual void joystickXMoved(DM2USBMIDIDriver * dm2);
	virtual void joystickYMoved(DM2USBMIDIDriver * dm2);
	
	virtual void  leftRingSpun(DM2USBMIDIDriver * dm2);
	virtual void rightRingSpun(DM2USBMIDIDriver * dm2);

	/*** Incoming ***/
	virtual void buttonReceived(int number, Bank * bank, int value, bool onMessage);
	
	/*** Utility Functions ***/
	//Note: Maybe these should be static?, at least the ones with a myBank pointer
	void makeBasicNote(bool status,int noteNumber, DM2USBMIDIDriver * dm2);
	void makeCCNote(int channel, int controlNumber, int value, DM2USBMIDIDriver * dm2); 
	
	virtual void readSettings();

	virtual void clearLEDAllBanks();
	void clearLEDBank(struct Bank *);
	void clearLED();
	void toggleLED(int);
	void toggleLED(int,struct Bank *);
	void toggleButton(bool * button);
	void toggleButton(int button, struct Bank * theBank);
	bool ledStatus(int ledNum, struct Bank * theBank);
	void setLEDbuttonStatusByNumber(int buttonNumber, bool status, struct Bank * theBank);
	bool getLEDbuttonStatusByNumber(int buttonNumber, struct Bank * theBank);
	void setLED(bool *led, bool status);
	void setLED(bool *led, bool status, struct Bank * theBank);


private:
	//Degenerate copy and assignment 
	DM2Configuration(const DM2Configuration&); 
	DM2Configuration& operator=(const DM2Configuration&);

};

#endif