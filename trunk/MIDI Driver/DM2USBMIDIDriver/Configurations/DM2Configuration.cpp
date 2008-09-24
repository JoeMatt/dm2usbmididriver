/*
 *  DM2Configuration.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/4/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "DM2Configuration.h"
#include "DM2USBMIDI.h"

DM2Configuration::DM2Configuration()
{
	bank1 = new struct Bank;
	bank2 = new struct Bank;
	bank3 = new struct Bank;
	bank4 = new struct Bank;
	
	bank1->bankNumber = 1;
	bank2->bankNumber = 2;
	bank3->bankNumber = 3;
	bank4->bankNumber = 4;			
	
	clearLEDAllBanks();
	currentBank = bank1;
		
}

DM2Configuration::~DM2Configuration()
{
	delete bank1;
	delete bank2;
	delete bank3;
	delete bank4;
}

/***************** Scratch Ring Buttons *********************
Check the ring button status.

If it's different
then check if we're using sticky buttons

if sticky buttons
if status == 1
toggle the led
if current_bank->button_x == ~current_bank->button_x
send note, off if 0, on if 1 now
else not sticky buttons
toggle led
send note, off if status = 0, on if status = 1
***********************************************************/
#pragma mark LED Buttons
void DM2Configuration::buttonRight1Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_1)
		return;

	currentBank->buttons.right_1 = !currentBank->buttons.right_1;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_1 = dm2->status.right_1;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_1 = !currentBank->leds.right_1;
	makeBasicNote(currentBank->buttons.right_1,(currentBank->bankNumber-1) * 16 + 7,dm2);
}

void DM2Configuration::buttonRight2Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_2)
		return;
	
	currentBank->buttons.right_2 = !currentBank->buttons.right_2;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_2 = dm2->status.right_2;

	if(currentBank->iControlLeds)
		currentBank->leds.right_2 = !currentBank->leds.right_2;
	makeBasicNote(currentBank->buttons.right_2,(currentBank->bankNumber-1) * 16 + 6,dm2);
}
void DM2Configuration::buttonRight3Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_3)
		return;
	
	currentBank->buttons.right_3 = !currentBank->buttons.right_3;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_3 = dm2->status.right_3;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_3 = !currentBank->leds.right_3;
	makeBasicNote(currentBank->buttons.right_3,(currentBank->bankNumber-1) * 16 + 5,dm2);
}
void DM2Configuration::buttonRight4Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_4)
		return;
	
	currentBank->buttons.right_4 = !currentBank->buttons.right_4;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_4 = dm2->status.right_4;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_4 = !currentBank->leds.right_4;
	makeBasicNote(currentBank->buttons.right_4,(currentBank->bankNumber-1) * 16 + 4,dm2);
}
void DM2Configuration::buttonRight5Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_5)
		return;
	
	currentBank->buttons.right_5 = !currentBank->buttons.right_5;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_5 = dm2->status.right_5;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_5 = !currentBank->leds.right_5;
	makeBasicNote(currentBank->buttons.right_5,(currentBank->bankNumber-1) * 16 + 3,dm2);
}
void DM2Configuration::buttonRight6Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_6)
		return;
	
	currentBank->buttons.right_6 = !currentBank->buttons.right_6;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_6 = dm2->status.right_6;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_6 = !currentBank->leds.right_6;
	makeBasicNote(currentBank->buttons.right_6,(currentBank->bankNumber-1) * 16 + 2,dm2);
}
void DM2Configuration::buttonRight7Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_7)
		return;
	
	currentBank->buttons.right_7 = !currentBank->buttons.right_7;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_7 = dm2->status.right_7;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_7 = !currentBank->leds.right_7;
	makeBasicNote(currentBank->buttons.right_7,(currentBank->bankNumber-1) * 16 + 1,dm2);
}
void DM2Configuration::buttonRight8Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.right_8)
		return;
	
	currentBank->buttons.right_8 = !currentBank->buttons.right_8;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.right_8 = dm2->status.right_8;
	
	if(currentBank->iControlLeds)
		currentBank->leds.right_8 = !currentBank->leds.right_8;
	makeBasicNote(currentBank->buttons.right_8,(currentBank->bankNumber-1) * 16,dm2);
}

void DM2Configuration::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_1)
		return;
	
	currentBank->buttons.left_1 = !currentBank->buttons.left_1;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_1 = dm2->status.left_1;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_1 = !currentBank->leds.left_1;
	makeBasicNote(currentBank->buttons.left_1,(currentBank->bankNumber-1) * 16 + 15,dm2);
}

