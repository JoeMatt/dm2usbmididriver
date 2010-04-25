/*
 *  TraktorMixMode.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/21/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "TraktorMixMode.h"
#include "DM2USBMIDI.h"

/*
 -play (1) - Sticky (Blinks when playing to MIDI clock)
 -cue play (2)
 -cue pause (3)
 -Cue Set	(4)

 -sync - Sticky (5)
 -key lock - sticky

 
 -bpm tap - A/B Buttons
 
 wheel
 *-pitch / with middle
 *-scratch / with center
 -bend
 *-wind
 
 */

TraktorMixMode::TraktorMixMode(Bank * dm2bank) : TraktorModeInterface(dm2bank), leftScratch(FALSE), rightScratch(FALSE)
{
	setDefaults();
}
void TraktorMixMode::setDefaults()
{
	myBank->leds.right_1 = OFF;
	myBank->leds.right_2 = OFF;
	myBank->leds.right_3 = OFF;
	myBank->leds.right_4 = OFF;
	myBank->leds.right_5 = OFF;
	myBank->leds.right_6 = OFF;
	myBank->leds.right_7 = OFF;
	myBank->leds.right_8 = OFF;
	
	myBank->buttons.right_1 = FALSE;
	myBank->buttons.right_2 = FALSE;
	myBank->buttons.right_3 = FALSE;	
	myBank->buttons.right_4 = FALSE;
	myBank->buttons.right_5 = FALSE;
	myBank->buttons.right_6 = FALSE;
	myBank->buttons.right_7 = FALSE;
	myBank->buttons.right_8 = FALSE;
	
	myBank->leds.left_1 = OFF;
	myBank->leds.left_2 = OFF;
	myBank->leds.left_3 = OFF;
	myBank->leds.left_4 = OFF;
	myBank->leds.left_5 = OFF;
	myBank->leds.left_6 = OFF;
	myBank->leds.left_7 = OFF;
	myBank->leds.left_8 = OFF;
	
	myBank->buttons.left_1 = FALSE;
	myBank->buttons.left_2 = FALSE;
	myBank->buttons.left_3 = FALSE;	
	myBank->buttons.left_4 = FALSE;
	myBank->buttons.left_5 = FALSE;
	myBank->buttons.left_6 = FALSE;
	myBank->buttons.left_7 = FALSE;
	myBank->buttons.left_8 = FALSE;
}
/*** LED Buttons ***/
	/*** Right Buttons ***/
	void TraktorMixMode::buttonRight1Clicked(DM2USBMIDIDriver * dm2){					// Right Play
		if( !dm2->status.right_1 )
			return;
		if(myBank->buttons.right_1) //Toggle is already active
		{
			myBank->buttons.right_1 = FALSE;
			//myBank->leds.right_1 = OFF; 
		}
		else
		{
			myBank->buttons.right_1 = TRUE;
			//myBank->leds.right_1 = ON;
		}
		
		makeBasicNote(myBank->buttons.right_1, kNOTE_TRAKTOR_DECKB_MIX_PLAY,dm2);
	}
	void TraktorMixMode::buttonRight2Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.right_2, kNOTE_TRAKTOR_DECKB_MIX_CUEPLAY,dm2);}	// Right Cue play
	void TraktorMixMode::buttonRight3Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.right_3, kNOTE_TRAKTOR_DECKB_MIX_CUEPAUSE,dm2);} // Right Cue Pause
	void TraktorMixMode::buttonRight4Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.right_4, kNOTE_TRAKTOR_DECKB_MIX_CUESET,dm2);}	// Right Cue Set
	void TraktorMixMode::buttonRight5Clicked(DM2USBMIDIDriver * dm2){					// Right Sync (sticky)
		if( !dm2->status.right_5 )
			return;
		if(myBank->buttons.right_5) //Toggle is already active
		{
			myBank->buttons.right_5 = FALSE;
			//myBank->leds.right_5 = OFF; 
		}
		else
		{
			myBank->buttons.right_5 = TRUE;
			//myBank->leds.right_5 = ON;
		}
		
		makeBasicNote(myBank->buttons.right_5, kNOTE_TRAKTOR_DECKB_MIX_SYNC,dm2);
	}
	void TraktorMixMode::buttonRight6Clicked(DM2USBMIDIDriver * dm2){		// Right key lock
		if( !dm2->status.right_6 )
			return;
		if(myBank->buttons.right_6) //Toggle is already active
		{
			myBank->buttons.right_6 = FALSE;
			//myBank->leds.right_6 = OFF; 
		}
		else
		{
			myBank->buttons.right_6 = TRUE;
			//myBank->leds.right_6 = ON;
		}
		makeBasicNote(myBank->buttons.right_6, kNOTE_TRAKTOR_DECKB_MIX_KEYLOCK,dm2);	}	

	void TraktorMixMode::buttonRight7Clicked(DM2USBMIDIDriver * dm2){
	makeBasicNote(dm2->status.right_7, kNOTE_TRAKTOR_DECKB_MIX_CUE_PREVIOUS,dm2);}	// Right Cue previous

	void TraktorMixMode::buttonRight8Clicked(DM2USBMIDIDriver * dm2){
	makeBasicNote(dm2->status.right_8, kNOTE_TRAKTOR_DECKB_MIX_CUE_NEXT,dm2);}	// Right Cue next


