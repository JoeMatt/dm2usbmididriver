/*=============================================================================
	DM2USBMIDI.h
	By : Joe Mattiello

	Based upon: SampleUSBMIDI.h © Copyright 2005 Apple Computer, Inc.
	
=============================================================================*/

#ifndef __DM2USBMIDI_h__
#define __DM2USBMIDI_h__

#include "USBVendorMIDIDriver.h"
#include "DM2 Structs.h"
#include <Growl/GrowlApplicationBridge-Carbon.h>
#include <Growl/GrowlDefines.h>

// --------------------- ** PRE-PROC DEFINES ** ----------------------------//

// CFUUID 
#define kFactoryUUID CFUUIDGetConstantUUIDWithBytes(NULL, 0xEC, 0x2F, 0x5F, 0x94, 0x26, 0x22, 0x41, 0x43, 0xBC, 0xF9, 0x02, 0xCF, 0x77, 0x50, 0x1C, 0x5E)
// EC2F5F94-2622-4143-BCF9-02CF77501C5E

#define kTheInterfaceToUse	0

#define kMyVendorID			0x0665
#define kMyProductID		0x0301
#define kMyNumPorts			1		

//The bits for LED status
#define ON FALSE
#define OFF TRUE

#if DEBUG
#define DEBUG_WRITE		0
#define DEBUG_READ		0
#define DEBUG_BUTTONS	1
#endif

#define appID CFSTR("com.joemattiello.driver.dm2")

#define kDoubleClickTime -150000

class DM2Configuration;
class DM2BasicNoBanks;
class MixxxConfiguration;
class TraktorConfiguration;

class DM2USBMIDIDriver : public USBVendorMIDIDriver {
public:
	DM2USBMIDIDriver();
	~DM2USBMIDIDriver();
	
	// USBMIDIDriverBase overrides
	virtual bool			MatchDevice(		USBDevice *		inUSBDevice);

	virtual MIDIDeviceRef	CreateDevice(		USBDevice *		inUSBDevice,
												USBInterface *	inUSBInterface);
	
	virtual void			PreExistingDeviceFound(	MIDIDeviceRef	inMIDIDevice,
												   USBDevice *		inUSBDevice,
												   USBInterface *	inUSBInterface);
	

	virtual USBInterface *	CreateInterface(	USBMIDIDevice *	usbmDev);

	virtual void		StartInterface(			USBMIDIDevice *	usbmDev);
							// pipes are opened, do any extra initialization (send config msgs etc)
							
	virtual void		StopInterface(			USBMIDIDevice *	usbmDev);
							// pipes are about to be closed, do any preliminary cleanup
							
	virtual void		HandleInput(			USBMIDIDevice *	usbmDev,
												MIDITimeStamp	when,
												Byte *			readBuf,
												ByteCount 		readBufSize);
	void TraktorHandleInput(USBMIDIDevice *usbmDev, MIDITimeStamp when, Byte *readBuf, ByteCount readBufSize);

							// a USB message arrived, parse it into a MIDIPacketList and
							// call MIDIReceived

	virtual ByteCount	PrepareOutput(			USBMIDIDevice *	usbmDev,
												WriteQueue &	writeQueue,
												Byte *			destBuf);
							// dequeue from WriteQueue into a single USB message, return
	
	dm_status status;
	dm_status oldstatus;
	
	USBMIDIDevice *GusbmDev;
	
	void printf_dm2();
	
	int midiClock;
	int midiClockLeftRing;
	int midiClockRightRing;
	bool midiClockPaused;
	CFStringRef midiClockResolution;
	
	struct MIDITimeStamps timeStamps;
	
	//Growl, it's loaded dynamically from inside the bundle so we're using function pointers since normal linking won't work
	// The reason it won't work you ask? Well we're a dynamic bundle being loaded from MIDIServer, and therefor can't link to, 
	// and then dynamically load our own bundles correctly in version of OS X below 10.4, which used to be our target.
	// TODO: upgrade the following to more sane methods supported by 10.4, @loader_path instead of @executable_path
	// see: http://growl.info/documentation/developer/implementing-growl.php?lang=cocoa
	
	struct Growl_Delegate growlDelegate;
	typedef Boolean (*Growl_SetDelegate)(struct Growl_Delegate *);
	typedef void	(*Growl_Notify)(CFStringRef,CFStringRef,CFStringRef,CFDataRef,signed int,Boolean,CFPropertyListRef);
	
	Growl_SetDelegate MyGrowl_SetDelegate;
	Growl_Notify	MyGrowl_Notify;
	bool enableGrowl;
	bool hasGrowl;
	//End Growl
	
	void createNote(struct Button * button, Byte * noteBuf);

	void setLED(int, bool);
	void sendLights(USBMIDIDevice *usbmDev);
	void sendLights(USBMIDIDevice *usbmDev, uint16_t *);
	void sendLights();
	void testLights();
	char buffer[16];
	bool bitCheck(Byte,int);
	CFStringRef softwareMode;

	void resetInterface();
	void resetMIDIClock();
	
	/*** Calibration data *****/
	unsigned int x_min, x_middle, x_max, 
		y_min, y_middle, y_max,
		slider_min, slider_max, slider_middle;
	double x_ratio, y_ratio, slider_ratio, x_adjust, y_adjust;
	bool calibrated;
	//double calcRatio(int x, int y);
	int calcSliderValue();
	void calibrateJoystickX();
	void calibrateJoystickY();
	int calcJoystickXValue();
	int calcJoystickYValue();
	/*** MIDI Packet handelers ****/
	MIDIPacket *pkt;
	MIDIPacketList *pktlist;
	MIDITimeStamp timeStamp;
	Byte pbuf[64];
	Byte noteBuf[4];
	
	void readSettings();
	void resetCalibration();
	void show(CFStringRef, ...);
	
	DM2Configuration * currentConfig;
	DM2Configuration * genericConfigWithBanks;
	DM2BasicNoBanks * genericConfigNoBanks;
	MixxxConfiguration * mixxxConfig;
	TraktorConfiguration * traktorConfig;
};
//Non-member function
void notifyCallback(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo);
void LoadGrowlBundle (CFBundleRef *bundlePtr);

//inline functions
//TODO:maybe grab some of these and make them STATIC, will that save performacne, espcailly calcRatio and calcSliderValue
inline const static double 
#ifdef __LITTLE_ENDIAN__
__attribute__((fastcall)) //makes the values passed by register rather than stack 
#endif
calcRatio(int x, int y)
{
	return 127.0 / (double) abs(x-y);
}
inline void DM2USBMIDIDriver::calibrateJoystickX()
{
	if (status.x > x_max) {
		x_max = status.x;
		x_ratio = calcRatio(x_min, x_max);
	}
	
	if( !x_middle)
		x_middle = status.x;
}
inline void DM2USBMIDIDriver::calibrateJoystickY()
{
	if (status.y > y_max) {
		y_max = status.y;
		y_ratio = calcRatio(y_min, y_max);
	}
	if( !y_middle)
		y_middle = status.y;
}

inline int DM2USBMIDIDriver::calcSliderValue()
{
	return (int) ((status.slider - slider_min) * slider_ratio);
}

inline int DM2USBMIDIDriver::calcJoystickXValue()
{
	double value;
	value = (double)(status.x - x_min) * x_ratio;
	return (int) value;
}

inline int DM2USBMIDIDriver::calcJoystickYValue()
{
	return (int) ((status.y - y_min) * y_ratio);
}
#endif // __DM2USBMIDI_h__
