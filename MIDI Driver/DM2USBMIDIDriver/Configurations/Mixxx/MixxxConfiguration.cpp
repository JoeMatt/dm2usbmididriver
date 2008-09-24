/*
 *  MixxxConfiguration.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/5/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */


//TODO: Test left, copy to right
#include "MixxxConfiguration.h"
#include "DM2USBMIDI.h"
#include "DM2 Structs.h"

MixxxConfiguration::MixxxConfiguration() : DM2Configuration(), leftRingCCValue(kNOTE_MIXXX_LINUX_CC_DECKA), rightRingCCValue(kNOTE_MIXXX_LINUX_CC_DECKB),
middleLeftRingMoved(FALSE), middleRightRingMoved(FALSE), led8LeftRingMoved(FALSE), led8RightRingMoved(FALSE), led7LeftRingMoved(FALSE), led7RightRingMoved(FALSE),
led6LeftRingMoved(FALSE), led6RightRingMoved(FALSE), led3LeftRingMoved(FALSE), led3RightRingMoved(FALSE), led2LeftRingMoved(FALSE), led2RightRingMoved(FALSE), jogmidival(64)
{	
	/* Delete unused Bank structs */
	delete bank2;
	delete bank3;
	delete bank4;
	
	/* TODO: Some of the following can probably be deleted. Non toggle buttons, maybe leds as well */
	bank1->leds.right_1 = OFF;
	bank1->leds.right_2 = OFF;
	bank1->leds.right_3 = OFF;
	bank1->leds.right_4 = OFF;
	bank1->leds.right_5 = OFF;
	bank1->leds.right_6 = OFF;
	bank1->leds.right_7 = OFF;
	bank1->leds.right_8 = OFF;
 	
	bank1->buttons.right_1 = FALSE;
	bank1->buttons.right_2 = FALSE;
	bank1->buttons.right_3 = FALSE;	
	bank1->buttons.right_4 = FALSE;
	bank1->buttons.right_5 = FALSE;
	bank1->buttons.right_6 = FALSE;
	bank1->buttons.right_7 = FALSE;
	bank1->buttons.right_8 = FALSE;
	
	bank1->leds.left_1 = OFF;
	bank1->leds.left_2 = OFF;
	bank1->leds.left_3 = OFF;
	bank1->leds.left_4 = OFF;
	bank1->leds.left_5 = OFF;
	bank1->leds.left_6 = OFF;
	bank1->leds.left_7 = OFF;
	bank1->leds.left_8 = OFF;
	
	bank1->buttons.left_1 = FALSE;
	bank1->buttons.left_2 = FALSE;
	bank1->buttons.left_3 = FALSE;	
	bank1->buttons.left_4 = FALSE;
	bank1->buttons.left_5 = FALSE;
	bank1->buttons.left_6 = FALSE;
	bank1->buttons.left_7 = FALSE;
	bank1->buttons.left_8 = FALSE;

}

