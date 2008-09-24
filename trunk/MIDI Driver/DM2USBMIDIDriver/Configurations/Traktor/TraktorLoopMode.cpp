/*
 *  TraktorLoopMode.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/21/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "TraktorLoopMode.h"
#include "DM2USBMIDI.h"
/*
 *Loop Set/In   - Center
 *Loop Active/Out - Center + Middle
 Deck Loop
 *Loop Lock - (2) sticky
 Loop Select Prev
 Loop Select Next
 *Loop Reloop (8)
 Loop Jump To
* Loop Snap Beat (4) -sticky
 Loop Length Select - next/prev/or wheel
*Loop Length- Hold down XXX and press 1 to 4
 Loop Move-
 Loop Start-
 Loop End-
 /Loop Move/Size Move
 *Loop Move Forward    (3)
 *Loop Move Backward   (7)
 *Loop Length Increase (1)
 *Loop Length Decrease (5)
 
 wheel-
	tempo bend
 TODO:: make snap beat midi in controlled
 */

TraktorLoopMode::TraktorLoopMode(Bank * dm2bank) : TraktorModeInterface(dm2bank)
{	
	setDefaults();
}
void TraktorLoopMode::setDefaults()
{
	myBank->leds.right_1 = ON;
	myBank->leds.right_3 = ON;
	myBank->leds.right_5 = ON;
	myBank->leds.right_7 = ON;
	
	myBank->leds.right_2 = OFF;
	myBank->leds.right_4 = OFF;
	myBank->leds.right_6 = OFF;
	myBank->leds.right_8 = OFF;
	
	myBank->buttons.right_8 = FALSE;
	myBank->buttons.right_1 = FALSE;
	myBank->buttons.right_2 = FALSE;
	myBank->buttons.right_3 = FALSE;
	
	myBank->buttons.right_4 = FALSE;
	myBank->buttons.right_5 = FALSE;
	myBank->buttons.right_6 = FALSE;
	myBank->buttons.right_7 = FALSE;
	
	myBank->leds.left_1 = ON;
	myBank->leds.left_3 = ON;
	myBank->leds.left_5 = ON;
	myBank->leds.left_7 = ON;
	
	myBank->leds.left_2 = OFF;
	myBank->leds.left_4 = OFF;
	myBank->leds.left_6 = OFF;
	myBank->leds.left_8 = OFF;
	
	myBank->buttons.left_8 = FALSE;
	myBank->buttons.left_1 = FALSE;
	myBank->buttons.left_2 = FALSE;
	myBank->buttons.left_3 = FALSE;
	
	myBank->buttons.left_4 = FALSE;
	myBank->buttons.left_5 = FALSE;
	myBank->buttons.left_6 = FALSE;
	myBank->buttons.left_7 = FALSE;
}

/*** LED Buttons ***/
void TraktorLoopMode::buttonRight1Clicked(DM2USBMIDIDriver * dm2){ //Loop length Increase
	currentBank->leds.right_1 = dm2->status.right_1 ? OFF : ON;
	makeBasicNote(dm2->status.right_1,kNOTE_TRAKTOR_DECKB_LOOP_LENGTHINCREASE,dm2);
}

void TraktorLoopMode::buttonRight2Clicked(DM2USBMIDIDriver * dm2){ //Loop lock (sticky)
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
	
	makeBasicNote(currentBank->buttons.right_2,kNOTE_TRAKTOR_DECKB_LOOP_LOCK,dm2);}