/*** LEFT RING BUTTONS ***/
	void TraktorMixMode::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){					// Left Play
		if( !dm2->status.left_1 )
			return;
		if(myBank->buttons.left_1) //Toggle is already active
		{
			myBank->buttons.left_1 = FALSE;
			//myBank->leds.left_1 = OFF; 
		}
		else
		{
			myBank->buttons.left_1 = TRUE;
			//myBank->leds.left_1 = ON;
		}
		
		makeBasicNote(myBank->buttons.left_1, kNOTE_TRAKTOR_DECKA_MIX_PLAY,dm2);
	}
	void TraktorMixMode::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.left_2, kNOTE_TRAKTOR_DECKA_MIX_CUEPLAY,dm2);}	// Left Cue play
	void TraktorMixMode::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.left_3, kNOTE_TRAKTOR_DECKA_MIX_CUEPAUSE,dm2);}	// Left Cue Pause
	void TraktorMixMode::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){
		makeBasicNote(dm2->status.left_4, kNOTE_TRAKTOR_DECKA_MIX_CUESET,dm2);}	// Left Cue Set
	void TraktorMixMode::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){					// Left Sync (sticky)
		if( !dm2->status.left_5 )
			return;
		if(myBank->buttons.left_5) //Toggle is already active
		{
			myBank->buttons.left_5 = FALSE;
			//myBank->leds.left_5 = OFF; 
		}
		else
		{
			myBank->buttons.left_5 = TRUE;
			//myBank->leds.left_5 = ON;
		}
		
		makeBasicNote(myBank->buttons.left_5, kNOTE_TRAKTOR_DECKA_MIX_SYNC,dm2);
	}
	void TraktorMixMode::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){		// left key lock
		if( !dm2->status.left_6 )
			return;
		if(myBank->buttons.left_6) //Toggle is already active
		{
			myBank->buttons.left_6 = FALSE;
			//myBank->leds.left_6 = OFF; 
		}
		else
		{
			myBank->buttons.left_6 = TRUE;
			//myBank->leds.left_6 = ON;
		}
		makeBasicNote(myBank->buttons.left_6, kNOTE_TRAKTOR_DECKA_MIX_KEYLOCK,dm2);	
		}	

	void TraktorMixMode::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){
	makeBasicNote(dm2->status.left_7, kNOTE_TRAKTOR_DECKA_MIX_CUE_PREVIOUS,dm2);}	// Left Cue previous

	void TraktorMixMode::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){
	makeBasicNote(dm2->status.left_8, kNOTE_TRAKTOR_DECKA_MIX_CUE_NEXT,dm2);}	// Left Cue next
/*** END LED BUTTONS ***/

