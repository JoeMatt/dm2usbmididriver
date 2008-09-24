/*
 *  DM2 Structs.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/1/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */
#ifndef __DM2_Structs_h__
#define __DM2_Structs_h__

#include <CoreMIDI/CoreMIDI.h>

/*** START TRAKTOR ***/
	/*** START DECK B ***/
	/* Mix */									/* 0 + (n) */
#define kNOTE_TRAKTOR_DECKB_MIX_PLAY			0	/* Button 1 (0) */   /* Inputable */
#define kNOTE_TRAKTOR_DECKB_MIX_CUEPLAY			1	/* Button 2 (1) */
#define kNOTE_TRAKTOR_DECKB_MIX_CUEPAUSE		2	/* Button 3 (2) */
#define kNOTE_TRAKTOR_DECKB_MIX_CUESET			3	/* Button 4 (3) */
#define kNOTE_TRAKTOR_DECKB_MIX_SYNC			4	/* Button 5 (4) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_MIX_KEYLOCK			5	/* Button 6 (5) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_MIX_CUE_PREVIOUS	6	/* Button 7 (6) */
#define kNOTE_TRAKTOR_DECKB_MIX_CUE_NEXT		7	/* Button 8 (7) */
//#define kNOTE_TRAKTOR_DECKB_MIX_BPMTAP			6	/* NOTHING */
#define kNOTE_TRAKTOR_DECKB_MIX_CUE				127 /* Bottom B */
		
	
	/* Loop */									/* 16 + (n) */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTHINCREASE	16	/* Button 1 (0) */
#define kNOTE_TRAKTOR_DECKB_LOOP_LOCK			17	/* Button 2 (1) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_LOOP_MOVEFORWARD	18	/* Button 3 (2) */
#define kNOTE_TRAKTOR_DECKB_LOOP_SNAPBEAT		19	/* Button 4 (3) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTHDECREASE	20	/* Button 5 (4) */
													/* Button 6 (5) */
#define kNOTE_TRAKTOR_DECKB_LOOP_MOVEBACKWARD	21	/* Button 7 (6) */
#define kNOTE_TRAKTOR_DECKB_LOOP_RELOOP			23	/* Button 8 (7) */
#define kNOTE_TRAKTOR_DECKB_LOOP_SET			125	/* Center */
#define kNOTE_TRAKTOR_DECKB_LOOP_ACTIVE			124 /* Center + Middle */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTH1		115 /* B + 1 */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTH2		117 /* B + 2 */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTH3		119 /* B + 3 */
#define kNOTE_TRAKTOR_DECKB_LOOP_LENGTH4		121 /* B + 4 */
#define kNOTE_TRAKTOR_DECKA_LOOP_SIZESELECT		60 /* A */
#define kNOTE_TRAKTOR_DECKB_LOOP_SIZESELECT		61 /* B */

	/* FX */									/* 32 + (n) */
#define kNOTE_TRAKTOR_DECKB_FX_KNOB1RESET		98	/* DblClick Button 8 */
#define kNOTE_TRAKTOR_DECKB_FX_KNOB2RESET		99	/* DblClick Button 1 */
#define kNOTE_TRAKTOR_DECKB_FX_KNOB3RESET		100 /* DblClick Button 2 */
#define kNOTE_TRAKTOR_DECKB_FX_KNOB4RESET		101	/* DblClick Button 3 */
													/* Button 1 (0) */
													/* Button 2 (1) */
													/* Button 3 (2) */
#define kNOTE_TRAKTOR_DECKB_FX_BUTTON4			35	/* Button 4 (3) */
#define kNOTE_TRAKTOR_DECKB_FX_BUTTON3			36	/* Button 5 (4) */
#define kNOTE_TRAKTOR_DECKB_FX_BUTTON2			37	/* Button 6 (5) */
#define kNOTE_TRAKTOR_DECKB_FX_BUTTON1			38	/* Button 7 (6) */
													/* Button 8 (7) */
#define kNOTE_TRAKTOR_DECKB_FX_SELECTNEXT		85	/* Center */
#define kNOTE_TRAKTOR_DECKB_FX_CUE				87	/* B */
	/* EQ */									/* 48 + (n) */
													/* Button 1 (0) */