void DM2Configuration::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_2)
		return;
	
	currentBank->buttons.left_2 = !currentBank->buttons.left_2;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_2 = dm2->status.left_2;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_2 = !currentBank->leds.left_2;
	makeBasicNote(currentBank->buttons.left_2,(currentBank->bankNumber-1) * 16 + 14,dm2);
}
void DM2Configuration::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_3)
		return;
	
	currentBank->buttons.left_3 = !currentBank->buttons.left_3;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_3 = dm2->status.left_3;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_3 = !currentBank->leds.left_3;
	makeBasicNote(currentBank->buttons.left_3,(currentBank->bankNumber-1) * 16 + 13,dm2);
}
void DM2Configuration::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_4)
		return;
	
	currentBank->buttons.left_4 = !currentBank->buttons.left_4;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_4 = dm2->status.left_4;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_4 = !currentBank->leds.left_4;
	makeBasicNote(currentBank->buttons.left_4,(currentBank->bankNumber-1) * 16 + 12,dm2);
}
void DM2Configuration::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_5)
		return;
	
	currentBank->buttons.left_5 = !currentBank->buttons.left_5;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_5 = dm2->status.left_5;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_5 = !currentBank->leds.left_5;
	makeBasicNote(currentBank->buttons.left_5,(currentBank->bankNumber-1) * 16 + 11,dm2);
}
void DM2Configuration::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_6)
		return;
	
	currentBank->buttons.left_6 = !currentBank->buttons.left_6;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_6 = dm2->status.left_6;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_6 = !currentBank->leds.left_6;
	makeBasicNote(currentBank->buttons.left_6,(currentBank->bankNumber-1) * 16 + 10,dm2);
}
void DM2Configuration::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_7)
		return;
	
	currentBank->buttons.left_7 = !currentBank->buttons.left_7;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_7 = dm2->status.left_7;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_7 = !currentBank->leds.left_7;
	makeBasicNote(currentBank->buttons.left_7,(currentBank->bankNumber-1) * 16 + 9,dm2);
}
void DM2Configuration::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){
	if(currentBank->sticky_buttons && !dm2->status.left_8)
		return;
	
	currentBank->buttons.left_8 = !currentBank->buttons.left_8;
	
	if(!currentBank->sticky_buttons)
		currentBank->buttons.left_8 = dm2->status.left_8;
	
	if(currentBank->iControlLeds)
		currentBank->leds.left_8 = !currentBank->leds.left_8;
	makeBasicNote(currentBank->buttons.left_8,(currentBank->bankNumber-1) * 16 + 8,dm2);
}
#pragma mark Top Buttons
void DM2Configuration::stopClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.stop,kNOTE_BASIC_STOPBUTTON,dm2);}

void DM2Configuration::playClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.play,kNOTE_BASIC_PLAYBUTTON,dm2);}

void DM2Configuration::recClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.rec,kNOTE_BASIC_RECBUTTON,dm2);}

void DM2Configuration::top3Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_3,kNOTE_BASIC_TOP3BUTTON,dm2);}

void DM2Configuration::top2Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_2,kNOTE_BASIC_TOP2BUTTON,dm2);}
	
void DM2Configuration::top1Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_1,kNOTE_BASIC_TOP1BUTTON,dm2);}

/************* Bank 1 to 4 buttons ************
* Change the current Bank
* Send MIDI notes
*********************************************/

#pragma mark Bottom buttons
void DM2Configuration::bottom1Clicked(DM2USBMIDIDriver * dm2)
{			currentBank = bank1;
	makeBasicNote(dm2->status.bottom_1, kNOTE_BASIC_BOTTOM1BUTTON, dm2);
}

void DM2Configuration::bottom2Clicked(DM2USBMIDIDriver * dm2)
{			currentBank = bank2;
	makeBasicNote(dm2->status.bottom_2, kNOTE_BASIC_BOTTOM2BUTTON, dm2);
}

void DM2Configuration::bottom3Clicked(DM2USBMIDIDriver * dm2)
{			currentBank = bank3;
	makeBasicNote(dm2->status.bottom_3, kNOTE_BASIC_BOTTOM3BUTTON, dm2);
}
void DM2Configuration::bottom4Clicked(DM2USBMIDIDriver * dm2)
{			currentBank = bank4;
	makeBasicNote(dm2->status.bottom_4, kNOTE_BASIC_BOTTOM4BUTTON, dm2);
}

