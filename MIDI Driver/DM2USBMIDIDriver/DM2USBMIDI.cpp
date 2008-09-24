/*=============================================================================
	DM2USBMIDI.cpp
Changelog :: 
	- Beta 3 (0.3)
		- Added invert LED option
		- Added new icon
		- Added clear LEDs button
		- Added calibration reset button
		- Added version update checking
		- Added documentation to prefPane
		- Added tooltips
		- Version numbering scheme simplified
		- Fixed Left scratch ring sending same note for Back and Forward
		- Setting changes take effect without restart/unlplug

	- Beta 2 (0.0.2)
		Changed to 10.2.8 SDK for PPC users
		Added support for LEDs
		Added option for Sticky Keys (swtich emulation) for scratch ring buttons
		Added support for 4 banks with independent scratch ring LED status/buttons
		Created System Preference Pane
		Optimized USB data handeling
		Tested and fixed to work on PPC (Using rosetta on x86 only though)
		Fixed procressing input until after the device is done init'ing to avoid triggering buttons
	- Beta 1 (0.0.1)
		Initial Build
Features ::
	Doesn't seem to crash, yet. On my machine at least.
	A bunch of buttons.
	Auto-Calibrates.

TODO::  
	Allow for fixing of f'd up Joystick rest position.
	Figure out proper way of sending XY on joystick so it will work as dual axis on software synths / Abelton live
	Fix re-init without unplugging DM2
	MIDI clock setting
	Finish settings in prefPane
	Add icon to Growl //sort of there
	Test Growl on PPC
Maybes::
	Joystick control mouse
	Customizable button MIDI values
	DJ1800
	Mixxx template
	Abelton Live 6 support
=============================================================================*/

#include "DM2USBMIDI.h"
#include "DM2Configuration.h"
#include "MixxxConfiguration.h"
#include "TraktorConfiguration.h"
#include <unistd.h> //usleep
#include <time.h> //nanosleep

#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>

//#include <iostream>
//using namespace std;
// ____________________ ** C EXTERN ** _________________________________________//


// Implementation of the factory function for this type. __attribute__((visibility("default"))) makes it so we don't strip the 
// symbol to it therefor making MIDIServer capable of loading.
// see http://www.noodlesoft.com/blog/2007/04/05/xcode-odds-ends-automated-builds/
// and http://developer.apple.com/documentation/DeveloperTools/Conceptual/CppRuntimeEnv/Articles/SymbolVisibility.html
extern "C" __attribute__((visibility("default"))) void *NewDM2USBMIDIDriver(CFAllocatorRef allocator, CFUUIDRef typeID);
extern "C" void *NewDM2USBMIDIDriver(CFAllocatorRef allocator, CFUUIDRef typeID) 
{
	// If correct type is being requested, allocate an
	// instance of TestType and return the IUnknown interface.
	if (CFEqual(typeID, kMIDIDriverTypeID)) {
		DM2USBMIDIDriver *result = new DM2USBMIDIDriver;
		return result->Self();
	} else {
		// If the requested type is incorrect, return NULL.
		return NULL;
	}
}

// ____________________ ** CODE START ** ______________________________________//

DM2USBMIDIDriver::DM2USBMIDIDriver() :
	USBVendorMIDIDriver(kFactoryUUID)
{
		resetCalibration();
		softwareMode = CFSTR("Generic MIDI");
		
		genericConfig = new DM2Configuration();
		mixxxConfig = new MixxxConfiguration();
		traktorConfig = new TraktorConfiguration();

		currentConfig = genericConfig;
}

DM2USBMIDIDriver::~DM2USBMIDIDriver()
{
}

// __________________________________________________________________________________________________

bool		DM2USBMIDIDriver::MatchDevice(	USBDevice *	inUSBDevice)
{
	const IOUSBDeviceDescriptor * devDesc = inUSBDevice->GetDeviceDescriptor();
	if (USBToHostWord(devDesc->idVendor) == kMyVendorID) {
		UInt16 devProduct = USBToHostWord(devDesc->idProduct);
		if (devProduct == kMyProductID)
			return true;
	}
	return false;
}

MIDIDeviceRef	DM2USBMIDIDriver::CreateDevice(	USBDevice *	inUSBDevice, USBInterface *	inUSBInterface)
{
	MIDIDeviceRef dev;
	MIDIEntityRef ent;
	CFStringRef boxName = CFSTR("DM2"); //Model
	MIDIDeviceCreate(Self(),
		boxName,
		CFSTR("MixMan"),	// manufacturer name
		boxName,
		&dev);
	// make entity for each port, with 1 source, 1 destination
	for (int port = 1; port <= kMyNumPorts; ++port) {
		char portname[64];
		if (kMyNumPorts > 1)
			sprintf(portname, "Port %d", port);
		else
			CFStringGetCString(boxName, portname, sizeof(portname), kCFStringEncodingMacRoman);
		CFStringRef str = CFStringCreateWithCString(NULL, portname, 0);
		MIDIDeviceAddEntity(dev, str, false, 1, 1, &ent);  
		CFRelease(str);
	}
	return dev;
}