#define kNOTE_TRAKTOR_DECKB_EQ_HIGHKILL			49	/* Button 2 (1) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_EQ_MIDKILL			50	/* Button 3 (2) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKB_EQ_LOWKILL			51	/* Button 4 (3) */	/* Inputable */
													/* Button 5 (4) */
													/* Button 6 (5) */
													/* Button 7 (6) */
													/* Button 8 (7) */
#define kNOTE_TRAKTOR_DECKB_EQ_HIGHRESET		92 /* DblClick Button 8 */
#define kNOTE_TRAKTOR_DECKB_EQ_MIDRESET			91 /* DblClick Button 7 */
#define kNOTE_TRAKTOR_DECKB_EQ_LOWRESET			90 /* DblClick Button 6 */
#define kNOTE_TRAKTOR_DECKB_EQ_BALANCERESET		88 /* DblClick Button 1 */
#define kNOTE_TRAKTOR_DECKB_EQ_VOLUMERESET		89 /* DblClick Button 5 */
	/*** END DECK B ***/
	/*** START DECK A ***/
	/* Mix */									/* 0 + (n) */
#define kNOTE_TRAKTOR_DECKA_MIX_PLAY			8	/* Button 1 (8) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKA_MIX_CUEPLAY			9	/* Button 2 (9) */
#define kNOTE_TRAKTOR_DECKA_MIX_CUEPAUSE		10	/* Button 3 (10) */
#define kNOTE_TRAKTOR_DECKA_MIX_CUESET			11	/* Button 4 (11) */
#define kNOTE_TRAKTOR_DECKA_MIX_SYNC			12	/* Button 5 (12) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKA_MIX_KEYLOCK			13	/* Button 6 (13) */	/* Inputable */
#define kNOTE_TRAKTOR_DECKA_MIX_CUE_PREVIOUS	14  /* Button 7 (14) */
#define kNOTE_TRAKTOR_DECKA_MIX_CUE_NEXT		15  /* Button 8 (15) */
//#define kNOTE_TRAKTOR_DECKA_MIX_BPMTAP			7	/* NOTHING  */
#define kNOTE_TRAKTOR_DECKA_MIX_CUE				126 /*Bottom A */

	/* Loop */									/* 16 + (n) */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTHINCREASE	24	/* Button 1 (8)  */
#define kNOTE_TRAKTOR_DECKA_LOOP_LOCK			25	/* Button 2 (9)  */
#define kNOTE_TRAKTOR_DECKA_LOOP_MOVEFORWARD	26	/* Button 3 (10) */
#define kNOTE_TRAKTOR_DECKA_LOOP_SNAPBEAT		27	/* Button 4 (11) */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTHDECREASE	28	/* Button 5 (12) */
													/* Button 6 (13) */
#define kNOTE_TRAKTOR_DECKA_LOOP_MOVEBACKWARD	30	/* Button 7 (14) */
#define kNOTE_TRAKTOR_DECKA_LOOP_RELOOP			31	/* Button 8 (15) */
#define kNOTE_TRAKTOR_DECKA_LOOP_SET			123	/* Center */
#define kNOTE_TRAKTOR_DECKA_LOOP_ACTIVE			122	/* Center + Middle */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTH1		114	/* A + 1 */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTH2		116	/* A + 2 */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTH3		118	/* A + 3 */
#define kNOTE_TRAKTOR_DECKA_LOOP_LENGTH4		120	/* A + 4 */
	/* FX */									/* 32 + (n) */
#define kNOTE_TRAKTOR_DECKA_FX_KNOB1RESET		102	/* DblClick Button 8 */
#define kNOTE_TRAKTOR_DECKA_FX_KNOB2RESET		103	/* DblClick Button 1 */
#define kNOTE_TRAKTOR_DECKA_FX_KNOB3RESET		104	/* DblClick Button 2 */
#define kNOTE_TRAKTOR_DECKA_FX_KNOB4RESET		105	/* DblClick Button 3 */
													/* Button 1 (8) */
													/* Button 2 (9) */
													/* Button 3 (10) */
