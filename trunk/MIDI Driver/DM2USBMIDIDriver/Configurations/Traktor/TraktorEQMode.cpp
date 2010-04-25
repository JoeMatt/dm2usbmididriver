/*
 *  TraktorEQMode.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/14/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */
#include <CoreServices/CoreServices.h>
#include "/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/CarbonCore.framework/Versions/A/Headers/DriverServices.h"
#include "TraktorEQMode.h"
#include "DM2USBMIDI.h"


/*-EQ Mode / Scratch
	Lights indicate which is the active setting that the wheel will change
	Rings control
		High
		Mid
		Low
		Balance
		Channel Volume
		Scratching

	Buttons Control     -- Double Click on any of these is a reset
	Select High (8)		-------\
	Select Mid  (7)				|
	Select Low	(6)				|---Radio	
	Select Balance(1)			 |
	Select Channel Volume(5) ----/

	High Kill (2)	- Sticky
	Mid Kill  (3)	- Sticky
	Low Kill  (4)	- Sticky

	Left/Right Center Buttons - Left/Right Scratch mode


*/
TraktorEQMode::TraktorEQMode(Bank * dm2bank) : TraktorModeInterface(dm2bank), leftScratch(FALSE), rightScratch(FALSE)
{	
	setDefaults();
}

void TraktorEQMode::setDefaults()
{
	myBank->leds.right_1 = OFF;
	myBank->leds.right_2 = OFF;
	myBank->leds.right_3 = OFF;
	myBank->leds.right_4 = OFF;
	myBank->leds.right_5 = ON;
	myBank->leds.right_6 = OFF;
	myBank->leds.right_7 = OFF;
	myBank->leds.right_8 = OFF;
	
	myBank->buttons.right_1 = FALSE;
	myBank->buttons.right_2 = FALSE;
	myBank->buttons.right_3 = FALSE;	
	myBank->buttons.right_4 = FALSE;
	myBank->buttons.right_5 = TRUE;
	myBank->buttons.right_6 = FALSE;
	myBank->buttons.right_7 = FALSE;
	myBank->buttons.right_8 = FALSE;
	
	myBank->leds.left_1 = OFF;
	myBank->leds.left_2 = OFF;
	myBank->leds.left_3 = OFF;
	myBank->leds.left_4 = OFF;
	myBank->leds.left_5 = ON;
	myBank->leds.left_6 = OFF;
	myBank->leds.left_7 = OFF;
	myBank->leds.left_8 = OFF;
	
	myBank->buttons.left_1 = FALSE;
	myBank->buttons.left_2 = FALSE;
	myBank->buttons.left_3 = FALSE;	
	myBank->buttons.left_4 = FALSE;
	myBank->buttons.left_5 = TRUE;
	myBank->buttons.left_6 = FALSE;
	myBank->buttons.left_7 = FALSE;
	myBank->buttons.left_8 = FALSE;
}

void TraktorEQMode::leftRingSpun(DM2USBMIDIDriver * dm2)
{

	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 22, channel 2
	if(dm2->status.left)//scratching right
	{
		dm2->noteBuf[0] = 0xB0; //shift the channel up 8 if holding the round button in the center thingy
		dm2->noteBuf[1] = kCC_TRAKTOR_SCRATCH;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB0,kCC_TRAKTOR_SCRATCH,accel,dm2);
	}
	else if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{
		if(leftScratch == true) // Prevent scratch ring 'spill' 
		{
			if(accel == 64)
				leftScratch = false;
			return;
		}
		
		int modifier;
		if(currentBank->buttons.left_8)//EQ High
			modifier = 0;
		else if(currentBank->buttons.left_7)//EQ Mid
			modifier = 1;
		
		else if(currentBank->buttons.left_6)//EQ Low
			modifier = 2;
		
		else if(currentBank->buttons.left_1) //Balance
			modifier = 3;
		
		else if(currentBank->buttons.left_5) //Volume
			modifier = 4;
		else
			modifier = 0;
		
		dm2->noteBuf[0] = 0xB0 + modifier; //shift the channel up based on what 'mode' the LED buttons put us in. 
		dm2->noteBuf[1] = kCC_TRAKTOR_EQ_KNOB;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB0 + modifier,kCC_TRAKTOR_EQ_KNOB,accel,dm2);
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#ifdef DEBUG
//	printf("Sending EQ left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif

}