/**** Rings *****/
void TraktorMixMode::leftRingSpun(DM2USBMIDIDriver * dm2){
	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 24
	if(dm2->status.left)//scratching left
	{
		dm2->noteBuf[0] = 0xB0; //shift the channel up 8 if holding the round button in the center thingy
		dm2->noteBuf[1] = kCC_TRAKTOR_SCRATCH;
		dm2->noteBuf[2] = accel;
		
		//makeCCNote(0xB0,kCC_TRAKTOR_SCRATCH,accel,dm2);
	}
	else if(dm2->status.middle) // pitch bending left
	{
		dm2->noteBuf[0] = 0xB0; 
		dm2->noteBuf[1] = kCC_TRAKTOR_PITCH;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB0,kCC_TRAKTOR_PITCH,accel,dm2);
	}
	else if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{				
		dm2->noteBuf[0] = 0xB0; 
		dm2->noteBuf[1] = kCC_TRAKTOR_DECKWIND; //deck wind left
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#ifdef DEBUG
	//	printf("Sending Loop left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}
void TraktorMixMode::rightRingSpun(DM2USBMIDIDriver * dm2){
	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 24
	if(dm2->status.right)//scratching right
	{
		dm2->noteBuf[0] = 0xB1; //When Scrach button is held, send CC 22, chan 1(left) and 2(right)
		dm2->noteBuf[1] = kCC_TRAKTOR_SCRATCH;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB1,kCC_TRAKTOR_SCRATCH,accel,dm2);
	}
	else if(dm2->status.middle) // pitch bending left
	{
		dm2->noteBuf[0] = 0xB1; 
		dm2->noteBuf[1] = kCC_TRAKTOR_PITCH;
		dm2->noteBuf[2] = accel;
		//makeCCNote(0xB1,kCC_TRAKTOR_PITCH,accel,dm2);
	}
	else if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{				
		dm2->noteBuf[0] = 0xB1;
		dm2->noteBuf[1] = kCC_TRAKTOR_DECKWIND; //CC 26, deck wind
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#ifdef DEBUG
	//	printf("Sending Loop right ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}


/** Other Buttons ***/
void TraktorMixMode::leftClicked(DM2USBMIDIDriver * dm2)
{
	if(dm2->status.left)
		leftScratch = TRUE;
	DM2Configuration::leftClicked(dm2);
}

void TraktorMixMode::rightClicked(DM2USBMIDIDriver * dm2)
{
	if(dm2->status.right)
		rightScratch = TRUE;
	DM2Configuration::rightClicked(dm2);	
}

/** Mix specific ***/
void TraktorMixMode::bottomAClicked(DM2USBMIDIDriver * dm2)									//Left BMP tap
{ makeBasicNote(dm2->status.bottom_A, kNOTE_TRAKTOR_DECKA_MIX_CUE, dm2);}
void TraktorMixMode::bottomBClicked(DM2USBMIDIDriver * dm2)									//Right BPM tap
{ makeBasicNote(dm2->status.bottom_B, kNOTE_TRAKTOR_DECKB_MIX_CUE, dm2);}

/**** Input ****/
void TraktorMixMode::buttonReceived(int number, int value)
{
	//Which LED number is the note for?, from 0 to 15
	switch(number)
	{
		case 0: // play
			myBank->buttons.right_1 = (value == 127) ? 1 : 0;
			myBank->leds.right_1 = (value == 127) ? ON : OFF;
			break;
		case 4:	//sync
			myBank->buttons.right_5 = (value == 127) ? 1 : 0;
			myBank->leds.right_5 = (value == 127) ? ON : OFF;
			break;
		case 5: // key lock
			myBank->buttons.right_6 = (value == 127) ? 1 : 0;
			myBank->leds.right_6 = (value == 127) ? ON : OFF;
			break;
		case 8:
			myBank->buttons.left_1 = (value == 127) ? 1 : 0;
			myBank->leds.left_1 = (value == 127) ? ON : OFF;
			break;
		case 12:
			myBank->buttons.left_5 = (value == 127) ? 1 : 0;
			myBank->leds.left_5 = (value == 127) ? ON : OFF;
			break;
		case 13:
			myBank->buttons.left_6 = (value == 127) ? 1 : 0;
			myBank->leds.left_6 = (value == 127) ? ON : OFF;
			break;
	}
}