#define kNOTE_TRAKTOR_DECKA_FX_BUTTON4			43	/* Button 4 (11) */
#define kNOTE_TRAKTOR_DECKA_FX_BUTTON3			44	/* Button 5 (12) */
#define kNOTE_TRAKTOR_DECKA_FX_BUTTON2			45	/* Button 6 (13) */
#define kNOTE_TRAKTOR_DECKA_FX_BUTTON1			46	/* Button 7 (14) */
													/* Button 8 (15) */
#define kNOTE_TRAKTOR_DECKA_FX_SELECTNEXT		84	/* Center */
#define kNOTE_TRAKTOR_DECKA_FX_CUE				86	/* A */
	/* EQ */									/* 48 + (n) */
													/* Button 1 (8) */
#define kNOTE_TRAKTOR_DECKA_EQ_HIGHKILL			57	/* Button 2 (9) */
#define kNOTE_TRAKTOR_DECKA_EQ_MIDKILL			58	/* Button 3 (10)*/
#define kNOTE_TRAKTOR_DECKA_EQ_LOWKILL			59	/* Button 4 (11)*/
													/* Button 5 (12) */
													/* Button 6 (13) */
													/* Button 7 (14) */
													/* Button 8 (15) */
#define kNOTE_TRAKTOR_DECKA_EQ_HIGHRESET		97	/* DblClick Button 8 */
#define kNOTE_TRAKTOR_DECKA_EQ_MIDRESET			96	/* DblClick Button 7 */
#define kNOTE_TRAKTOR_DECKA_EQ_LOWRESET			95	/* DblClick Button 6 */
#define kNOTE_TRAKTOR_DECKA_EQ_BALANCERESET		93	/* DblClick Button 1 */
#define kNOTE_TRAKTOR_DECKA_EQ_VOLUMERESET		94	/* DblClick Button 5 */
	/*** END DECK A ***/
	/*** Global CC Values ***/
#define kCC_TRAKTOR_SCRATCH						22
#define kCC_TRAKTOR_EQ_KNOB						23
#define kCC_TRAKTOR_FX_KNOB						24
#define kCC_TRAKTOR_TEMPOBEND					25
#define kCC_TRAKTOR_DECKWIND					26
#define kCC_TRAKTOR_PITCH						27
	/*** Global Others ***/
#define kNOTE_TRAKTOR_GLOBAL_CHANGETO_MIX		52	/* 1 */
#define kNOTE_TRAKTOR_GLOBAL_CHANGETO_LOOP		53	/* 2 */
#define kNOTE_TRAKTOR_GLOBAL_CHANGETO_FX		54	/* 3 */
#define kNOTE_TRAKTOR_GLOBAL_CHANGETO_EQ		55	/* 4 */
/*** END TRAKTOR ***/

#pragma mark Basic Config
#define kNOTE_DECKB_ACTIVATESCRATCH				70

#define kNOTE_BASIC_STOPBUTTON					64
#define kNOTE_BASIC_PLAYBUTTON					65
#define kNOTE_BASIC_RECBUTTON					66
#define kNOTE_BASIC_TOP3BUTTON					67
#define kNOTE_BASIC_TOP2BUTTON					68
#define kNOTE_BASIC_TOP1BUTTON					69
#define kNOTE_BASIC_MIDDLEBUTTON				72
#define kNOTE_BASIC_BOTTOMABUTTON				74
#define kNOTE_BASIC_BOTTOMBBUTTON				73
#define kNOTE_BASIC_LEFTCENTERBUTTON			71
#define kNOTE_BASIC_RIGHTCENTERBUTTON			70
#define kNOTE_BASIC_LEFTRINGFORWARD				76
#define kNOTE_BASIC_LEFTRINGBACKWARD			75
#define kNOTE_BASIC_RIGHTRINGFORWARD			78
#define kNOTE_BASIC_RIGHTRINGBACKWARD			77
#define kNOTE_BASIC_CC_SLIDER					8
#define kNOTE_BASIC_CC_JOYSTICKX				12
#define kNOTE_BASIC_CC_JOYSTICKY				13

