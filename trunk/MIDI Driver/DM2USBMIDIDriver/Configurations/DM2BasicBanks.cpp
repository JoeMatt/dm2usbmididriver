/*
 *  DM2BasicNoBanks.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 2/17/09.
 *  Copyright 2009 Sense Networks. All rights reserved.
 *
 */

#include "DM2BasicBanks.h"
#include "DM2USBMIDI.h"
#include "DM2 Structs.h"

DM2BasicNoBanks::DM2BasicNoBanks() : DM2Configuration()
{	
	/* Delete unused Bank structs */
	delete bank2;
	delete bank3;
	delete bank4;
	
	bank2 = bank3 = bank4 = NULL;
}


#pragma mark Bottom buttons
void DM2BasicNoBanks::bottom1Clicked(DM2USBMIDIDriver * dm2)
{			
	makeBasicNote(dm2->status.bottom_1, kNOTE_BASIC_BOTTOM1BUTTON, dm2);
}
void DM2BasicNoBanks::bottom2Clicked(DM2USBMIDIDriver * dm2)
{			
	makeBasicNote(dm2->status.bottom_3, kNOTE_BASIC_BOTTOM2BUTTON, dm2);
}
void DM2BasicNoBanks::bottom3Clicked(DM2USBMIDIDriver * dm2)
{			
	makeBasicNote(dm2->status.bottom_4, kNOTE_BASIC_BOTTOM3BUTTON, dm2);
}
void DM2BasicNoBanks::bottom4Clicked(DM2USBMIDIDriver * dm2)
{			
	makeBasicNote(dm2->status.bottom_4, kNOTE_BASIC_BOTTOM4BUTTON, dm2);
}

void DM2BasicNoBanks::clearLEDAllBanks()
{
	clearLEDBank(bank1);
}

void DM2BasicNoBanks::readSettings()
{	
	CFPropertyListRef rtn;
	
	// Read the preference, default for CFPreferencesGetAppBooleanValue is false if not found
	
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1StickyButtons"), appID );
	if(rtn != NULL)
		bank1->sticky_buttons = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank1->sticky_buttons = false;
	}
	
		/** MIDI Display **/
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1DisplaysMIDIClock"), appID );
	if(rtn != NULL)
		bank1->isMidiClock = CFBooleanGetValue( (CFBooleanRef) rtn);
	else {
		bank1->isMidiClock = false;
	}
	
		/* Bump Ignore */
	rtn = CFPreferencesCopyAppValue( CFSTR("bank1ScratchRingBumpIgnore"), appID );
	if(rtn != NULL)
		CFNumberGetValue( (CFNumberRef) rtn, kCFNumberIntType, &(bank1->bumpIgnore));
	else
		bank1->bumpIgnore = 0;
	
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