void TraktorEQMode::rightRingSpun(DM2USBMIDIDriver * dm2)
{

	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 22, channel 1
	if(dm2->status.right)//scratching right
	{
		dm2->noteBuf[0] = 0xB1; //When Scrach button is held, send CC 22, chan 1(left) and 2(right)
		dm2->noteBuf[1] = kCC_TRAKTOR_SCRATCH;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB1,kCC_TRAKTOR_SCRATCH,accel,dm2);
	}
	else if( accel == 64 || abs(accel - 64) > 0)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{
		if(rightScratch == true) // Prevent scratch ring 'spill' 
		{
			if(accel == 64)
				rightScratch = false;
			return;
		}
		int modifier;
		if(currentBank->buttons.right_8)
			modifier = 0;
		else if(currentBank->buttons.right_7)
			modifier = 1;
		
		else if(currentBank->buttons.right_6)
			modifier = 2;
		
		else if(currentBank->buttons.right_1)
			modifier = 3;
		
		else if(currentBank->buttons.right_5)
			modifier = 4;
		else
			modifier = 0;
		
		dm2->noteBuf[0] = 0xB5 + modifier; //shift the channel up 8 if holding the round button in the center thingy
		dm2->noteBuf[1] = kCC_TRAKTOR_EQ_KNOB;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB5 + modifier,kCC_TRAKTOR_EQ_KNOB,accel,dm2);
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
	#ifdef DEBUG
//	printf("Sending EQ right ring: %x %i %i, rightScratch: %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2],rightScratch);
	#endif
}
/******* END Scratch Rings ***/
/******* RIGHT LEDs **********/

void TraktorEQMode::buttonRight2Clicked(DM2USBMIDIDriver * dm2){ // HIGH KILL
	if( !dm2->status.right_2 )
		return;
	if(currentBank->buttons.right_2) //Toggle is already active
	{
		currentBank->buttons.right_2 = FALSE;
		//currentBank->leds.right_2 = OFF; 
	}
	else
	{
		currentBank->buttons.right_2 = TRUE;
		//currentBank->leds.right_2 = ON;
	}
       //if button is already on, send 80 (noteoff), other was it was 0 (off) and now we want a note on.
	makeBasicNote(currentBank->buttons.right_2,kNOTE_TRAKTOR_DECKB_EQ_HIGHKILL,dm2);
}
void TraktorEQMode::buttonRight3Clicked(DM2USBMIDIDriver * dm2){ // MID KILL
	if( !dm2->status.right_3 )
		return;
	if(currentBank->buttons.right_3) //Toggle is already active
	{
		currentBank->buttons.right_3 = FALSE;
		//currentBank->leds.right_3 = OFF; 
	}
	else
	{
		currentBank->buttons.right_3 = TRUE;
		//currentBank->leds.right_3 = ON;
	}
	makeBasicNote(currentBank->buttons.right_3,kNOTE_TRAKTOR_DECKB_EQ_MIDKILL,dm2);
}
void TraktorEQMode::buttonRight4Clicked(DM2USBMIDIDriver * dm2){ // LOW KILL
	if( !dm2->status.right_4 )
		return;
	if(currentBank->buttons.right_4) //Toggle is already active
	{
		currentBank->buttons.right_4 = FALSE;
		//currentBank->leds.right_4 = OFF; 
	}
	else
	{
		currentBank->buttons.right_4 = TRUE;
		//currentBank->leds.right_4 = ON;
	}
	/*dm2->noteBuf[0] = currentBank->buttons.right_4 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = 51;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 51, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );
	//printf("Right Low Kill: [1] %x, [2] %i, [3] %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);*/
	makeBasicNote(currentBank->buttons.right_4,kNOTE_TRAKTOR_DECKB_EQ_LOWKILL,dm2);
}
void TraktorEQMode::buttonRight1Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_1)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration( UpTime(), dm2->timeStamps.right_1);

		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_EQ_BALANCERESET,dm2); // BALANCE RESET
	}		
	dm2->timeStamps.right_1 = UpTime();
	
	currentBank->leds.right_1 = ON;
	currentBank->leds.right_5 = OFF;
	currentBank->leds.right_6 = OFF;
	currentBank->leds.right_7 = OFF;
	currentBank->leds.right_8 = OFF;
	
	currentBank->buttons.right_1 = TRUE;
	currentBank->buttons.right_5 = FALSE;
	currentBank->buttons.right_6 = FALSE;
	currentBank->buttons.right_7 = FALSE;
	currentBank->buttons.right_8 = FALSE;
}