void	DM2USBMIDIDriver::PreExistingDeviceFound(	MIDIDeviceRef	inMIDIDevice,
									   USBDevice *		inUSBDevice,
									   USBInterface *	inUSBInterface)
{
	IOReturn ioreturn;
	printf("OH SNAP!!!\\n");
	IOUSBDeviceInterface187 **	deviceInterface = (IOUSBDeviceInterface187**) inUSBDevice->GetPluginInterface();
	
//	ioreturn = (*deviceInterface)->USBDeviceOpen(deviceInterface);
//	if( ioreturn == kIOReturnExclusiveAccess)
//		printf("Cant get exclusive access");
//	else if(ioreturn == kIOReturnError)
//		printf("Some error");
//	else if(ioreturn == kIOReturnSuccess)
//		printf("Open was success");
//	else
//		printf("I don't kn ow");
	
	//(*deviceInterface)->SetConfiguration(deviceInterface, 0);
	//(*deviceInterface)->ResetDevice(deviceInterface);
	//(*deviceInterface)->USBDeviceReEnumerate(deviceInterface, 0);
	
	io_iterator_t interface_iterator;
	IOUSBFindInterfaceRequest request;
	request.bInterfaceClass = kIOUSBFindInterfaceDontCare;
	request.bInterfaceSubClass = kIOUSBFindInterfaceDontCare;
	request.bInterfaceProtocol = kIOUSBFindInterfaceDontCare;
	request.bAlternateSetting = kIOUSBFindInterfaceDontCare;
	
	(*deviceInterface)->CreateInterfaceIterator(deviceInterface, &request, &interface_iterator);
	
	io_service_t  usbInterface = ((io_object_t) 0);
	while( (usbInterface = IOIteratorNext(interface_iterator)) )
	{
		printf("Interface!\n");
		//NSLog(@"found interface: %p", (void *)theUsbInterfaceRef);
		IOUSBInterfaceInterface190 **theUsbInterfaceRef = NULL;
		
		IOCFPlugInInterface **iodev;
		SInt32 theScore;
		ioreturn = IOCreatePlugInInterfaceForService(usbInterface, kIOUSBInterfaceUserClientTypeID, kIOCFPlugInInterfaceID, &iodev, &theScore);
		
		IOObjectRelease(usbInterface); // no longer need this reference
		usbInterface = 0;
		
		ioreturn = (*iodev)->QueryInterface(iodev, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID190), (LPVOID*)&theUsbInterfaceRef);
		(*iodev)->Release(iodev); // done with this
		
	//	(*theUsbInterfaceRef)->ClearPipeStallBothEnds(theUsbInterfaceRef,0);
	//	(*theUsbInterfaceRef)->ClearPipeStallBothEnds(theUsbInterfaceRef,1);
	//	(*theUsbInterfaceRef)->ClearPipeStallBothEnds(theUsbInterfaceRef,0x81);
		//(*theUsbInterfaceRef)->Release(theUsbInterfaceRef);
		//(*theUsbInterfaceRef)->USBInterfaceClose(theUsbInterfaceRef);
		//(*theUsbInterfaceRef)->ReadPipe(theUsbInterfaceRef,0x81,nil,nil);
		UInt8 numendpoints;
		(*theUsbInterfaceRef)->GetNumEndpoints(theUsbInterfaceRef, &numendpoints);
		printf("Number of endpoints : %u", numendpoints); 
		UInt8 x;
		for(x=0; x<numendpoints;x++)
			(*theUsbInterfaceRef)->ClearPipeStallBothEnds(theUsbInterfaceRef,x);
		
		printf("dd shit\n");
	}
	IOObjectRelease(interface_iterator);
	
	//IOUSBInterfaceInterface **  interfaceInterface = (IOUSBInterfaceInterface**) inUSBInterface->GetPluginInterface();
	//(*interfaceInterface)->ClearPipeStallBothEnds(interfaceInterface, 2);
	//(*interfaceInterface)->GetBandwidthAvailable(interfaceInterface,nil);
	//(*deviceInterface)->USBDeviceReEnumerate(deviceInterface, 0);
	//(*deviceInterface)->ResetDevice(deviceInterface);
	//IOUSBInterfaceInterface ** intf =  inUSBInterface->GetPluginInterface();
//	(*intf)->ClearPipeStall(*intf,2);
	//intf->AbortPipe(intf,2);
	//GusbmDev->Initialize();
}



USBInterface *	DM2USBMIDIDriver::CreateInterface(USBMIDIDevice *device)
{
	USBInterface *intf = device->mUSBDevice->FindInterface(kTheInterfaceToUse, 0);
	return intf;
}