void DM2Configuration::middleClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.middle,kNOTE_BASIC_MIDDLEBUTTON,dm2);}

void DM2Configuration::bottomAClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_A,kNOTE_BASIC_BOTTOMABUTTON,dm2);	}

void DM2Configuration::bottomBClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_B,kNOTE_BASIC_BOTTOMBBUTTON,dm2);}

void DM2Configuration::leftClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.left,kNOTE_BASIC_LEFTCENTERBUTTON,dm2);}

void DM2Configuration::rightClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.right,kNOTE_BASIC_RIGHTCENTERBUTTON,dm2);}

#pragma mark Slider & Joystick
void DM2Configuration::sliderMoved(DM2USBMIDIDriver * dm2)
{	
	dm2->noteBuf[0] = 0xB0;
	dm2->noteBuf[1] = kNOTE_BASIC_CC_SLIDER;														//General Purpose Slider 1 = 16 , 10 = pan, 8 = balance
	dm2->noteBuf[2] =  dm2->calcSliderValue();  
}
void DM2Configuration::joystickXMoved(DM2USBMIDIDriver * dm2)
{
	dm2->noteBuf[0] = 0xB0;
	dm2->noteBuf[1] = kNOTE_BASIC_CC_JOYSTICKX;													// Effect control 1
	dm2->noteBuf[2] = 127 - dm2->calcJoystickXValue();										// Because the X axis is reversed to what you'd expect 		
}
void DM2Configuration::joystickYMoved(DM2USBMIDIDriver * dm2)
{
	dm2->noteBuf[0] = 0xB0;		
	dm2->noteBuf[1] = kNOTE_BASIC_CC_JOYSTICKY;													// Effect control 2
	dm2->noteBuf[2] = dm2->calcJoystickYValue();				//should give us range of 0 to 127;	
}