#pragma mark Rings
void  MixxxConfiguration::leftRingSpun(DM2USBMIDIDriver * dm2)
{
	
	
	//range of 62 instead of 127, about half
	int accel;
	accel = dm2->status.accel_left;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	
	//if( (accel - currentBank->bumpIgnore) <= 0 && accel != 64)
	//	return;
	
	 
	
	/*
		Middle - Set turned toggle to TRUE. Send notes for playlist scroll
	 */

	struct dm_status * status = &dm2->status;
	if(status->middle)
	{
		middleLeftRingMoved = TRUE;
		/* Send NOTE instead */
		if(accel > 64)
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK_MOVE_UP, dm2);
		else if(accel < 64)
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK_MOVE_DOWN, dm2);

		return;
	}
	else if( status->left_1 ){
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON1;
	}
	else if( status->left_2 ){
		led2LeftRingMoved = TRUE;
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON2;
	}	
	else if( status->left_3 ){
		led3LeftRingMoved = TRUE;
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON3;
	}	
	else if( status->left_4 ){
		//Seems un implimented in .xml config
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON4;
	}	
	else if( status->left_6 ){
		led6LeftRingMoved = TRUE;
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON6;
	}	
	else if( status->left_7 ){
		led7LeftRingMoved = TRUE;
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON7;
	}	
	else if( status->left_8 ){
		led8LeftRingMoved = TRUE;
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON8;
	}
	else
	{
		leftRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKA;
	}
	

	
	/** LINUX CODE **/
	int diff;
	diff = (uint8_t)status->accel_left;
	printf("Stage1 %i\n",diff);
	if (diff & 0x80) diff-=256;
	printf("Stage2 %i\n",diff);
	diff = -diff;
	printf("Stage3 %i\n",diff);
	
	// Jog wheel mode
	if (TRUE) {
		diff += 64;
		if (diff < 0)   diff = 0;
		if (diff > 127) diff = 127;
		if (diff != jogmidival)
		{
			dm2->noteBuf[0] = 0xB0;
			dm2->noteBuf[1] = leftRingCCValue;
			dm2->noteBuf[2] = diff;
			dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
			printf("Sending left ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
		}
		jogmidival = diff;
	}
	/** END LINUX CODE **/
}

void MixxxConfiguration::rightRingSpun(DM2USBMIDIDriver * dm2)
{
	//range of 62 instead of 127, about half
	int accel;
	accel = dm2->status.accel_right;
	if(accel == 0)
		accel = 64;
	else
		accel = accel > 0 ? (int)(63 - (accel * .5)) : (int)(accel * -.48 + 66);
	
	//if( (accel - currentBank->bumpIgnore) <= 0 && accel != 64)
	//	return;
	
	
	
	/*
	 Middle - Set turned toggle to TRUE. Send notes for playlist scroll
	 */
	
	struct dm_status * status = &dm2->status;
	if(status->middle)
	{
		middleRightRingMoved = TRUE;
		/* Send NOTE instead */
		if(accel > 64)
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK_MOVE_UP, dm2);
		else if(accel < 64)
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK_MOVE_DOWN, dm2);
		
		return;
	}
	else if( status->right_1 ){
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON1;
	}
	else if( status->right_2 ){
		led2RightRingMoved = TRUE;
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON2;
	}	
	else if( status->right_3 ){
		led3RightRingMoved = TRUE;
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON3;
	}	
	else if( status->right_4 ){
		//Seems un implimented in .xml config
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON4;
	}	
	else if( status->right_6 ){
		led6RightRingMoved = TRUE;
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON6;
	}	
	else if( status->right_7 ){
		led7RightRingMoved = TRUE;
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON7;
	}	
	else if( status->right_8 ){
		led8RightRingMoved = TRUE;
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON8;
	}
	else
	{
		rightRingCCValue = kNOTE_MIXXX_LINUX_CC_DECKB;
	}
	
	
	
	/** LINUX CODE **/
	int diff;
	diff = (uint8_t)status->accel_right;
	printf("Stage1 %i\n",diff);
	if (diff & 0x80) diff-=256;
	printf("Stage2 %i\n",diff);
	diff = -diff;
	printf("Stage3 %i\n",diff);
	
	// Jog wheel mode
	if (TRUE) {
		diff += 64;
		if (diff < 0)   diff = 0;
		if (diff > 127) diff = 127;
		if (diff != jogmidival)
		{
			dm2->noteBuf[0] = 0xB0;
			dm2->noteBuf[1] = rightRingCCValue;
			dm2->noteBuf[2] = diff;
			dm2->pkt = MIDIPacketListAdd(dm2->pktlist, sizeof(dm2->pbuf), dm2->pkt, dm2->timeStamp, 3, dm2->noteBuf );
#if DEBUG
			printf("Sending right ring: %x %i %i\n",dm2->noteBuf[0],dm2->noteBuf[1],dm2->noteBuf[2]);
#endif
		}
		jogmidival = diff;
	}
	/** END LINUX CODE **/
}

