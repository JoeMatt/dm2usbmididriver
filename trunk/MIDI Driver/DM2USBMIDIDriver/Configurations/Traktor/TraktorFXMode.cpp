/*
 *  TraktorFXMode.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/14/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "TraktorFXMode.h"
#include "DM2USBMIDI.h"
/*
-FX Mode / NO scratching
	LEDS for FX buttons should be controlled via MIDI IN, set in .tks file, don't do anything here
	except button two seems to always be non-sticky, so can controll here for less delay

	Rings Control
		FX Knobs 1 to 4

	Buttons Control
		Select FX Knob 1 to 4  -- Radio
			8
			1
			2
			3
		FX Button 1 - 4		   -- 2 is non stick, 1,3,4 handled by MIDI in via TKS file
			7 -- sticky
			6 -- non sticky
			5 -- sticky
			4 -- sticky
	Ring Center button
		Select next FX
	A-B Buttons
		deck monitor cue effect

	Shift Button
		Either ring controls the 'master fx' of the same parameter
		the LEDs need to be swapped out as well
*/

TraktorFXMode::TraktorFXMode(Bank * dm2bank) : TraktorModeInterface(dm2bank)
{	
	setDefaults();
}

void TraktorFXMode::setDefaults()
{
	myBank->leds.right_8 = ON;
	myBank->leds.right_1 = OFF;
	myBank->leds.right_2 = OFF;
	myBank->leds.right_3 = OFF;
	
	myBank->leds.right_4 = OFF;
	myBank->leds.right_5 = OFF;
	myBank->leds.right_6 = OFF;
	myBank->leds.right_7 = OFF;
	
	myBank->buttons.right_8 = TRUE;
	myBank->buttons.right_1 = FALSE;
	myBank->buttons.right_2 = FALSE;
	myBank->buttons.right_3 = FALSE;
	
	myBank->buttons.right_4 = FALSE;
	myBank->buttons.right_5 = FALSE;
	myBank->buttons.right_6 = FALSE;
	myBank->buttons.right_7 = FALSE;
	
	myBank->leds.left_8 = ON;
	myBank->leds.left_1 = OFF;
	myBank->leds.left_2 = OFF;
	myBank->leds.left_3 = OFF;
	
	myBank->leds.left_4 = OFF;
	myBank->leds.left_5 = OFF;
	myBank->leds.left_6 = OFF;
	myBank->leds.left_7 = OFF;
	
	myBank->buttons.left_8 = TRUE;
	myBank->buttons.left_1 = FALSE;
	myBank->buttons.left_2 = FALSE;
	myBank->buttons.left_3 = FALSE;
	
	myBank->buttons.left_4 = FALSE;
	myBank->buttons.left_5 = FALSE;
	myBank->buttons.left_6 = FALSE;
	myBank->buttons.left_7 = FALSE;
}
/*** LED Buttons ***/
void TraktorFXMode::buttonRight8Clicked(DM2USBMIDIDriver * dm2){ // SELECT FX KNOB 1 / DOUBLE CLICK RESET
	if(  dm2->status.right_8)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration( UpTime(), dm2->timeStamps.right_8);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_FX_KNOB1RESET,dm2);
	}		
	dm2->timeStamps.right_8 = UpTime();
	
	currentBank->leds.right_8 = ON;
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_2 = OFF;
	currentBank->leds.right_3 = OFF;
	
	currentBank->buttons.right_8 = TRUE;
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_2 = FALSE;
	currentBank->buttons.right_3 = FALSE;
}
void TraktorFXMode::buttonRight1Clicked(DM2USBMIDIDriver * dm2){// SELECT FX KNOB 2 / DOUBLE CLICK RESET
	if(  dm2->status.right_1)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration( UpTime(), dm2->timeStamps.right_1);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_FX_KNOB2RESET,dm2);
	}		
	dm2->timeStamps.right_1 = UpTime();
	
	currentBank->leds.right_8 = OFF;
	currentBank->leds.right_1 = ON;
	currentBank->leds.right_2 = OFF;
	currentBank->leds.right_3 = OFF;
	
	currentBank->buttons.right_8 = FALSE;
	currentBank->buttons.right_1 = TRUE;
	currentBank->buttons.right_2 = FALSE;
	currentBank->buttons.right_3 = FALSE;
}
void TraktorFXMode::buttonRight2Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_2)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration( UpTime(), dm2->timeStamps.right_2);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_FX_KNOB3RESET,dm2);
	}		
	dm2->timeStamps.right_2 = UpTime();
	
	currentBank->leds.right_8 = OFF;
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_2 = ON;
	currentBank->leds.right_3 = OFF;
	
	currentBank->buttons.right_8 = FALSE;
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_2 = TRUE;
	currentBank->buttons.right_3 = FALSE;
}
void TraktorFXMode::buttonRight3Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.right_3)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration( UpTime(), dm2->timeStamps.right_3);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKB_FX_KNOB4RESET,dm2);
	}		
	dm2->timeStamps.right_3 = UpTime();
	
	currentBank->leds.right_8 = OFF;
	currentBank->leds.right_1 = OFF;
	currentBank->leds.right_2 = OFF;
	currentBank->leds.right_3 = ON;
	
	currentBank->buttons.right_8 = FALSE;
	currentBank->buttons.right_1 = FALSE;
	currentBank->buttons.right_2 = FALSE;
	currentBank->buttons.right_3 = TRUE;
}
void TraktorFXMode::buttonRight4Clicked(DM2USBMIDIDriver * dm2){ // FX BUTTON 4
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
	dm2->noteBuf[1] = 35;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );*/
	makeBasicNote(currentBank->buttons.right_4,kNOTE_TRAKTOR_DECKB_FX_BUTTON4,dm2);
}
void TraktorFXMode::buttonRight5Clicked(DM2USBMIDIDriver * dm2){ // FX BUTTON 3
	if( !dm2->status.right_5 )
		return;
	if(currentBank->buttons.right_5) //Toggle is already active
	{
		currentBank->buttons.right_5 = FALSE;
		//currentBank->leds.right_5 = OFF; 
	}
	else
	{
		currentBank->buttons.right_5 = TRUE;
		//currentBank->leds.right_5 = ON;
	}
	/*dm2->noteBuf[0] = currentBank->buttons.right_5 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = 36;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );*/
	makeBasicNote(currentBank->buttons.right_5,kNOTE_TRAKTOR_DECKB_FX_BUTTON3,dm2);
}
void TraktorFXMode::buttonRight6Clicked(DM2USBMIDIDriver * dm2){ // FX BUTTON 2
	currentBank->leds.right_6 = dm2->status.right_6 ? ON : OFF;

	/*dm2->noteBuf[0] = dm2->status.right_6 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = 37;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );*/
	makeBasicNote(dm2->status.right_6,kNOTE_TRAKTOR_DECKB_FX_BUTTON2,dm2);
}
void TraktorFXMode::buttonRight7Clicked(DM2USBMIDIDriver * dm2){ // FX BUTTON 1
	if( !dm2->status.right_7 )
		return;
	if(currentBank->buttons.right_7) //Toggle is already active
	{
		currentBank->buttons.right_7 = FALSE;
		//currentBank->leds.right_7 = OFF; 
	}
	else
	{
		currentBank->buttons.right_7 = TRUE;
		//currentBank->leds.right_7 = ON;
	}
	/*dm2->noteBuf[0] = currentBank->buttons.right_7 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = 38;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );*/
	makeBasicNote(currentBank->buttons.right_7,kNOTE_TRAKTOR_DECKB_FX_BUTTON1,dm2);
}
/** Left LEDs **/
void TraktorFXMode::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.left_8)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_8);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_FX_KNOB1RESET,dm2); // Left knob 1 reset
	}		
	dm2->timeStamps.left_8 = UpTime();

	currentBank->leds.left_8 = ON;
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_2 = OFF;
	currentBank->leds.left_3 = OFF;
	
	currentBank->buttons.left_8 = TRUE;
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_2 = FALSE;
	currentBank->buttons.left_3 = FALSE;
}
void TraktorFXMode::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.left_1)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_1);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_FX_KNOB2RESET,dm2); // Left knob2 reset
	}		
	dm2->timeStamps.left_1 = UpTime();
	
	currentBank->leds.left_8 = OFF;
	currentBank->leds.left_1 = ON;
	currentBank->leds.left_2 = OFF;
	currentBank->leds.left_3 = OFF;
	
	currentBank->buttons.left_8 = FALSE;
	currentBank->buttons.left_1 = TRUE;
	currentBank->buttons.left_2 = FALSE;
	currentBank->buttons.left_3 = FALSE;
}
void TraktorFXMode::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.left_2)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_2);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_FX_KNOB3RESET,dm2); // left knob3 reset
	}		
	dm2->timeStamps.left_2 = UpTime();
	
	currentBank->leds.left_8 = OFF;
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_2 = ON;
	currentBank->leds.left_3 = OFF;
	
	currentBank->buttons.left_8 = FALSE;
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_2 = TRUE;
	currentBank->buttons.left_3 = FALSE;
}
void TraktorFXMode::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){
	if(  dm2->status.left_3)
	{
		float deltaTime;
		deltaTime = (float) AbsoluteDeltaToDuration(UpTime(), *(AbsoluteTime *) &dm2->timeStamps.left_3);
		
		if ( deltaTime > kDoubleClickTime )
			makeBasicNote(TRUE,kNOTE_TRAKTOR_DECKA_FX_KNOB4RESET,dm2); // left knob4 reset
	}		
	dm2->timeStamps.left_3 = UpTime();
	
	currentBank->leds.left_8 = OFF;
	currentBank->leds.left_1 = OFF;
	currentBank->leds.left_2 = OFF;
	currentBank->leds.left_3 = ON;
	
	currentBank->buttons.left_8 = FALSE;
	currentBank->buttons.left_1 = FALSE;
	currentBank->buttons.left_2 = FALSE;
	currentBank->buttons.left_3 = TRUE;
}
void TraktorFXMode::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){ // Left FX button 4
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
	dm2->noteBuf[0] = currentBank->buttons.left_4 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = kNOTE_TRAKTOR_DECKA_FX_BUTTON4;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );	
	// makeBasicNote(currentBank->buttons.left_4,kNOTE_TRAKTOR_DECKA_FX_BUTTON4,dm2);
}
void TraktorFXMode::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){ // Left FX Button 3
	if( !dm2->status.left_5 )
		return;
	if(currentBank->buttons.left_5) //Toggle is already active
	{
		currentBank->buttons.left_5 = FALSE;
		//currentBank->leds.left_5 = OFF; 
	}
	else
	{
		currentBank->buttons.left_5 = TRUE;
		//currentBank->leds.left_5 = ON;
	}
	dm2->noteBuf[0] = currentBank->buttons.left_5 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = kNOTE_TRAKTOR_DECKA_FX_BUTTON3;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );
	// makeBasicNote(currentBank->buttons.left_5,kNOTE_TRAKTOR_DECKA_FX_BUTTON3,dm2);
}
void TraktorFXMode::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){ // Left FX button 2
	currentBank->leds.left_6 = dm2->status.left_6 ? ON : OFF;
	
	dm2->noteBuf[0] = dm2->status.left_6 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = kNOTE_TRAKTOR_DECKA_FX_BUTTON2;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );
	// makeBasicNote(dm2->status.left_6,kNOTE_TRAKTOR_DECKA_FX_BUTTON2,dm2);
}
void TraktorFXMode::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){ // Left FX Button 1
	if( !dm2->status.left_7 )
		return;
	if(currentBank->buttons.left_7) //Toggle is already active
	{
		currentBank->buttons.left_7 = FALSE;
		//currentBank->leds.left_7 = OFF; 
	}
	else
	{
		currentBank->buttons.left_7 = TRUE;
		//currentBank->leds.left_7 = ON;
	}
	dm2->noteBuf[0] = currentBank->buttons.left_7 ? 0x90 : 0x80;         
	dm2->noteBuf[1] = kNOTE_TRAKTOR_DECKA_FX_BUTTON1;														
	dm2->noteBuf[2] = 127;
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, 64, dm2->pkt, dm2->timeStamp, 3, (Byte*)&dm2->noteBuf );
	// makeBasicNote(currentBank->buttons.left_7,kNOTE_TRAKTOR_DECKA_FX_BUTTON1,dm2);
}