/******* Scratch Rings **************/
#pragma mark Scratch Rings
void DM2Configuration::leftRingSpun(DM2USBMIDIDriver * dm2)
{
/* THE OLD STUPID WAY, 2 DIFFERENT NOTES 
	int accel;	
	Byte * noteBuf = dm2->noteBuf;
	if (dm2->status.accel_left < 0) {
		accel = dm2->status.accel_left *  -1;
	}
	else {
		accel = dm2->status.accel_left;
	}

	if(accel)
	{
		if( (accel - currentBank->bumpIgnore) <= 0)// && dm2->oldstatus.accel_left < accel) //So we don't ignore on decel,nvm, it would still trigger if we bumped and then it came down a hair
			return;
		if(accel == 128)
			accel = 127;
		noteBuf[0] = 0x90;					
		noteBuf[1] = dm2->status.accel_left < 0 ? kNOTE_BASIC_LEFTRINGBACKWARD : kNOTE_BASIC_LEFTRINGFORWARD;
		noteBuf[2] = accel;
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
		#if DEBUG
		printf("Sending left ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
		#endif
	}
	else  //We need to turn off BOTH notes in this case.
	{
		noteBuf[0] = 0x80;					
		noteBuf[1] = kNOTE_BASIC_LEFTRINGBACKWARD;
		noteBuf[2] = 0;								
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
		#if DEBUG
		printf("Sending left ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
		#endif
		noteBuf[1] = kNOTE_BASIC_LEFTRINGFORWARD;
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
		#if DEBUG
		printf("Sending left ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
		#endif
	}
 */
	//range of 62 instead of 127, about half
	int accel;
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	
	if( (accel - currentBank->bumpIgnore) <= 0 && accel != 64)
		return;
	//Note CC 22, channel 1
	dm2->noteBuf[0] = 0xB0;
	dm2->noteBuf[1] = 22;//kNOTE_BASIC_LEFTRINGFORWARD;
	dm2->noteBuf[2] = accel;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	printf("Sending left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}

void DM2Configuration::rightRingSpun(DM2USBMIDIDriver * dm2)
{
/* OLD WAY 	
	int accel;	
	Byte * noteBuf = dm2->noteBuf;
	if (dm2->status.accel_right < 0) {
		accel = dm2->status.accel_right *  -1;
	}
	else {
		accel = dm2->status.accel_right;
	}
	
	if(accel)
	{
		if( (accel - currentBank->bumpIgnore) <= 0)
			return;
		if(accel == 128)
			accel = 127;
		noteBuf[0] = 0x90;					
		noteBuf[1] = dm2->status.accel_right < 0 ? kNOTE_BASIC_RIGHTRINGBACKWARD : kNOTE_BASIC_RIGHTRINGFORWARD;
		noteBuf[2] = accel;
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
	#if DEBUG
		printf("Sending right ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
	#endif
	}
	else  //We need to turn off BOTH notes in this case.
	{
		noteBuf[0] = 0x80;					
		noteBuf[1] = kNOTE_BASIC_RIGHTRINGBACKWARD;
		noteBuf[2] = 0;								
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
	#if DEBUG
		printf("Sending right ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
	#endif
		noteBuf[1] = kNOTE_BASIC_RIGHTRINGFORWARD;
		dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, noteBuf );
	#if DEBUG
		printf("Sending right ring: %x %i %i\n",noteBuf[0],noteBuf[1],noteBuf[2]);
	#endif
	}
 */
	//range of 62 instead of 127, about half
	int accel;
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	
	if( (accel - currentBank->bumpIgnore) <= 0 && accel != 64)
		return;
	//Note CC 22, channel 1
	dm2->noteBuf[0] = 0xB1;
	dm2->noteBuf[1] = 22;//kNOTE_BASIC_RIGHTRINGFORWARD;
	dm2->noteBuf[2] = accel;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	printf("Sending right ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
	
}
/****** Incoming *******/
void DM2Configuration::buttonReceived(int number, Bank * bank, int value, bool onMessage)
{
	if(bank->isMidiClock)
		return;
	
	if(bank->midiInControlsLeds)
	{	
		/* An 'On' with 0 velocity is reall an 'Off' */
		if(onMessage & value == 0)
			onMessage = false;
		
		/* Toggle the led only if the received msg is opposite of current status */
		if( onMessage != ledStatus(number, bank) )
		{
		   toggleLED(number,bank);
			/* If the button status matters, ie; using sticky/toggle buttons we should set this to match */
			// TODO: Maybe make this an option
			if(currentBank->sticky_buttons)
			{
				if(currentBank->invertLeds)
					onMessage = !onMessage;
				setLEDbuttonStatusByNumber( number, onMessage, bank);
			}	
		}
	}
}

/******* Utility Functions *********/
#pragma mark Utility Functions
void DM2Configuration::makeBasicNote(bool status,int noteNumber, DM2USBMIDIDriver * dm2)
{
	dm2->noteBuf[0] = status ? 0x90 : 0x80;
	dm2->noteBuf[1] = noteNumber;
	dm2->noteBuf[2] = 127;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
	#if DEBUG
	printf("Sending basic note, status: %x, note#: %i\n",dm2->noteBuf[0],dm2->noteBuf[1]);
	#endif
}

void DM2Configuration::makeCCNote(int channel, int controlNumber, int value, DM2USBMIDIDriver * dm2)
{
	dm2->noteBuf[0] = 0xB0 + channel;
	dm2->noteBuf[1] = controlNumber;
	dm2->noteBuf[2] = value;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
}

void  DM2Configuration::clearLED()
{
	clearLEDBank(currentBank);
}

void DM2Configuration::clearLEDBank(struct Bank * bank)
{
	bool clear = bank->invertLeds ? ON : OFF;
	bank->leds.right_1 = clear;
	bank->leds.right_2 = clear;
	bank->leds.right_3 = clear;
	bank->leds.right_4 = clear;
	bank->leds.right_5 = clear;
	bank->leds.right_6 = clear;
	bank->leds.right_7 = clear;
	bank->leds.right_8 = clear;

	bank->leds.left_1 = clear;
	bank->leds.left_2 = clear;
	bank->leds.left_3 = clear;
	bank->leds.left_4 = clear;
	bank->leds.left_5 = clear;
	bank->leds.left_6 = clear;
	bank->leds.left_7 = clear;
	bank->leds.left_8 = clear;
	
	bank->buttons.right_1 = FALSE;
	bank->buttons.right_2 = FALSE;
	bank->buttons.right_3 = FALSE;
	bank->buttons.right_4 = FALSE;
	bank->buttons.right_5 = FALSE;
	bank->buttons.right_6 = FALSE;
	bank->buttons.right_7 = FALSE;
	bank->buttons.right_8 = FALSE;
	
	bank->buttons.left_1 = FALSE;
	bank->buttons.left_2 = FALSE;
	bank->buttons.left_3 = FALSE;
	bank->buttons.left_4 = FALSE;
	bank->buttons.left_5 = FALSE;
	bank->buttons.left_6 = FALSE;
	bank->buttons.left_7 = FALSE;
	bank->buttons.left_8 = FALSE;
}

void DM2Configuration::clearLEDAllBanks()
{
	clearLEDBank(bank1);
	clearLEDBank(bank2);
	clearLEDBank(bank3);
	clearLEDBank(bank4);
}

void DM2Configuration::toggleButton(bool * button)
{ 	*button = !(*button); }

void DM2Configuration::toggleButton(int button, struct Bank * theBank)
{
	bool * theButton;
	
	/* Maybe can change to something like
	 theButton = *theBank->buttons.right_8 + sizeof(bool)*button;
	*/
	switch(button)
	{
		case 0:
			theButton = &theBank->buttons.right_8;
			break;
		case 1:
			theButton = &theBank->buttons.right_7;
			break;
		case 2:
			theButton = &theBank->buttons.right_6;
			break;
		case 3:
			theButton = &theBank->buttons.right_5;
			break;
		case 4:
			theButton = &theBank->buttons.right_4;
			break;
		case 5:
			theButton = &theBank->buttons.right_3;
			break;
		case 6:
			theButton = &theBank->buttons.right_2;
			break;
		case 7:
			theButton = &theBank->buttons.right_1;
			break;
		case 8:
			theButton = &theBank->buttons.left_8;
			break;
		case 9:
			theButton = &theBank->buttons.left_7;
			break;
		case 10:
			theButton = &theBank->buttons.left_6;
			break;
		case 11:
			theButton = &theBank->buttons.left_5;
			break;
		case 12:
			theButton = &theBank->buttons.left_4;
			break;
		case 13:
			theButton = &theBank->buttons.left_3;
			break;
		case 14:
			theButton = &theBank->buttons.left_2;
			break;
		case 15:
			theButton = &theBank->buttons.left_1;
			break;
		default:
			theButton = new bool;
			break;
	}
	*theButton = !(*theButton);	
}



void DM2Configuration::toggleLED(int ledNum, struct Bank * theBank)
{
	ledNum = ledNum % 16; //insted of dying, we're mod'ing if the number is too big
	
	//*((uint16_t *) &theBank->leds) ^= (1 << ledNum);

	/* That code is brilliant, I'm not even sure what it does but I kept
		typing stuff til it worked. No actually, what it does is
		it type casts the struct led_status into a 16bit long int so the 
		OS knows how to operate with it. Then we bitshift a sinde bit
		the number of slots we want. Then we XOR that bit with the original value
		and set it to itself. got it?
		*/
	bool * theLED;
	switch(ledNum)
	{
		case 0:
			theLED = &theBank->leds.right_8;
			break;
		case 1:
			theLED = &theBank->leds.right_7;
			break;
		case 2:
			theLED = &theBank->leds.right_6;
			break;
		case 3:
			theLED = &theBank->leds.right_5;
			break;
		case 4:
			theLED = &theBank->leds.right_4;
			break;
		case 5:
			theLED = &theBank->leds.right_3;
			break;
		case 6:
			theLED = &theBank->leds.right_2;
			break;
		case 7:
			theLED = &theBank->leds.right_1;
			break;
		case 8:
			theLED = &theBank->leds.left_8;
			break;
		case 9:
			theLED = &theBank->leds.left_7;
			break;
		case 10:
			theLED = &theBank->leds.left_6;
			break;
		case 11:
			theLED = &theBank->leds.left_5;
			break;
		case 12:
			theLED = &theBank->leds.left_4;
			break;
		case 13:
			theLED = &theBank->leds.left_3;
			break;
		case 14:
			theLED = &theBank->leds.left_2;
			break;
		case 15:
			theLED = &theBank->leds.left_1;
			break;
		default:
			theLED = new bool;
			break;
	}
	*theLED = !(*theLED);
}
void DM2Configuration::toggleLED(int ledNum)
{
	toggleLED(ledNum, currentBank);
}

void  DM2Configuration::setLED(bool *led, bool status)
{
	setLED(led,status,currentBank);
}

void  DM2Configuration::setLED(bool *led, bool status, struct Bank * theBank)
{
	// ON is actually FALSE remember, so flip on !invertLEDs
	if( !theBank->invertLeds)
		status = !status; 
	
	*led = status;
}


void DM2Configuration::setLEDbuttonStatusByNumber(int buttonNumber,bool status, struct Bank * theBank)
{
	buttonNumber = buttonNumber % 16; //insted of dying, we're mod'ing if the number is too big
	
	bool * theButton;
	switch(buttonNumber)
	{
		case 0:
			theButton = &theBank->buttons.right_8;
			break;
		case 1:
			theButton = &theBank->buttons.right_7;
			break;
		case 2:
			theButton = &theBank->buttons.right_6;
			break;
		case 3:
			theButton = &theBank->buttons.right_5;
			break;
		case 4:
			theButton = &theBank->buttons.right_4;
			break;
		case 5:
			theButton = &theBank->buttons.right_3;
			break;
		case 6:
			theButton = &theBank->buttons.right_2;
			break;
		case 7:
			theButton = &theBank->buttons.right_1;
			break;
		case 8:
			theButton = &theBank->buttons.left_8;
			break;
		case 9:
			theButton = &theBank->buttons.left_7;
			break;
		case 10:
			theButton = &theBank->buttons.left_6;
			break;
		case 11:
			theButton = &theBank->buttons.left_5;
			break;
		case 12:
			theButton = &theBank->buttons.left_4;
			break;
		case 13:
			theButton = &theBank->buttons.left_3;
			break;
		case 14:
			theButton = &theBank->buttons.left_2;
			break;
		case 15:
			theButton = &theBank->buttons.left_1;
			break;
		default:
			theButton = new bool;
			break;
	}
	*theButton = status;
}

bool DM2Configuration::getLEDbuttonStatusByNumber(int buttonNumber, struct Bank * theBank)
{
	buttonNumber = buttonNumber % 16; //insted of dying, we're mod'ing if the number is too big
	
	bool * theButton;
	switch(buttonNumber)
	{
		case 0:
			theButton = &theBank->buttons.right_8;
			break;
		case 1:
			theButton = &theBank->buttons.right_7;
			break;
		case 2:
			theButton = &theBank->buttons.right_6;
			break;
		case 3:
			theButton = &theBank->buttons.right_5;
			break;
		case 4:
			theButton = &theBank->buttons.right_4;
			break;
		case 5:
			theButton = &theBank->buttons.right_3;
			break;
		case 6:
			theButton = &theBank->buttons.right_2;
			break;
		case 7:
			theButton = &theBank->buttons.right_1;
			break;
		case 8:
			theButton = &theBank->buttons.left_8;
			break;
		case 9:
			theButton = &theBank->buttons.left_7;
			break;
		case 10:
			theButton = &theBank->buttons.left_6;
			break;
		case 11:
			theButton = &theBank->buttons.left_5;
			break;
		case 12:
			theButton = &theBank->buttons.left_4;
			break;
		case 13:
			theButton = &theBank->buttons.left_3;
			break;
		case 14:
			theButton = &theBank->buttons.left_2;
			break;
		case 15:
			theButton = &theBank->buttons.left_1;
			break;
		default:
			theButton = new bool;
			break;
	}
	return *theButton;
}



void DM2Configuration::readSettings()
{	
	CFPropertyListRef rtn;
	
	// Read the preference, default for CFPreferencesGetAppBooleanValue is false if not found
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1StickyButtons"), appID );
	if(rtn != NULL)
		bank1->sticky_buttons = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank1->sticky_buttons = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank2StickyButtons"), appID );
	if(rtn != NULL)
		bank2->sticky_buttons = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank2->sticky_buttons = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank3StickyButtons"), appID );
	if(rtn != NULL)
		bank3->sticky_buttons = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank3->sticky_buttons = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank4StickyButtons"), appID );
	if(rtn != NULL)
		bank4->sticky_buttons = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank4->sticky_buttons = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1InvertLeds"), appID );
	if(rtn != NULL)
		bank1->invertLeds = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank1->invertLeds = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank2InvertLeds"), appID );
	if(rtn != NULL)
		bank2->invertLeds = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank2->invertLeds = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank3InvertLeds"), appID );
	if(rtn != NULL)
		bank3->invertLeds = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank3->invertLeds = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank4InvertLeds"), appID );
	if(rtn != NULL)
		bank4->invertLeds = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank4->invertLeds = false;
	}
	/** MIDI Display **/
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1DisplaysMIDIClock"), appID );
	if(rtn != NULL)
		bank1->isMidiClock = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank1->isMidiClock = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank2DisplaysMIDIClock"), appID );
	if(rtn != NULL)
		bank2->isMidiClock = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank2->isMidiClock = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank3DisplaysMIDIClock"), appID );
	if(rtn != NULL)
		bank3->isMidiClock = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank3->isMidiClock = false;
	}
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank4DisplaysMIDIClock"), appID );
	if(rtn != NULL)
		bank4->isMidiClock = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank4->isMidiClock = false;
	}
	/* Bump Ignore */
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1ScratchRingBumpIgnore"), appID );
	if(rtn != NULL)
		CFNumberGetValue( (CFNumberRef) rtn, kCFNumberIntType, &(bank1->bumpIgnore));
	else
		bank1->bumpIgnore = 0;
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank2ScratchRingBumpIgnore"), appID );
	if(rtn != NULL)
		CFNumberGetValue( (CFNumberRef) rtn, kCFNumberIntType, &(bank1->bumpIgnore));
	else
		bank2->bumpIgnore = 0;
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank3ScratchRingBumpIgnore"), appID );
	if(rtn != NULL)
		CFNumberGetValue( (CFNumberRef) rtn, kCFNumberIntType, &(bank1->bumpIgnore));
	else
		bank3->bumpIgnore = 0;
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank4ScratchRingBumpIgnore"), appID );
	if(rtn != NULL)
		CFNumberGetValue( (CFNumberRef) rtn, kCFNumberIntType, &(bank1->bumpIgnore));
	else
		bank4->bumpIgnore = 0;
	/* Who Controls LEDs */
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1WhoControlsLEDs"), appID );
	if(rtn != NULL)
	{
	
		if		( CFStringCompare((CFStringRef) rtn, CFSTR("MIDI Messages Only"), kCFCompareCaseInsensitive) == kCFCompareEqualTo )
		{
			bank1->midiInControlsLeds = TRUE;
			bank1->iControlLeds = FALSE;
		}
		else if ( CFStringCompare((CFStringRef) rtn, CFSTR("Driver & MIDI Messages"), kCFCompareCaseInsensitive) == kCFCompareEqualTo )
		{
			bank1->midiInControlsLeds = TRUE;
			bank1->iControlLeds = TRUE;
		}
		else /* "Driver Only" or default for unknown values */
		{
			bank1->midiInControlsLeds = FALSE;
			bank1->iControlLeds = TRUE;
		}
	}
	else
	{
		bank1->midiInControlsLeds = FALSE;
		bank1->iControlLeds = TRUE;
	}
	
	if(rtn)
		CFRelease(rtn);
}