/* Bottom 1-4 Buttons */
#pragma mark Bottom Buttons
#define kNOTE_BASIC_BOTTOM1BUTTON					79
#define kNOTE_BASIC_BOTTOM2BUTTON					80
#define kNOTE_BASIC_BOTTOM3BUTTON					81
#define kNOTE_BASIC_BOTTOM4BUTTON					82


/* Mixxx */
#pragma mark Mixxx
#define kNOTE_MIXXX_LINUX_STOPBUTTON	48
#define kNOTE_MIXXX_LINUX_PLAYBUTTON	49
#define kNOTE_MIXXX_LINUX_RECBUTTON		50
#define kNOTE_MIXXX_LINUX_TOP3BUTTON	51
#define kNOTE_MIXXX_LINUX_TOP2BUTTON	52
#define kNOTE_MIXXX_LINUX_TOP1BUTTON	53
#define kNOTE_MIXXX_LINUX_RIGHTCENTERBUTTON 54
#define kNOTE_MIXXX_LINUX_LEFTCENTERBUTTON 55
#define kNOTE_MIXXX_LINUX_BOTTOMBBUTTON 58
#define kNOTE_MIXXX_LINUX_BOTTOMABUTTON 59
#define kNOTE_MIXXX_LINUX_BOTTOM4BUTTON 60
#define kNOTE_MIXXX_LINUX_BOTTOM3BUTTON 61
#define kNOTE_MIXXX_LINUX_BOTTOM2BUTTON 62
#define kNOTE_MIXXX_LINUX_BOTTOM1BUTTON 63

#define kNOTE_MIXXX_LINUX_DECKA_BUTTON8 16
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON7 17
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON6 18
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON5 0 /* UNUSED */
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON4 20
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON3 21 //rate down small
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON2 22 //rate up small
#define kNOTE_MIXXX_LINUX_DECKA_BUTTON1 0 /* Unused */

#define kNOTE_MIXXX_LINUX_DECKB_BUTTON8 32
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON7 33
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON6 34
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON5 0 /* UNUSED */
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON4 36
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON3 37
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON2 38
#define kNOTE_MIXXX_LINUX_DECKB_BUTTON1 0 /* Unused */

/* CC's Holding an LED button and spinning the wheel will send the CC value of the following */
	//NO BUTTONS BEING HELD
#define kNOTE_MIXXX_LINUX_CC_DECKA 1
#define kNOTE_MIXXX_LINUX_CC_DECKB 3
#define kNOTE_MIXXX_LINUX_CC_SLIDER 2
#define kNOTE_MIXXX_LINUX_CC_JOYSTICKX 4
#define kNOTE_MIXXX_LINUX_CC_JOYSTICKY 5

#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON8 16
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON7 17
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON6 18
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON5 0 /* UNUSED */
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON4 20
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON3 21
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON2 22
#define kNOTE_MIXXX_LINUX_CC_DECKA_BUTTON1 23

#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON8 32
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON7 33
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON6 34
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON5 0 /* UNUSED */
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON4 36
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON3 37
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON2 38
#define kNOTE_MIXXX_LINUX_CC_DECKB_BUTTON1 39

#define kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK_MOVE_UP 65
#define kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK_MOVE_UP 65
#define kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK_MOVE_DOWN 66
#define kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK_MOVE_DOWN 66
#define kNOTE_MIXXX_LINUX_DECKA_CHANGETRACK 67
#define kNOTE_MIXXX_LINUX_DECKB_CHANGETRACK 68

/* End Mix */


struct MidiMessage
{
	unsigned type	 :4;
	unsigned channel :4;
	unsigned char number;
	unsigned char value;
};

struct Button
{
	struct MidiMessage midiMessge;	
};


struct button_status
{
	bool right_8 ;
	bool right_7 ;
	bool right_6 ;
	bool right_5 ;
	bool right_4 ;
	bool right_3 ;
	bool right_2 ;
	bool right_1 ;
	
