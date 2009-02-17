/*
 *  DM2BasicNoBanks.h
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 2/17/09.
 *  Copyright 2009 Sense Networks. All rights reserved.
 *
 */

/*
 Inherits all from DM2Configuration.
 
 Ignores switching of banks on bottom 1-4.
 Deletes banks created in DM2Configuration constructor.
 Overrides clearLEDAllBanks() and readSettings() to avoid crashing.
 
 */


#ifndef __DM2BasicNoBanks_h__
#define __DM2BasicNoBanks_h__

#include <Carbon/Carbon.h>
#include "DM2Configuration.h"

class DM2USBMIDIDriver;
class DM2Configuration;

class DM2BasicNoBanks : public DM2Configuration {
public:
	DM2BasicNoBanks();
	
	/* Extra Banks */
	struct Bank * bank2;
	struct Bank * bank3;
	struct Bank * bank4;

	/* Overridden methods */
	void bottom1Clicked(DM2USBMIDIDriver * dm2);
	void bottom2Clicked(DM2USBMIDIDriver * dm2);
	void bottom3Clicked(DM2USBMIDIDriver * dm2);
	void bottom4Clicked(DM2USBMIDIDriver * dm2);
	
	void clearLEDAllBanks();
	void readSettings();

};

#endif