bool DM2Configuration::ledStatus(int ledNum, struct Bank * theBank)
{
	ledNum = ledNum % 16; //insted of dying, we're mod'ing if the number is too big
	bool * theLED;
	switch(ledNum)
	{
		case 0:
			theLED = &theBank->leds.right_8;
			break;
		case 1:
			theLED = &theBank->leds.right_7;
			break;
		case 2:
			theLED = &theBank->leds.right_6;
			break;
		case 3:
			theLED = &theBank->leds.right_5;
			break;
		case 4:
			theLED = &theBank->leds.right_4;
			break;
		case 5:
			theLED = &theBank->leds.right_3;
			break;
		case 6:
			theLED = &theBank->leds.right_2;
			break;
		case 7:
			theLED = &theBank->leds.right_1;
			break;
		case 8:
			theLED = &theBank->leds.left_8;
			break;
		case 9:
			theLED = &theBank->leds.left_7;
			break;
		case 10:
			theLED = &theBank->leds.left_6;
			break;
		case 11:
			theLED = &theBank->leds.left_5;
			break;
		case 12:
			theLED = &theBank->leds.left_4;
			break;
		case 13:
			theLED = &theBank->leds.left_3;
			break;
		case 14:
			theLED = &theBank->leds.left_2;
			break;
		case 15:
			theLED = &theBank->leds.left_1;
			break;
		default:
			theLED = new bool;
			break;
	}
	return *theLED;
}


	