	bool left_8 ;
	bool left_7 ;
	bool left_6 ;
	bool left_5 ;
	bool left_4 ;
	bool left_3 ;
	bool left_2 ;
	bool left_1 ;
};

struct led_status
{
	bool right_8 ;
	bool right_7 ;
	bool right_6 ;
	bool right_5 ;
	bool right_4 ;
	bool right_3 ;
	bool right_2 ;
	bool right_1 ;
	
	bool left_8 ;
	bool left_7 ;
	bool left_6 ;
	bool left_5 ;
	bool left_4 ;
	bool left_3 ;
	bool left_2 ;
	bool left_1 ;
};

struct Bank{
	int bankNumber;

	struct button_status buttons;
	struct led_status leds;
	
	/* Settings */
	int		bumpIgnore;
	bool	sticky_buttons;
	bool	invertLeds;
	bool	isMidiClock;
	bool	iControlLeds;
	bool	midiInControlsLeds;
};

struct dm_status
{	
	//10 bytes
	signed accel_left  :8;
	signed accel_right :8;
	//On PPC the bytes are actually bit swapped. I don't understand it, this isn't what endianess means, but it is. So I need to fix it for them.
#if __BIG_ENDIAN__ 
	//PPC
	unsigned right_1 :1;
	unsigned right_2 :1;
	unsigned right_3 :1;
	unsigned right_4 :1;
	unsigned right_5 :1;
	unsigned right_6 :1;
	unsigned right_7 :1;
	unsigned right_8 :1;
	
	unsigned left_1 :1;
	unsigned left_2 :1;
	unsigned left_3 :1;
	unsigned left_4 :1;
	unsigned left_5 :1;
	unsigned left_6 :1;
	unsigned left_7 :1;
	unsigned left_8 :1;
	
	unsigned left :1;
	unsigned right :1;
	unsigned top_1 :1;
	unsigned top_2 :1;
	unsigned top_3 :1;
	unsigned rec :1;
	unsigned play :1;
	unsigned stop :1;
	
	unsigned bottom_1 :1;	
	unsigned bottom_2 :1;
	unsigned bottom_3 :1;
	unsigned bottom_4 :1;
	unsigned bottom_A :1;
	unsigned bottom_B :1;
	unsigned middle :1;
	unsigned field1 :1;
#else
	//Intel x86
	unsigned right_8 :1;
	unsigned right_7 :1;
	unsigned right_6 :1;
	unsigned right_5 :1;
	unsigned right_4 :1;
	unsigned right_3 :1;
	unsigned right_2 :1;
	unsigned right_1 :1;
	
	unsigned left_8 :1;
	unsigned left_7 :1;
	unsigned left_6 :1;
	unsigned left_5 :1;
	unsigned left_4 :1;
	unsigned left_3 :1;
	unsigned left_2 :1;
	unsigned left_1 :1;
	
	unsigned stop :1;
	unsigned play :1;
	unsigned rec :1;
	unsigned top_3 :1;
	unsigned top_2 :1;
	unsigned top_1 :1;
	
	unsigned right :1;
	unsigned left :1;
	
	unsigned field1 :1;
	
	unsigned middle :1;
	unsigned bottom_B :1;
	unsigned bottom_A :1;
	unsigned bottom_4 :1;
	unsigned bottom_3 :1;
	unsigned bottom_2 :1;
	unsigned bottom_1 :1;
#endif	
	unsigned field2 :8;
	
	unsigned x :8;
	unsigned y :8;
	unsigned slider :8;
	
};

struct MIDITimeStamps
{
	AbsoluteTime right_1;
	AbsoluteTime right_2;
	AbsoluteTime right_3;
	AbsoluteTime right_4;
	AbsoluteTime right_5;
	AbsoluteTime right_6;
	AbsoluteTime right_7;
	AbsoluteTime right_8;

	AbsoluteTime left_1;
	AbsoluteTime left_2;
	AbsoluteTime left_3;
	AbsoluteTime left_4;
	AbsoluteTime left_5;
	AbsoluteTime left_6;
	AbsoluteTime left_7;
	AbsoluteTime left_8;
};

#endif