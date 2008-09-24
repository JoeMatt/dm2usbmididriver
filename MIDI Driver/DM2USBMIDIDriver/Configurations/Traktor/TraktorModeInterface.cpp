/*
 *  TraktorModeInterface.cpp
 *  DM2USBMIDIDriver
 *
 *  Created by Joseph Mattiello on 8/16/07.
 *  Copyright 2007 Joe Mattiello. All rights reserved.
 *
 */

#include "TraktorModeInterface.h"
#include "DM2Configuration.h"
#include "DM2 Structs.h"

TraktorModeInterface::TraktorModeInterface(Bank * dm2bank) 
{
	//We don't need our own banks for 'Modes' since TraktorConfiguration() handles them for us
	delete bank1;
	delete bank2;
	delete bank3;
	delete bank4; 
	myBank = currentBank = dm2bank; 
}