/**** Rings *****/
void TraktorFXMode::leftRingSpun(DM2USBMIDIDriver * dm2){
	int accel, modifier;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 24
	if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{		
		modifier = 0; //Button 8, default, FX mod 1
		if(currentBank->buttons.left_1)//FX Mod2
			modifier = 1;
		
		else if(currentBank->buttons.left_2)//FX Mod 3
			modifier = 2;
		
		else if(currentBank->buttons.left_3) //FX Mod 4
			modifier = 3;
		
		dm2->noteBuf[0] = 0xB0 + modifier; //shift the channel up based on what 'mode' the LED buttons put us in. 
		dm2->noteBuf[1] = kCC_TRAKTOR_FX_KNOB;
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	//	printf("Sending FX left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}
void TraktorFXMode::rightRingSpun(DM2USBMIDIDriver * dm2){
	int accel, modifier;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 24
	if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{		
		modifier = 0; //Button 8, FX Mod 1
		if(currentBank->buttons.right_1)// FX <Mod 2
			modifier = 1;
		
		else if(currentBank->buttons.right_2)// FX Mod 3
			modifier = 2;
		
		else if(currentBank->buttons.right_3) // FX Mod 4
			modifier = 3;
		
		dm2->noteBuf[0] = 0xB4 + modifier; //shift the channel up based on what 'mode' the LED buttons put us in. 
		dm2->noteBuf[1] = kCC_TRAKTOR_FX_KNOB;
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	//	printf("Sending FX right ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}

/** Other Buttons ***/
void TraktorFXMode::leftClicked(DM2USBMIDIDriver * dm2) // DECKA NEXT EFFECT SELECT
{makeBasicNote(dm2->status.left,kNOTE_TRAKTOR_DECKA_FX_SELECTNEXT,dm2);}
void TraktorFXMode::rightClicked(DM2USBMIDIDriver * dm2) // DECKB NEXT EFFECT SELECT
{makeBasicNote(dm2->status.right,kNOTE_TRAKTOR_DECKB_FX_SELECTNEXT,dm2);}

void TraktorFXMode::bottomAClicked(DM2USBMIDIDriver * dm2) // DECK A CUE EFFECT
{makeBasicNote(dm2->status.bottom_A,kNOTE_TRAKTOR_DECKA_FX_CUE,dm2);}

void TraktorFXMode::bottomBClicked(DM2USBMIDIDriver * dm2) // DECK B CUE EFFECT
{makeBasicNote(dm2->status.bottom_B,kNOTE_TRAKTOR_DECKB_FX_CUE,dm2);}
/**** Input ****/
void TraktorFXMode::buttonReceived(int number,int value)
{
	switch(number)
	{
		case 6:
			currentBank->buttons.right_7 = (value == 127) ? 1 : 0;
			currentBank->leds.right_7 = (value == 127) ? ON : OFF;
			break;
		case 4:
			currentBank->buttons.right_5 = (value == 127) ? 1 : 0;
			currentBank->leds.right_5 = (value == 127) ? ON : OFF;
			break;
		case 3:
			currentBank->buttons.right_4 = (value == 127) ? 1 : 0;
			currentBank->leds.right_4 = (value == 127) ? ON : OFF;
			break;
		case 11:
			currentBank->buttons.left_4 = (value == 127) ? 1 : 0;
			currentBank->leds.left_4 = (value == 127) ? ON : OFF;
			break;
		case 12:
			currentBank->buttons.left_5 = (value == 127) ? 1 : 0;
			currentBank->leds.left_5 = (value == 127) ? ON : OFF;
			break;
		case 14:
			currentBank->buttons.left_7 = (value == 127) ? 1 : 0;
			currentBank->leds.left_7 = (value == 127) ? ON : OFF;
			break;
	}
	printf("Number: %i, value: %i\n",number, value);
}