/* Sliders and Joystick */
#pragma mark Slider & Joystick
void MixxxConfiguration::sliderMoved(DM2USBMIDIDriver * dm2)
{	 
	makeCCNote(0, kNOTE_MIXXX_LINUX_CC_SLIDER, dm2->calcSliderValue(), dm2);
}
void MixxxConfiguration::joystickXMoved(DM2USBMIDIDriver * dm2)
{
	//Because the X axis is reversed to what you'd\_/ expect	
	makeCCNote(0, kNOTE_MIXXX_LINUX_CC_JOYSTICKX, 127 - dm2->calcJoystickXValue(), dm2);

}
void MixxxConfiguration::joystickYMoved(DM2USBMIDIDriver * dm2)
{
	makeCCNote(0, kNOTE_MIXXX_LINUX_CC_JOYSTICKY, dm2->calcJoystickYValue(), dm2);
}
/*** LED Buttons ***/
#pragma mark -
#pragma mark LED Buttons
/* Notes: Most of the LED buttons act as a Toggle, as in
	they should only send a note on button up, if the ring
	wasn't moved after button down
 */

#pragma mark Right
void MixxxConfiguration::buttonRight1Clicked(DM2USBMIDIDriver * dm2){
	//Unused, Balance value on wheel only
	clearLED();
	setLED(	&(bank1->leds.right_1) , dm2->status.right_1);
}
void MixxxConfiguration::buttonRight2Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.right_2) , dm2->status.right_2);
	
	if( !dm2->status.right_2)
	{
		if(led2RightRingMoved)
			led2RightRingMoved = FALSE;
		else
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKB_BUTTON2, dm2);
	}
}
void MixxxConfiguration::buttonRight3Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.right_3) , dm2->status.right_3);
	
	if( !dm2->status.right_3)
	{
		if(led3RightRingMoved)
			led3RightRingMoved = FALSE;
		else
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKB_BUTTON3, dm2);
	}
}
void MixxxConfiguration::buttonRight4Clicked(DM2USBMIDIDriver * dm2){
	/* Reverse */
	/* NOTE: The linux version doesn't treat the LED as a toggle, i think it should since it stays 
	 in reverse after press until repress. Either change the LED behaviour or make it so you have to hhold
	 the reverse button */
	
	clearLED();
	setLED(	&(bank1->leds.right_4) , dm2->status.right_4);	
	makeBasicNote(dm2->status.right_4, kNOTE_MIXXX_LINUX_DECKB_BUTTON4, dm2);
}
void MixxxConfiguration::buttonRight5Clicked(DM2USBMIDIDriver * dm2){
	/* Multiplexed reset controls
	 If holding a button, and we clicked button.*_5, reset that control
	 */
	struct dm_status * status = &dm2->status;
	
	if(status->right_8)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON8, 64, dm2);
	if(status->right_7)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON7, 64, dm2);
	if(status->right_6)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON6, 64, dm2);
	if(status->right_3)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON3, 64, dm2);
	if(status->right_2)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON2, 64, dm2);
	if(status->right_1)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON1, 64, dm2);
}
void MixxxConfiguration::buttonRight6Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.right_6) , dm2->status.right_6);
	
	//if ring hasn't moved and button is now up 
	if(!dm2->status.right_6) 
	{
		if(led6RightRingMoved)
			led6RightRingMoved = FALSE;
		else
		{	
			toggleButton(&bank1->buttons.right_6);
			makeBasicNote(bank1->buttons.right_6, kNOTE_MIXXX_LINUX_DECKB_BUTTON6, dm2);
		}
	}
}
void MixxxConfiguration::buttonRight7Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.right_7) , dm2->status.right_7);	
	//if ring hasn't moved and button is now up 
	if(!dm2->status.right_7) 
	{
		if(led7RightRingMoved)
			led7RightRingMoved = FALSE;
		else
		{	toggleButton(&bank1->buttons.right_7);
			makeBasicNote(bank1->buttons.right_7, kNOTE_MIXXX_LINUX_DECKB_BUTTON7, dm2);
		}
	}
}
void MixxxConfiguration::buttonRight8Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.right_8) , dm2->status.right_8);
	
	//if ring hasn't moved and button is now up 
	if(!dm2->status.right_8) 
	{
		if(led8RightRingMoved)
			led8RightRingMoved = FALSE;
		else
		{	toggleButton(&bank1->buttons.right_8);
			makeBasicNote(bank1->buttons.right_8, kNOTE_MIXXX_LINUX_DECKB_BUTTON8, dm2);
		}
	}
}