void TraktorLoopMode::buttonRight3Clicked(DM2USBMIDIDriver * dm2){ //Loop move forward
	currentBank->leds.right_3 = dm2->status.right_3 ? OFF : ON;
	makeBasicNote(dm2->status.right_3,kNOTE_TRAKTOR_DECKB_LOOP_MOVEFORWARD,dm2);
}
void TraktorLoopMode::buttonRight4Clicked(DM2USBMIDIDriver * dm2){ // snap beat sticky
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
	makeBasicNote(currentBank->buttons.right_4,kNOTE_TRAKTOR_DECKB_LOOP_SNAPBEAT,dm2);
}
void TraktorLoopMode::buttonRight5Clicked(DM2USBMIDIDriver * dm2){ //Loop length decreace
	currentBank->leds.right_5 = dm2->status.right_5 ? OFF : ON;
	makeBasicNote(dm2->status.right_5,kNOTE_TRAKTOR_DECKB_LOOP_LENGTHDECREASE,dm2);
}
void TraktorLoopMode::buttonRight6Clicked(DM2USBMIDIDriver * dm2){ // unused
	//currentBank->leds.right_6 = dm2->status.right_6 ? ON : OFF;
}
void TraktorLoopMode::buttonRight7Clicked(DM2USBMIDIDriver * dm2){ //Loop move backward
	currentBank->leds.right_7 = dm2->status.right_7 ? OFF : ON;
	makeBasicNote(dm2->status.right_7,kNOTE_TRAKTOR_DECKB_LOOP_MOVEBACKWARD,dm2);
}
void TraktorLoopMode::buttonRight8Clicked(DM2USBMIDIDriver * dm2){ //reloop
	currentBank->leds.right_8 = dm2->status.right_8 ? ON : OFF;
	makeBasicNote(dm2->status.right_8,kNOTE_TRAKTOR_DECKB_LOOP_RELOOP,dm2);
}
//left
void TraktorLoopMode::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){//LOOP LENGTH INCREASE
	currentBank->leds.left_1 = dm2->status.left_1 ? OFF : ON;
	makeBasicNote(dm2->status.left_1,kNOTE_TRAKTOR_DECKA_LOOP_LENGTHINCREASE,dm2);
}
void TraktorLoopMode::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){  //Loop lock (sticky) 
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
	
	makeBasicNote(currentBank->buttons.left_2,kNOTE_TRAKTOR_DECKA_LOOP_LOCK,dm2);}
void TraktorLoopMode::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){ //Loop move forward
	currentBank->leds.left_3 = dm2->status.left_3 ? OFF : ON;
	makeBasicNote(dm2->status.left_3,kNOTE_TRAKTOR_DECKA_LOOP_MOVEFORWARD,dm2);
}
void TraktorLoopMode::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){ // Loop snap to beat (Sticky)
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
	
	makeBasicNote(currentBank->buttons.left_4,kNOTE_TRAKTOR_DECKA_LOOP_SNAPBEAT,dm2);
}
void TraktorLoopMode::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){ // Loopp length decrease
	currentBank->leds.left_5 = dm2->status.left_5 ? OFF : ON;
	makeBasicNote(dm2->status.left_5,kNOTE_TRAKTOR_DECKA_LOOP_LENGTHDECREASE,dm2);
}
void TraktorLoopMode::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){ // unused
	//currentBank->leds.left_6 = dm2->status.left_6 ? ON : OFF;
}
void TraktorLoopMode::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){ // Loop move backward
	currentBank->leds.left_7 = dm2->status.left_7 ? OFF : ON;
	makeBasicNote(dm2->status.left_7,kNOTE_TRAKTOR_DECKA_LOOP_MOVEBACKWARD,dm2);
}
void TraktorLoopMode::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){ //reloop
	currentBank->leds.left_8 = dm2->status.left_8 ? ON : OFF;
	makeBasicNote(dm2->status.left_8,kNOTE_TRAKTOR_DECKA_LOOP_RELOOP,dm2);
}

/*** Input ***/
void TraktorLoopMode::buttonReceived(int number, int value)
{
	//Which LED number is the note for?, from 0 to 15
	switch(number)
	{
		case 1: // Lock right
			myBank->buttons.right_2 = (value == 127) ? 1 : 0;
			myBank->leds.right_2 = (value == 127) ? ON : OFF;
			break;
		case 3: // Snap beat right
			myBank->buttons.right_4 = (value == 127) ? 1 : 0;
			myBank->leds.right_4 = (value == 127) ? ON : OFF;
			break;
		case 9: // lock left
			myBank->buttons.left_2 = (value == 127) ? 1 : 0;
			myBank->leds.left_2 = (value == 127) ? ON : OFF;
			break;
		case 11: // snap beat left
			myBank->buttons.left_4 = (value == 127) ? 1 : 0;
			myBank->leds.left_4 = (value == 127) ? ON : OFF;
			break;
	}
}