void TraktorEQMode::buttonRight5Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_5)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.right_5);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_EQ_VOLUMERESET,dm2); // VOLUME RESET
	}		
	dm2->timeStamps.right_5 = UpTime();
	
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_5 = ON;
	currentBank->leds.right_6 = OFF;
	currentBank->leds.right_7 = OFF;
	currentBank->leds.right_8 = OFF;
	
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_5 = TRUE;
	currentBank->buttons.right_6 = FALSE;
	currentBank->buttons.right_7 = FALSE;
	currentBank->buttons.right_8 = FALSE;}
void TraktorEQMode::buttonRight6Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_6)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.right_6);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_EQ_LOWRESET,dm2); // LOW RESET
	}		
	dm2->timeStamps.right_6 = UpTime();
	
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_5 = OFF;
	currentBank->leds.right_6 = ON;
	currentBank->leds.right_7 = OFF;
	currentBank->leds.right_8 = OFF;
	
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_5 = FALSE;
	currentBank->buttons.right_6 = TRUE;
	currentBank->buttons.right_7 = FALSE;
	currentBank->buttons.right_8 = FALSE;}
void TraktorEQMode::buttonRight7Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_7)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.right_7);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_EQ_MIDRESET,dm2); // MID RESET
	}		
	dm2->timeStamps.right_7 = UpTime();
	
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_5 = OFF;
	currentBank->leds.right_6 = OFF;
	currentBank->leds.right_7 = ON;
	currentBank->leds.right_8 = OFF;
	
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_5 = FALSE;
	currentBank->buttons.right_6 = FALSE;
	currentBank->buttons.right_7 = TRUE;
	currentBank->buttons.right_8 = FALSE;}
void TraktorEQMode::buttonRight8Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_8)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.right_8);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_EQ_HIGHRESET,dm2); // HIGH RESET
	}		
	dm2->timeStamps.right_8 = UpTime();
	
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_5 = OFF;
	currentBank->leds.right_6 = OFF;
	currentBank->leds.right_7 = OFF;
	currentBank->leds.right_8 = ON;
	
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_5 = FALSE;
	currentBank->buttons.right_6 = FALSE;
	currentBank->buttons.right_7 = FALSE;
	currentBank->buttons.right_8 = TRUE;}

/***** END Right LEDs *****/
/***** LEFT LEDs **********/

void TraktorEQMode::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.left_1)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_1);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_EQ_BALANCERESET,dm2); // Balance reset
	}		
	dm2->timeStamps.left_1 = UpTime();
	
	currentBank->leds.left_1 = ON;
	currentBank->leds.left_5 = OFF;
	currentBank->leds.left_6 = OFF;
	currentBank->leds.left_7 = OFF;
	currentBank->leds.left_8 = OFF;
	
	currentBank->buttons.left_1 = TRUE;
	currentBank->buttons.left_5 = FALSE;
	currentBank->buttons.left_6 = FALSE;
	currentBank->buttons.left_7 = FALSE;
	currentBank->buttons.left_8 = FALSE;
}
void TraktorEQMode::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){ // High kill
	if( !dm2->status.left_2 )
		return;
	if(currentBank->buttons.left_2) //Toggle is already active
	{
		currentBank->buttons.left_2 = FALSE;
		//currentBank->leds.left_2 = OFF; 
	}
	else
	{
		currentBank->buttons.left_2 = TRUE;
		//currentBank->leds.left_2 = ON;
	}
	//if button is already on, send 80 (noteoff), other was it was 0 (off) and now we want a note on.
	makeBasicNote(currentBank->buttons.left_2,kNOTE_TRAKTOR_DECKA_EQ_HIGHKILL,dm2);
	
}
void TraktorEQMode::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){ // Mid Kill
	if( !dm2->status.left_3 )
		return;
	if(currentBank->buttons.left_3) //Toggle is already active
	{
		currentBank->buttons.left_3 = FALSE;
		//currentBank->leds.left_3 = OFF; 
	}
	else
	{
		currentBank->buttons.left_3 = TRUE;
		//currentBank->leds.left_3 = ON;
	}
	makeBasicNote(currentBank->buttons.left_3,kNOTE_TRAKTOR_DECKA_EQ_MIDKILL,dm2);
}
void TraktorEQMode::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){ // Low Kill
	if( !dm2->status.left_4 )
		return;
	if(currentBank->buttons.left_4) //Toggle is already active
	{
		currentBank->buttons.left_4 = FALSE;
		//currentBank->leds.left_4 = OFF; 
	}
	else
	{
		currentBank->buttons.left_4 = TRUE;
		//currentBank->leds.left_4 = ON;
	}
	printf("Left low kill sent\n");
	makeBasicNote(currentBank->buttons.left_4,kNOTE_TRAKTOR_DECKA_EQ_LOWKILL,dm2);
}
void TraktorEQMode::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){	//Volume select	
	if(  dm2->status.left_5)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_5);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_EQ_VOLUMERESET,dm2);//Volume reset
	}		
	dm2->timeStamps.left_5 = UpTime();
	
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_5 = ON;
	currentBank->leds.left_6 = OFF;
	currentBank->leds.left_7 = OFF;
	currentBank->leds.left_8 = OFF;
	
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_5 = TRUE;
	currentBank->buttons.left_6 = FALSE;
	currentBank->buttons.left_7 = FALSE;
	currentBank->buttons.left_8 = FALSE;}