#pragma mark Left
void MixxxConfiguration::buttonLeft1Clicked(DM2USBMIDIDriver * dm2){
	//Unused, Balance value on wheel only
	clearLED();
	setLED(	&(bank1->leds.left_1) , dm2->status.left_1);
}
void MixxxConfiguration::buttonLeft2Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.left_2) , dm2->status.left_2);

	if( !dm2->status.left_2)
	{
		if(led2LeftRingMoved)
			led2LeftRingMoved = FALSE;
		else
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKA_BUTTON2, dm2);
	}
}
void MixxxConfiguration::buttonLeft3Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.left_3) , dm2->status.left_3);
	
	if( !dm2->status.left_3)
	{
		if(led3LeftRingMoved)
			led3LeftRingMoved = FALSE;
		else
			makeBasicNote(TRUE, kNOTE_MIXXX_LINUX_DECKA_BUTTON3, dm2);
	}

}

void MixxxConfiguration::buttonLeft4Clicked(DM2USBMIDIDriver * dm2){
	/* Reverse */
	/* NOTE: The linux version doesn't treat the LED as a toggle, i think it should since it stays 
		in reverse after press until repress. Either change the LED behaviour or make it so you have to hhold
	 the reverse button */
	
	clearLED();
	setLED(	&(bank1->leds.left_4) , dm2->status.left_4);	
	makeBasicNote(dm2->status.left_4, kNOTE_MIXXX_LINUX_DECKA_BUTTON4, dm2);
}

void MixxxConfiguration::buttonLeft5Clicked(DM2USBMIDIDriver * dm2){

	/* Multiplexed reset controls
	 If holding a button, and we clicked button.*_5, reset that control
	 */
	 struct dm_status * status = &dm2->status;

	if(status->left_8)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON8, 64, dm2);
	if(status->left_7)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON7, 64, dm2);
	if(status->left_6)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON6, 64, dm2);
	if(status->left_3)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON3, 64, dm2);
	if(status->left_2)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON2, 64, dm2);
	if(status->left_1)
		makeCCNote(0, kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON1, 64, dm2);
}

void MixxxConfiguration::buttonLeft6Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.left_6) , dm2->status.left_6);

	//if ring hasn't moved and button is now up 
	if(!dm2->status.left_6) 
	{
		if(led6LeftRingMoved)
			led6LeftRingMoved = FALSE;
		else
		{	
		toggleButton(&bank1->buttons.left_6);
		makeBasicNote(bank1->buttons.left_6, kNOTE_MIXXX_LINUX_DECKA_BUTTON6, dm2);
		}
	}
}

void MixxxConfiguration::buttonLeft7Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.left_7) , dm2->status.left_7);	
	//if ring hasn't moved and button is now up 
	if(!dm2->status.left_7) 
	{
		if(led7LeftRingMoved)
			led7LeftRingMoved = FALSE;
		else
		{	toggleButton(&bank1->buttons.left_7);
			makeBasicNote(bank1->buttons.left_7, kNOTE_MIXXX_LINUX_DECKA_BUTTON7, dm2);
		}
	}
}