/**** Rings *****/
void TraktorLoopMode::leftRingSpun(DM2USBMIDIDriver * dm2){
	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	
	if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{				
		dm2->noteBuf[0] = 0xB0; 
		dm2->noteBuf[1] = kCC_TRAKTOR_TEMPOBEND; //CC 25, deck tempo bend
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	//	printf("Sending Loop left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}
void TraktorLoopMode::rightRingSpun(DM2USBMIDIDriver * dm2){
	int accel;
	//range of 62 instead of 127, about half
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	//Note CC 24
	if( accel == 64 || abs(accel - 64) > 1)  //To stop 'needle jumps' that small tap might cause, should only be done on 'transport critical' modes
	{				
		dm2->noteBuf[0] = 0xB1;
		dm2->noteBuf[1] = kCC_TRAKTOR_TEMPOBEND;
		dm2->noteBuf[2] = accel;
	}
	else
		return;
	
	dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
	//	printf("Sending Loop right ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
}

/** Other Buttons ***/
void TraktorLoopMode::leftClicked(DM2USBMIDIDriver * dm2){
	if( dm2->status.middle )
		makeBasicNote(dm2->status.left,kNOTE_TRAKTOR_DECKA_LOOP_ACTIVE,dm2); // LOOP ACTIVATE/OUT
	else
		makeBasicNote(dm2->status.left,kNOTE_TRAKTOR_DECKA_LOOP_SET,dm2); //LOOP SET/IN
}
void TraktorLoopMode::rightClicked(DM2USBMIDIDriver * dm2){
	if( dm2->status.middle )
		makeBasicNote(dm2->status.right,kNOTE_TRAKTOR_DECKB_LOOP_ACTIVE,dm2);// LOOP ACTIVATE/OUT
	else
		makeBasicNote(dm2->status.right,kNOTE_TRAKTOR_DECKB_LOOP_SET,dm2);//LOOP SET/IN
}

/** Loop specific **/	
void TraktorLoopMode::bottomAClicked(DM2USBMIDIDriver * dm2) //Do nothing, we're waiting for 1,2,3,4 to be pressed as well
{
	makeBasicNote(dm2->status.bottom_A,kNOTE_TRAKTOR_DECKA_LOOP_SIZESELECT,dm2);
}
void TraktorLoopMode::bottomBClicked(DM2USBMIDIDriver * dm2)
{
	makeBasicNote(dm2->status.bottom_B,kNOTE_TRAKTOR_DECKB_LOOP_SIZESELECT,dm2);
}

void TraktorLoopMode::bottom1Clicked(DM2USBMIDIDriver * dm2) //Loop length 1
{
	if( dm2->status.bottom_A )
		makeBasicNote(dm2->status.bottom_1,kNOTE_TRAKTOR_DECKA_LOOP_LENGTH1,dm2);
	if( dm2->status.bottom_B )
		makeBasicNote(dm2->status.bottom_1, kNOTE_TRAKTOR_DECKB_LOOP_LENGTH1 ,dm2);
}
void TraktorLoopMode::bottom2Clicked(DM2USBMIDIDriver * dm2) //Loop length 2
{
	if( dm2->status.bottom_A )
		makeBasicNote(dm2->status.bottom_2,kNOTE_TRAKTOR_DECKA_LOOP_LENGTH2,dm2);
	if( dm2->status.bottom_B )
		makeBasicNote(dm2->status.bottom_2,kNOTE_TRAKTOR_DECKB_LOOP_LENGTH2,dm2);
}
void TraktorLoopMode::bottom3Clicked(DM2USBMIDIDriver * dm2) //Loop length 3
{
	if( dm2->status.bottom_A )
		makeBasicNote(dm2->status.bottom_3,kNOTE_TRAKTOR_DECKA_LOOP_LENGTH3,dm2);
	if( dm2->status.bottom_B )
		makeBasicNote(dm2->status.bottom_3,kNOTE_TRAKTOR_DECKB_LOOP_LENGTH3,dm2);
}
void TraktorLoopMode::bottom4Clicked(DM2USBMIDIDriver * dm2) //Loop length 4
{
	if( dm2->status.bottom_A )
		makeBasicNote(dm2->status.bottom_4,kNOTE_TRAKTOR_DECKA_LOOP_LENGTH4,dm2);
	if( dm2->status.bottom_B )
		makeBasicNote(dm2->status.bottom_1,kNOTE_TRAKTOR_DECKB_LOOP_LENGTH4,dm2);
}