void TraktorEQMode::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){ // Low EQ Select
	if(  dm2->status.left_6)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_6);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_EQ_LOWRESET,dm2);	//Low EQ reset
	}		
	dm2->timeStamps.left_6 = UpTime();
	
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_5 = OFF;
	currentBank->leds.left_6 = ON;
	currentBank->leds.left_7 = OFF;
	currentBank->leds.left_8 = OFF;
	
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_5 = FALSE;
	currentBank->buttons.left_6 = TRUE;
	currentBank->buttons.left_7 = FALSE;
	currentBank->buttons.left_8 = FALSE;}
void TraktorEQMode::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){	// Mid EQ Select
	if(  dm2->status.left_7)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_7);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_EQ_MIDRESET,dm2); // Mid EQ reset
	}		
	dm2->timeStamps.left_7 = UpTime();
	
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_5 = OFF;
	currentBank->leds.left_6 = OFF;
	currentBank->leds.left_7 = ON;
	currentBank->leds.left_8 = OFF;
	
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_5 = FALSE;
	currentBank->buttons.left_6 = FALSE;
	currentBank->buttons.left_7 = TRUE;
	currentBank->buttons.left_8 = FALSE;}
void TraktorEQMode::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){ // High EQ Select
	if(  dm2->status.left_8)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_8);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_EQ_HIGHRESET,dm2); // High EQ Reset
	}		
	dm2->timeStamps.left_8 = UpTime();
	
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_5 = OFF;
	currentBank->leds.left_6 = OFF;
	currentBank->leds.left_7 = OFF;
	currentBank->leds.left_8 = ON;
	
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_5 = FALSE;
	currentBank->buttons.left_6 = FALSE;
	currentBank->buttons.left_7 = FALSE;
	currentBank->buttons.left_8 = TRUE;}

/*** OTher Buttons ***/

void TraktorEQMode::leftClicked(DM2USBMIDIDriver * dm2)
{
	if(dm2->status.left)
		leftScratch = TRUE;
	DM2Configuration::leftClicked(dm2);
}

void TraktorEQMode::rightClicked(DM2USBMIDIDriver * dm2)
{
	if(dm2->status.right)
		rightScratch = TRUE;
	DM2Configuration::rightClicked(dm2);	
}

void TraktorEQMode::bottomAClicked(DM2USBMIDIDriver * dm2)									//Left BMP tap
{ makeBasicNote(dm2->status.bottom_A, kNOTE_TRAKTOR_DECKA_MIX_CUE, dm2);}
void TraktorEQMode::bottomBClicked(DM2USBMIDIDriver * dm2)									//Right BPM tap
{ makeBasicNote(dm2->status.bottom_B, kNOTE_TRAKTOR_DECKB_MIX_CUE, dm2);}

/**** Input ****/
void TraktorEQMode::buttonReceived(int number, int value)
{
	//Which LED number is the note for?
	switch(number)
	{
		case 1:
			currentBank->buttons.right_2 = (value == 127) ? 1 : 0;
			currentBank->leds.right_2 = (value == 127) ? ON : OFF;
			break;
		case 2:
			currentBank->buttons.right_3 = (value == 127) ? 1 : 0;
			currentBank->leds.right_3 = (value == 127) ? ON : OFF;
			break;
		case 3:
			currentBank->buttons.right_4 = (value == 127) ? 1 : 0;
			currentBank->leds.right_4 = (value == 127) ? ON : OFF;
			break;
		case 9:
			currentBank->buttons.left_2 = (value == 127) ? 1 : 0;
			currentBank->leds.left_2 = (value == 127) ? ON : OFF;
			break;
		case 10:
			currentBank->buttons.left_3 = (value == 127) ? 1 : 0;
			currentBank->leds.left_3 = (value == 127) ? ON : OFF;
			break;
		case 11:
			currentBank->buttons.left_4 = (value == 127) ? 1 : 0;
			currentBank->leds.left_4 = (value == 127) ? ON : OFF;
			break;
	}
}