void MixxxConfiguration::buttonLeft8Clicked(DM2USBMIDIDriver * dm2){
	clearLED();
	setLED(	&(bank1->leds.left_8) , dm2->status.left_8);

	//if ring hasn't moved and button is now up 
	if(!dm2->status.left_8) 
	{
		if(led8LeftRingMoved)
			led8LeftRingMoved = FALSE;
		else
		{	toggleButton(&bank1->buttons.left_8);
			makeBasicNote(bank1->buttons.left_8, kNOTE_MIXXX_LINUX_DECKA_BUTTON8, dm2);
		}
	}
}


/*** Top Buttons ***/
#pragma mark Top Buttons
void MixxxConfiguration::stopClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.stop,kNOTE_MIXXX_LINUX_STOPBUTTON,dm2);}

void MixxxConfiguration::playClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.play,kNOTE_MIXXX_LINUX_PLAYBUTTON,dm2);}

void MixxxConfiguration::recClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.rec,kNOTE_MIXXX_LINUX_RECBUTTON,dm2);}

void MixxxConfiguration::top3Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_3,kNOTE_MIXXX_LINUX_TOP3BUTTON,dm2);}

void MixxxConfiguration::top2Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_2,kNOTE_MIXXX_LINUX_TOP2BUTTON,dm2);}

void MixxxConfiguration::top1Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.top_1,kNOTE_MIXXX_LINUX_TOP1BUTTON,dm2);}

/*** Bottom Buttons ****/
#pragma mark Bottom Buttons
void MixxxConfiguration::bottom1Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_1,kNOTE_MIXXX_LINUX_BOTTOM1BUTTON,dm2);}


void MixxxConfiguration::bottom2Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_2,kNOTE_MIXXX_LINUX_BOTTOM2BUTTON,dm2);}


void MixxxConfiguration::bottom3Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_3,kNOTE_MIXXX_LINUX_BOTTOM3BUTTON,dm2);}

void MixxxConfiguration::bottom4Clicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_4,kNOTE_MIXXX_LINUX_BOTTOM4BUTTON,dm2);}


void MixxxConfiguration::middleClicked(DM2USBMIDIDriver * dm2)
{	
	//On button up, check if rings were moved, send notes
	if(!dm2->status.middle)
	{
		if(middleLeftRingMoved)
			makeBasicNote(OFF,kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK,dm2);
		
		if(middleRightRingMoved)
			makeBasicNote(OFF,kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK,dm2);
		
		middleLeftRingMoved = middleRightRingMoved = FALSE;
	}
}

void MixxxConfiguration::bottomAClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_A,kNOTE_MIXXX_LINUX_BOTTOMABUTTON,dm2);}

void MixxxConfiguration::bottomBClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.bottom_B,kNOTE_MIXXX_LINUX_BOTTOMBBUTTON,dm2);}

void MixxxConfiguration::leftClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.left,kNOTE_MIXXX_LINUX_LEFTCENTERBUTTON,dm2);}

void MixxxConfiguration::rightClicked(DM2USBMIDIDriver * dm2)
{	makeBasicNote(dm2->status.right,kNOTE_MIXXX_LINUX_RIGHTCENTERBUTTON,dm2);}

/***** Input ****/
#pragma mark Input
void MixxxConfiguration::buttonReceived(int number, Bank * bank, int value, bool onMessage){

		/* Note: The linux setup is for 64-71, then 80 - 87 so 80-87 will be fucked up so i hacked the DM2 parent caller for now 
		 since Mixxx is the only case that uses over 63 right now*/
	//TODO: Change midi in code to send absolute values instead of mod16, add mod16 as a default case to overload
	
	//For now nothing really needs to be overloaded until the above is dealt with
	DM2Configuration::buttonReceived( number, bank,  value,  onMessage);
	
	/*
	 // LED buttons activated by these notes:
	 .led0notes =  { 64, 65, 66, 67, 68, 69, 70, 71 },
	 .led1notes =  { 80, 81, 82, 83, 84, 85, 86, 87 },
	 .led0idle = 88, .led1idle = 89
	 */

}