void		DM2USBMIDIDriver::StartInterface(USBMIDIDevice *usbmDev)
{
	char buffer[16];
	IOUSBInterfaceInterface ** intf =  usbmDev->mUSBIntfIntf;
	GusbmDev = usbmDev;
	IOReturn ioreturn;
	
	for(int x = 0; x<5;x++)
	{
		bzero(buffer, sizeof(buffer));
		
		*((uint16_t *) buffer + 1) = 0xFFFF;
		*((uint16_t *) buffer ) =  x%2 ? 0xFFFF : 0x0000;
		*((uint16_t *) buffer ) = HostToUSBWord( *((uint16_t *) buffer ) );
		ioreturn = (*intf)->WritePipe(intf, 2, buffer, strlen(buffer));
		
		if (ioreturn != kIOReturnSuccess)
		{
			printf("unable to do bulk write (%08x)\n", ioreturn);
			(void) (*intf)->USBInterfaceClose(intf);
			(void) (*intf)->Release(intf);
		}
		usleep(100000);
	//	struct timespec sleeptime;
		
	//	sleeptime.tv_sec = 100; //argument is supplied in milliseconds
		
	//	sleeptime.tv_nsec = 0; 
	//	nanosleep(&sleeptime, NULL);
	}	

	readSettings();
	resetMIDIClock();
	currentConfig->clearLEDAllBanks();
	sendLights();
	
	CFNotificationCenterRef center = CFNotificationCenterGetDistributedCenter();
	CFNotificationCenterAddObserver(center, 
									(void *)this, 
									notifyCallback, 
									NULL,  
									appID, 
									CFNotificationSuspensionBehaviorDeliverImmediately);
	
	//GROWL
	hasGrowl = false;
	if(enableGrowl)
	{
		CFBundleRef growlBundle;
		LoadGrowlBundle(&growlBundle);
		hasGrowl = CFBundleIsExecutableLoaded(growlBundle);
	
		if(hasGrowl)
		{
			// Create & fill the array containing the notifications
			CFMutableArrayRef allNotifications = CFArrayCreateMutable(
																	  kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
			CFArrayAppendValue(allNotifications, CFSTR("Driver Loaded"));
			CFArrayAppendValue(allNotifications, CFSTR("Traktor Mode Change"));
			
			// Create & fill the array containing the notifications that are turned
			// on by default.
			CFMutableArrayRef defaultNotifications = CFArrayCreateMutable(
																		  kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
			CFArrayAppendValue(defaultNotifications, CFSTR("Traktor Mode Change"));
			
			InitGrowlDelegate(&growlDelegate);
			growlDelegate.applicationName = CFSTR("MixMan DM2");
			//growlDelegate.applicationIconData = CFDataCreate(kCFAllocatorDefault, /*values*/ NULL, /*numValues*/ 0, &kCFTypeArrayCallBacks);
			CFTypeRef keys[] = { GROWL_NOTIFICATIONS_ALL, GROWL_NOTIFICATIONS_DEFAULT };
			CFTypeRef values[] = { allNotifications, defaultNotifications };
			growlDelegate.registrationDictionary = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 2,
																	  &kCFTypeDictionaryKeyCallBacks,
																	  &kCFTypeDictionaryValueCallBacks);


			MyGrowl_SetDelegate = (Growl_SetDelegate) CFBundleGetFunctionPointerForName(growlBundle,CFSTR("Growl_SetDelegate"));
			MyGrowl_Notify = (Growl_Notify) CFBundleGetFunctionPointerForName(growlBundle,CFSTR("Growl_NotifyWithTitleDescriptionNameIconPriorityStickyClickContext"));
			#if defined ( __i386__ )
			//We seem to be throwing a random bus error only when using growl and running under Rosetta
			// and only on Deployment mode
			// TODO: test Growl on a real PPC system
			
			MyGrowl_SetDelegate(&growlDelegate);
			#endif
			MyGrowl_Notify(CFSTR("MixMan DM2"),CFSTR("Driver Loaded"),CFSTR("Driver Loaded"),NULL,0,FALSE,NULL);

		}
	}		//END GROWL

}
void DM2USBMIDIDriver::resetInterface()
{
	//IOUSBInterfaceInterface * intf =  *(GusbmDev->mUSBIntfIntf);
	//(*intf)->ClearPipeStall(*intf,0);
	//intf->AbortPipe(intf,2);
	GusbmDev->Initialize();
}
void		DM2USBMIDIDriver::StopInterface(USBMIDIDevice *usbmDev)
{
	#if DEBUG	
	printf("Removing notifier\n");
	#endif
	//Clean-up notifier
	CFNotificationCenterRef center = CFNotificationCenterGetDistributedCenter();
    CFNotificationCenterRemoveEveryObserver(center, this);
	
	//TODO: Call super here? 
	
	// Clear LEDs
	IOReturn ioreturn;	
	IOUSBInterfaceInterface ** intf =  usbmDev->mUSBIntfIntf;
	char buffer[2] = {0xFF, 0xFF};
	
	ioreturn = (*intf)->WritePipe(intf, 2, buffer, strlen(buffer));
}

void		DM2USBMIDIDriver::HandleInput(USBMIDIDevice *usbmDev, MIDITimeStamp when, Byte *readBuf, ByteCount readBufSize)
{
	int cable = usbmDev->mNumEntities - 1;
	pktlist = (MIDIPacketList *)pbuf;
	pkt = MIDIPacketListInit(pktlist);
	this->timeStamp = when;

	if(readBufSize == 8)								// If buffer was of size 8, then update the status, except for the jog discs
	{	
		memcpy( &(((Byte *)(&status )) )[2] , readBuf,8);

		if ( memcmp(&status,&oldstatus,sizeof(struct dm_status)) == 0 || status.slider == 0)		
			// Check if there's even been a change, we can save some time and just return now if there isn't.
			// Or, if the slider is readying 0, that means it's still init'ing and throwing garbage data
			return;
		
		/************* Bank 1 to 4 buttons ************
		* Change the current Bank
		* Do not send MIDI notes
		*********************************************/
	
		bool statusChanged = false;
		if( status.bottom_1 != oldstatus.bottom_1)
		{
			statusChanged = true;
			currentConfig->bottom1Clicked(this);
		}
		else if( status.bottom_2 != oldstatus.bottom_2)
		{
			statusChanged = true;
			currentConfig->bottom2Clicked(this);
		}
 		else if( status.bottom_3 != oldstatus.bottom_3)
		{
			statusChanged = true;
			currentConfig->bottom3Clicked(this);
		}
		else if( status.bottom_4 != oldstatus.bottom_4)
		{
			statusChanged = true;
			currentConfig->bottom4Clicked(this);
		}
		
		/***************** Scratch Ring Buttons *********************
			Check the ring button status.
		************************************************************/
		/* Notes on USB Bus
			it's little endian and so it intel, ppc is big endian
			Also note that values are coming in the opposite order i'd expect, atleast from what I have labeled on my
			DM2, they come counter clockwise,  8 to 1, right then left.
		*/
		if(oldstatus.right_8 != status.right_8)
		{
			currentConfig->buttonRight8Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_7 != status.right_7)
		{
			currentConfig->buttonRight7Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_6 != status.right_6)
		{
			currentConfig->buttonRight6Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_5 != status.right_5)
		{
			currentConfig->buttonRight5Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_4 != status.right_4)
		{
			currentConfig->buttonRight4Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_3 != status.right_3)
		{
			currentConfig->buttonRight3Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_2 != status.right_2)
		{
			currentConfig->buttonRight2Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.right_1 != status.right_1)
		{
			currentConfig->buttonRight1Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_8 != status.left_8)
		{
			currentConfig->buttonLeft8Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_7 != status.left_7)
		{
			currentConfig->buttonLeft7Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_6 != status.left_6)
		{
			currentConfig->buttonLeft6Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_5 != status.left_5)
		{
			currentConfig->buttonLeft5Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_4 != status.left_4)
		{
			currentConfig->buttonLeft4Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_3 != status.left_3)
		{
			currentConfig->buttonLeft3Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_2 != status.left_2)
		{
			currentConfig->buttonLeft2Clicked(this); 
			statusChanged = TRUE;
		}
		if(oldstatus.left_1 != status.left_1)
		{
			currentConfig->buttonLeft1Clicked(this); 
			statusChanged = TRUE;
		}
		if(statusChanged)
			sendLights();
	
					
		/************* Calibrate Slider & Send note **************/
		if (oldstatus.slider != status.slider)
		{ 	//TODO : Maybe inline this?
			if (status.slider > slider_max) {
			slider_max = status.slider;
			slider_ratio = calcRatio(slider_min	,slider_max);
			}	
			currentConfig->sliderMoved(this);
			pkt = MIDIPacketListAdd(pktlist, sizeof(pbuf), pkt, when, 3, (Byte*)&noteBuf );
		}
		/************** END Slider ********************************/
		
		/************** Calibrate Joystick and send notes *********/
			// Range for X on mine is 24 to 164, 140 values
		if( oldstatus.x != status.x)							
		{			
			calibrateJoystickX();
			currentConfig->joystickXMoved(this);
			pkt = MIDIPacketListAdd(pktlist, sizeof(pbuf), pkt, when, 3, (Byte*)&noteBuf );
		}
		if( oldstatus.y != status.y ) 
		{	calibrateJoystickY();
			currentConfig->joystickYMoved(this);
			pkt = MIDIPacketListAdd(pktlist, sizeof(pbuf), pkt, when, 3, (Byte*)&noteBuf );
		}
		/***************    END Joystick   ************************/
		/*************** All other Buttons ************************/
			// Stop Button
		if(status.stop != oldstatus.stop)
		{
			currentConfig->stopClicked(this);
		}
			// Play Button
		if(status.play != oldstatus.play)
		{
			currentConfig->playClicked(this);
		}
			// Record Button
		if(status.rec != oldstatus.rec)
		{
			currentConfig->recClicked(this);
		}
			// Top #3 Button
		if(status.top_3 != oldstatus.top_3)
		{
			currentConfig->top3Clicked(this);
		}
			// Top #2 Button
		if(status.top_2 != oldstatus.top_2)
		{
			currentConfig->top2Clicked(this);
		}
			// Top #1 Button
		if(status.top_1 != oldstatus.top_1)
		{
			currentConfig->top1Clicked(this);
		}
			// Right Ring Button
		if(status.right != oldstatus.right)
		{
			currentConfig->rightClicked(this);
		}
			// Left Ring Button
		if(status.left != oldstatus.left)
		{
			currentConfig->leftClicked(this);
		}
			// Middle Button
		if(status.middle != oldstatus.middle)
		{
			currentConfig->middleClicked(this);
		}
			// Bottom B Button
		if(status.bottom_B != oldstatus.bottom_B)
		{
			currentConfig->bottomBClicked(this);
		}
			// Bottom A Button
		if(status.bottom_A != oldstatus.bottom_A)
		{			
			currentConfig->bottomAClicked(this);
		}
		/************** End 8 byte input **************************/
	}
	/*************** 2 Byte input / Scratch Rings *************/
	else if(readBufSize == 2)							// Else if the buffer was of size two bytes, each byte was the accel of the jog discs
	{
		status.accel_left =  readBuf[0];
		status.accel_right = readBuf[1];
		
		//if( memcmp(&status,&oldstatus,2) == 0 && status.accel_left == 0 && status.accel_right ==0)
		//	return;										//If the first two bytes haven't changed, we can leave.
														// but only if the rings are still 0 also. Maybe change this, I'm not sure what
														// effect this would have on scratching software
														// Update: I think this is frivilous and wastes more time on legit calls.
		/******** LEFT Ring *************/
		if(status.accel_left + oldstatus.accel_left != 0) //There had to have been a change to/from a rest state, or it's moving at the same speed
		{
			currentConfig->leftRingSpun(this);
		}
		/********* RIGHT Ring ****************/
		if(status.accel_right + oldstatus.accel_right != 0)
		{
			currentConfig->rightRingSpun(this);
		}
	}
	else
	{	// Any other size isn't valid
		#if DEBUG
		printf("Error: Unknown message\n");
		#endif
		return;
	}

	//If we got this far, we must have some changes to save and send down the midi pipe.
	
	#if DEBUG_READ
	printf_dm2();
	#endif
	
	memcpy( &oldstatus, &status, sizeof( struct dm_status ));	
	MIDIReceived(usbmDev->mSources[cable], pktlist);
}

void DM2USBMIDIDriver::printf_dm2()
{	
	printf( "--DM2 Status:\n" );
	printf( "Slider: %d, Min: %i, Max: %i, Ratio: %f\n", (unsigned int) status.slider, slider_min, slider_max, slider_ratio );
	printf( "Joystick: X: %d, Y: %d, x_min: %i, x_middle: %i, x_max: %i, y_min: %i, y_middle: %i, y_max: %i\n", (int) status.x, (int) status.y, x_min, x_middle, x_max, y_min, y_middle, y_max );
	printf( "accel left: %d\n", (int) this->status.accel_left );
	printf( "accel right: %d\n", (int) this->status.accel_right );

	if( this->status.right_1 )
		printf( "right 1\n" );
	if( this->status.right_2 )
		printf( "right 2\n" );
	if( this->status.right_3 )
		printf( "right 3\n" );
	if( this->status.right_4 )
		printf( "right 4\n" );
	if( this->status.right_5 )
		printf( "right 5\n" );
	if( this->status.right_6 )
		printf( "right 6\n" );
	if( this->status.right_7 )
		printf( "right 7\n" );
	if( this->status.right_8 )
		printf( "right 8\n" );
	
	if( this->status.left_1 )
		printf( "left 1\n" );
	if( this->status.left_2 )
		printf( "left 2\n" );
	if( this->status.left_3 )
		printf( "left 3\n" );
	if( this->status.left_4 )
		printf( "left 4\n" );
	if( this->status.left_5 )
		printf( "left 5\n" );
	if( this->status.left_6 )
		printf( "left 6\n" );
	if( this->status.left_7 )
		printf( "left 7\n" );
	if( this->status.left_8 )
		printf( "left 8\n" );
	
	
	if( this->status.top_1 )
		printf( "top_1\n" );
	if( this->status.top_2 )
		printf( "top_2\n" );
	if( this->status.top_3 )
		printf( "top_3\n" );
	if( this->status.stop )
		printf( "stop\n" );
	if( this->status.play )
		printf( "play\n" );
	if( this->status.rec )
		printf( "rec\n" );
	
	
	if( this->status.left )
		printf( "left\n" );
	if( this->status.right )
		printf( "right\n" );
	
	if( this->status.bottom_1 )
		printf( "bottom_1\n" );
	if( this->status.bottom_2 )
		printf( "bottom_2\n" );
	if( this->status.bottom_3 )
		printf( "bottom_3\n" );
	if( this->status.bottom_4 )
		printf( "bottom_4\n" );
	if( this->status.bottom_A )
		printf( "bottom_A\n" );
	if( this->status.bottom_B )
		printf( "bottom_B\n" );
	if( this->status.middle )
		printf( "middle\n" );
	
	//printf( "f4 %d\n", this->status.field1 );
	//printf( "f5 %d\n", this->status.field2 );
	
	
}

bool DM2USBMIDIDriver::bitCheck(Byte byt,int bit)
{
	return byt & (1 << bit);
}

void DM2USBMIDIDriver::sendLights(USBMIDIDevice *usbmDev)
{	
	char buffer[16];
	IOReturn ioreturn;
	IOUSBInterfaceInterface ** intf = usbmDev->mUSBIntfIntf;

	bzero(buffer, sizeof(buffer));
	*((uint16_t *) buffer + 1) = 0xFFFF;
	*((uint16_t *) buffer ) =	(currentConfig->currentBank->leds.right_8) +
								(currentConfig->currentBank->leds.right_7 << 1) +
								(currentConfig->currentBank->leds.right_6 << 2) +
								(currentConfig->currentBank->leds.right_5 << 3) +
								(currentConfig->currentBank->leds.right_4 << 4) +
								(currentConfig->currentBank->leds.right_3 << 5) +
								(currentConfig->currentBank->leds.right_2 << 6) + 
								(currentConfig->currentBank->leds.right_1 << 7) +
								(currentConfig->currentBank->leds.left_8 << 8) +
								(currentConfig->currentBank->leds.left_7 << 9) +
								(currentConfig->currentBank->leds.left_6 << 10) +
								(currentConfig->currentBank->leds.left_5 << 11) +
								(currentConfig->currentBank->leds.left_4 << 12) +
								(currentConfig->currentBank->leds.left_3 << 13) +
								(currentConfig->currentBank->leds.left_2 << 14) + 
								(currentConfig->currentBank->leds.left_1 << 15);


	
	
	*((uint16_t *) buffer ) = HostToUSBWord( *((uint16_t *) buffer ) );
	
	ioreturn = (*intf)->WritePipe(intf, 2, buffer, 4);
	//ioreturn = (*intf)->WritePipeAsync(intf, 2, buffer, strlen(buffer), NULL, (void *) usbmDev);
	
	if (ioreturn != kIOReturnSuccess)
	{
		printf("unable to do bulk write (%08x)\n", ioreturn);
		(void) (*intf)->USBInterfaceClose(intf);
		(void) (*intf)->Release(intf);
	}
	#if DEBUG_WRITE
	else
		printf("Wrote \"%4X\" (%ld bytes) to bulk endpoint\n", buffer[0], (UInt32) strlen(buffer));
	#endif
}

void DM2USBMIDIDriver::sendLights(USBMIDIDevice *usbmDev,uint16_t * ledStatus)
{		
	char buffer[16];
	IOReturn ioreturn;
	IOUSBInterfaceInterface ** intf = usbmDev->mUSBIntfIntf;
	
	bzero(buffer, sizeof(buffer));
	*((uint16_t *) buffer + 1) = 0xFFFF;
/*	*((uint16_t *) buffer ) =	(currentConfig->currentBank->leds.right_8) +
								(currentConfig->currentBank->leds.right_7 << 1) +
								(currentConfig->currentBank->leds.right_6 << 2) +
								(currentConfig->currentBank->leds.right_5 << 3) +
								(currentConfig->currentBank->leds.right_4 << 4) +
								(currentConfig->currentBank->leds.right_3 << 5) +
								(currentConfig->currentBank->leds.right_2 << 6) + 
								(currentConfig->currentBank->leds.right_1 << 7) +
								(currentConfig->currentBank->leds.left_8 << 8) +
								(currentConfig->currentBank->leds.left_7 << 9) +
								(currentConfig->currentBank->leds.left_6 << 10) +
								(currentConfig->currentBank->leds.left_5 << 11) +
								(currentConfig->currentBank->leds.left_4 << 12) +
								(currentConfig->currentBank->leds.left_3 << 13) +
								(currentConfig->currentBank->leds.left_2 << 14) + 
								(currentConfig->currentBank->leds.left_1 << 15);
*/	
	*((uint16_t *) buffer ) = *ledStatus;
	
	
	*((uint16_t *) buffer ) = HostToUSBWord( *((uint16_t *) buffer ) );
	
	ioreturn = (*intf)->WritePipe(intf, 2, buffer, 4);
	//ioreturn = (*intf)->WritePipeAsync(intf, 2, buffer, strlen(buffer), NULL, (void *) usbmDev);
	
	if (ioreturn != kIOReturnSuccess)
	{
		printf("unable to do bulk write (%08x)\n", ioreturn);
		(void) (*intf)->USBInterfaceClose(intf);
		(void) (*intf)->Release(intf);
	}
#if DEBUG_WRITE
	else
		printf("Wrote \"%4X\" (%ld bytes) to bulk endpoint\n", buffer[0], (UInt32) strlen(buffer));
#endif
}

void DM2USBMIDIDriver::sendLights()
{
	sendLights(GusbmDev);
}

void DM2USBMIDIDriver::readSettings()
{
#if DEBUG
	printf("Read Settings\n");
#endif
	CFPropertyListRef rtn;
	
	/** Software Mode **/
	rtn = CFPreferencesCopyAppValue( CFSTR("softwareMode"), appID );
	if(rtn != NULL)
		softwareMode = (CFStringRef) rtn;
	else
		softwareMode = CFSTR("Generic MIDI");
	
	if(CFStringCompare(softwareMode, CFSTR("Mixxx"),0) == 0)
		currentConfig = mixxxConfig;
	else if(CFStringCompare(softwareMode, CFSTR("Traktor"),0) == 0)
		currentConfig = traktorConfig;
	else
		currentConfig = genericConfig;
	
	/** MIDI Clock Resolution */
	rtn = CFPreferencesCopyAppValue( CFSTR("midiClockResolution"), appID );
	if(rtn != NULL)
		midiClockResolution = (CFStringRef) rtn;
	else
		midiClockResolution = CFSTR("16th");
	/** Growl **/
	rtn = CFPreferencesCopyAppValue( CFSTR("growlSupport"), appID );
	if(rtn != NULL)
		enableGrowl = CFBooleanGetValue((CFBooleanRef) rtn);
	else
		enableGrowl = false;
	
	currentConfig->readSettings();
	
#if DEBUG
	printf("Software Mode: %s\n",CFStringGetCStringPtr(softwareMode,0));
#endif
	
	if(rtn)
		CFRelease(rtn);

}

void DM2USBMIDIDriver::show(CFStringRef formatString, ...) {
	CFStringRef resultString;
	CFDataRef data;
	va_list argList;
	
	va_start(argList, formatString);
	resultString = CFStringCreateWithFormatAndArguments(NULL, NULL, 
														formatString, argList);
	va_end(argList);
	
	data = CFStringCreateExternalRepresentation(NULL, resultString, 
												CFStringGetSystemEncoding(), '?');
	
	if (data != NULL) {
		printf ("%.*s\n\n", (int)CFDataGetLength(data), 
				CFDataGetBytePtr(data));
		CFRelease(data);
	}
	CFRelease(resultString);
}

void DM2USBMIDIDriver::resetCalibration()
{	
		//Set calibration data
		/*
		 I tried letting it set its own values, but garbage data on init caused the mins to be below the actual mins. So this is hardcoded to start at 24 and stay. The maxes seemed
		 to all be different but the mins were all 24 so I hope this is accurate enough for most devices.
		 The maxes are autocalibrated on the fly using code below as values come in.
		 */
		
		x_min = 24 ;
		x_middle = 0;
		x_max =  25 ;
		x_ratio = calcRatio(x_min, x_max);
		
		y_min = 24 ;
		y_middle = 0;
		y_max = 25 ;
		y_ratio = calcRatio( y_min, y_max);
		
		slider_min = 24;
		slider_max = 25;
		slider_ratio = calcRatio(slider_min	,slider_max);
}



void DM2USBMIDIDriver::resetMIDIClock()
{
	midiClockRightRing = 0;
	midiClockLeftRing = 0;
	midiClock = 0;
	midiClockPaused = 0;
}

ByteCount	DM2USBMIDIDriver::PrepareOutput(USBMIDIDevice *usbmDev, WriteQueue &writeQueue, 
											Byte *destBuf)
{
//The caller to this function is like this, basically
	//		IOBuffer &writeBuffer = mWriteBuf[mCurWriteBuf];
//		ByteCount msglen = mDriver->PrepareOutput(this, mWriteQueue, writeBuffer);
//WritePipeAsync(mUSBIntfIntf, mOutPipe.mPipeIndex, writeBuffer, msglen, WriteCallback, this));
//msglen is the size of data to write
//writeBuffer hold the data, which is the same as destBuf
//writeQueue is the MIDI data
	
	// 8 OUT: 0B B0 08 7F 00 00 00 00 
	// CC chan 8, sent value 127, i dunno wtf 0B was for
	// 
	Byte *dest = destBuf, *destend = dest + usbmDev->mOutPipe.mMaxPacketSize;

	while (!writeQueue.empty()) {		
		WriteQueue::iterator wqit = writeQueue.begin();
		WriteQueueElem *wqe = &(*wqit);
		Byte *dataStart = wqe->packet.Data();
		Byte *src = dataStart + wqe->bytesSent;
		Byte *srcend = dataStart + wqe->packet.Length();
		int srcLeft;
		
		//Byte cableNibble = wqe->portNum << 4;
		
		while ((srcLeft = srcend - src) > 0 && dest <= destend - 4) {
			Byte c = *src++;
			
			switch (c >> 4) {
				case 0x8:	// note-off
				case 0x9:	// note-on
				/*	*dest++ = cableNibble | (c >> 4);
					*dest++ = c;
					*dest++ = *src++;
					*dest++ = *src++;
				*/
					//0 - 63
					//type, number velocity
					int note, velocity;
					note = *src++;
					velocity = *src++;
					if(note < 64)
					{
						struct Bank * changedBank;
						switch( note / 16 )
						{
							case 0:
								changedBank = currentConfig->bank1;
								break;
							case 1:
								changedBank = currentConfig->bank2;
								break;
							case 2:
								changedBank = currentConfig->bank3;
								break;
							case 3:
								changedBank = currentConfig->bank4;
								break;
							default:
								changedBank = currentConfig->bank1;
								break;
						}		
						int ledNumber = note % 16;
						//currentConfig->toggleLED(ledNumber,changedBank);
						bool onMessage;
						onMessage = ((c >> 4 ) == 0x9);
						currentConfig->buttonReceived(ledNumber, changedBank, velocity, onMessage); 
						#if DEBUG
						printf("Received, LED#: %i, Vel: %i\n",ledNumber,velocity);
						#endif
						if(changedBank == currentConfig->currentBank)
							sendLights();
					}
					else if(currentConfig == mixxxConfig)
					{
						//TODO: Fix this hacky case
						int ledNumber;
						if(note < 80)
							ledNumber = note%16;
						else
							ledNumber = (note-8)%16;
						
						bool onMessage;
						onMessage = ((c >> 4 ) == 0x9);
						currentConfig->buttonReceived(ledNumber, mixxxConfig->bank1, velocity, onMessage); 
						#if DEBUG
						printf("Mixxx Received, LED#: %i, Vel: %i\n",ledNumber,velocity);
						#endif
						sendLights();
					}
					break;
				case 0x0: case 0x1: case 0x2: case 0x3:
				case 0x4: case 0x5: case 0x6: case 0x7:
					// data byte, presumably a sysex continuation
					// F0 is also handled the same way
					inSysEx:
					--srcLeft;
					if (srcLeft < 2 && (
										srcLeft == 0 
										|| (srcLeft == 1 && src[0] != 0xF7))) {
						// we don't have 3 sysex bytes to fill the packet with
						// undo consumption of the first source byte
						--src;
						wqe->bytesSent = src - dataStart;
						//goto DoneFilling;
					} else {
						dest[1] = c;
						if ( *src++ == 0xF7) {
							;		// sysex ends with following 2 bytes
						} else if ( *src++ == 0xF7)
							;		// sysex ends with following 3 bytes
						}
					break;
				case 0xA:	// poly pressure
				case 0xB:	// control change
				case 0xE:	// pitch bend
					*src++;
					*src++;
					break;
				case 0xC:	// program change
				case 0xD:	// mono pressure
					*src++;
					break;
				case 0xF:	// system message
					switch (c) {
						case 0xF0:	// sysex start
							goto inSysEx;
						case 0xF8:	// clock
							// clock
							//clock sends 24 ticks per 'beat', ie 1/4 note, 12 clicks for 1/8th note, 6clicks per 16th note
							// more info http://www.gweep.net/~prefect/eng/reference/protocol/midispec.html#Seq
							//*dest++ = cableNibble | 0xF;// 1-byte system realtime
							//*dest++ = c;
							//*dest++ = 0;
							//*dest++ = 0;
							u_int16_t ledBinary = 0;
							if( CFStringCompare( midiClockResolution, CFSTR("1/4"),0) == 0 )
							{
								if(++midiClock % 24 == 0)
									midiClockLeftRing++;
								ledBinary = 1 << (midiClockLeftRing+8);
									
								if(midiClock % 24 < 3)
									ledBinary += 0xFF;
								 ledBinary = ~ledBinary;			 
							}
							else
							{
								int noteFractionModifier;
							
								noteFractionModifier = CFStringCompare( midiClockResolution,CFSTR("16th"),0) == kCFCompareEqualTo ? 2 : 1;

								if( !midiClockPaused && ((++midiClock % (3*noteFractionModifier)) == 0))
								{		
									
									if((++midiClockRightRing*noteFractionModifier % 8) == 0)
									{
										midiClockRightRing =0;
										if((++midiClockLeftRing % 8) == 0)
											midiClockLeftRing = 0;
									}
								
									
									ledBinary = ~(
												(1 << (midiClockLeftRing+8)) |
												( (int)(pow(2.0,(double) noteFractionModifier)-1) << (midiClockRightRing*noteFractionModifier ))
												);
								//	if(currentConfig->currentBank->invertLeds)
								//		ledBinary = ~ledBinary;
								}
							}

							if(currentConfig->currentBank->isMidiClock == TRUE)
							{
	
								//*((uint16_t *) &currentConfig->currentBank->leds) = ledBinary;
								currentConfig->currentBank->leds.left_1 = false;
								currentConfig->currentBank->leds.left_2 = false;
								currentConfig->currentBank->leds.left_3 = false;
								currentConfig->currentBank->leds.left_4 = false;
								currentConfig->currentBank->leds.left_5 = false;
								currentConfig->currentBank->leds.left_6 = false;
								currentConfig->currentBank->leds.left_7 = false;
								currentConfig->currentBank->leds.left_8 = false;
								switch(midiClockLeftRing)
								{
									case 0:
										currentConfig->currentBank->leds.left_1 = TRUE;
										break;
									case 1:
										currentConfig->currentBank->leds.left_2 = TRUE;
										break;
									case 2:
										currentConfig->currentBank->leds.left_3 = TRUE;
										break;
									case 3:
										currentConfig->currentBank->leds.left_4 = TRUE;
										break;
									case 4:
										currentConfig->currentBank->leds.left_5 = TRUE;
										break;
									case 5:
										currentConfig->currentBank->leds.left_6 = TRUE;
										break;
									case 6:
										currentConfig->currentBank->leds.left_7 = TRUE;
										break;
									case 7:
										currentConfig->currentBank->leds.left_8 = TRUE;
										break;
								}
								currentConfig->currentBank->leds.right_8 = (ledBinary & (1 << 0)) >> 0;
								currentConfig->currentBank->leds.right_7 = (ledBinary & (1 << 1)) >> 1;
								currentConfig->currentBank->leds.right_6 = (ledBinary & (1 << 2)) >> 2;
								currentConfig->currentBank->leds.right_5 = (ledBinary & (1 << 3)) >> 3;
								currentConfig->currentBank->leds.right_4 = (ledBinary & (1 << 4)) >> 4;
								currentConfig->currentBank->leds.right_3 = (ledBinary & (1 << 5)) >> 5;
								currentConfig->currentBank->leds.right_2 = (ledBinary & (1 << 6)) >> 6;
								currentConfig->currentBank->leds.right_1 = (ledBinary & (1 << 7)) >> 7;
								
								currentConfig->currentBank->leds.left_8 = (ledBinary & (1 << 8)) >> 8;
								currentConfig->currentBank->leds.left_7 = (ledBinary & (1 << 9)) >> 9;
								currentConfig->currentBank->leds.left_6 = (ledBinary & (1 << 10)) >> 10;
								currentConfig->currentBank->leds.left_5 = (ledBinary & (1 << 11)) >> 11;
								currentConfig->currentBank->leds.left_4 = (ledBinary & (1 << 12)) >> 12;
								currentConfig->currentBank->leds.left_3 = (ledBinary & (1 << 13)) >> 13;
								currentConfig->currentBank->leds.left_2 = (ledBinary & (1 << 14)) >> 14;
								currentConfig->currentBank->leds.left_1 = (ledBinary & (1 << 15)) >> 15;
								sendLights();
								//sendLights(GusbmDev, &ledBinary);
								//sendLights();
							}
								printf("MIDI Left: %i, midiright: %i\n",midiClockLeftRing,midiClockRightRing);	
							break;		
						case 0xFA:	// start
							resetMIDIClock();
							break;
						case 0xFB:	// continue
							midiClockPaused = FALSE;
							break;
						case 0xFC:	// stop
							midiClockPaused = TRUE;
							break;
						case 0xFE:	// active sensing
						case 0xFF:	// system reset
							break;
						case 0xF6:	// tune request (0)
						case 0xF7:	// EOX
							break;
						case 0xF1:	// MTC (1)
						case 0xF3:	// song select (1)
							*src++;
							break;
						case 0xF2:	// song pointer (2)
							*src++;
							*src++;
							break;
					}
				default:
					// unknown MIDI message! advance until we find a status byte
					while (src < srcend && *src < 0x80)
						++src;
					break;
			}
			
			if (src >= srcend) {
				// source packet completely sent
				wqe->packet.Dispose();
				writeQueue.erase(wqit);
				if (writeQueue.empty())
					break;
			} else
				wqe->bytesSent = src - dataStart;
		} // ran out of source data or filled buffer
			
			if (dest > destend - 4)
				// destBuf completely filled
				break;
		
		// we didn't fill the output buffer, loop around to look for more 
		// source data in the write queue
		
	} // while walking writeQueue
	return dest - destBuf;	
	
	/* This isn't a true MIDI device so we need to make our own handeler
		int n = USBMIDIPrepareOutput(usbmDev, writeQueue, destBuf, usbmDev->mOutPipe.mMaxPacketSize);
	if (n < usbmDev->mOutPipe.mMaxPacketSize) {
		memset(destBuf + n, 0, usbmDev->mOutPipe.mMaxPacketSize - n);
	}
	
	return usbmDev->mOutPipe.mMaxPacketSize;
	*/
} 

//Non-member function
void notifyCallback(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo) {

	DM2USBMIDIDriver * dm2 = (DM2USBMIDIDriver*) observer;

	if( CFStringCompare(name, CFSTR("Preferences Changed"), 0) == kCFCompareEqualTo)
	{
		CFPreferencesAppSynchronize(appID);
		dm2->readSettings();
		printf("Setting Changed\n");
	}
	else if( CFStringCompare(name, CFSTR("Clear All LEDs"), 0) == kCFCompareEqualTo)
	{	
		dm2->currentConfig->clearLEDAllBanks();
		dm2->sendLights(dm2->GusbmDev);
		printf("Cleared all LEDs\n");
	}
	else if( CFStringCompare(name, CFSTR("Reset Calibration"), 0) == kCFCompareEqualTo)
	{
		dm2->resetCalibration();
		printf("Calibration Data Reset\n");
	}
	else if( CFStringCompare(name, CFSTR("Reset Interface"), 0) == kCFCompareEqualTo)
	{
		dm2->resetInterface();
		printf("Interface Reset\n");
	}
	else
		printf("Unknown Notificaiton Received\n");
}

void LoadGrowlBundle (CFBundleRef *bundlePtr)                
{
    CFURLRef    baseURL     = NULL;
    CFURLRef    bundleURL   = NULL;
	
    if ( bundlePtr == NULL ) goto Bail;
    *bundlePtr = NULL;
	
	bundleURL = CFURLCreateWithFileSystemPath(
											  kCFAllocatorDefault,
											  CFSTR("/Library/Audio/MIDI Drivers/DM2USBMIDIDriver.plugin/Contents/Frameworks/Growl.Framework"),
											  kCFURLPOSIXPathStyle,
											  true );
	if ( bundleURL == NULL ) goto Bail;
	*bundlePtr = CFBundleCreate(kCFAllocatorDefault,bundleURL);
	if ( *bundlePtr == NULL ) goto Bail;

    if ( ! CFBundleLoadExecutable (*bundlePtr) )                        
    {
		CFRelease (*bundlePtr);
        *bundlePtr = NULL;
    }

Bail:
	if ( bundleURL != NULL ) CFRelease (bundleURL);                     
    if ( baseURL != NULL ) CFRelease (baseURL);                        
}