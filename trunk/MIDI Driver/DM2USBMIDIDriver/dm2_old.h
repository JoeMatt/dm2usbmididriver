/*
 *  dm2.h
 *  USBNotificationExample
 *
 *  Created by Joseph Mattiello on 5/3/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _dm2
#define _dm2

#define USE_ASYNC_IO

#define OFF 1
#define ON 0

#define VendorID		1637
//hex :  0x0665 dec : 1637
#define ProductID		769
//hex :  0x0301 dec : 769

#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>
#include <mach/mach.h>
struct dm_status
{
		
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
	
	unsigned field2 :8;
	
	unsigned x :8;
	unsigned y :8;
	unsigned slider :8;
	signed accel_left  :8;
	signed accel_right :8;

};

struct led_status
{
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
};

class DM2 {

private:
	struct led_status leds;
	struct dm_status  status;
	struct dm_status oldstatus;
	IOUSBInterfaceInterface220 	**intf;
	IOUSBDeviceInterface187 **dev;
	char buffer[64];

public:
	DM2();
	~DM2();
	

	void init();
	void toggleLED(int);
	void setLED(int, bool);
	void clearLED();
	void sendLights();
	void testLights();
	void readData();

	struct dm_status getStatus();
	
	IOUSBInterfaceInterface220 	** interface();
	IOReturn USBConfigure();
	IOReturn FindInterfaces();

	static void WriteCompletion(void *, IOReturn result, void *);
	static void ReadCompletion(void *, IOReturn result, void *);
	static void BulkTestDeviceRemoved(void *, io_iterator_t);
	static void BulkTestDeviceAdded(void *, io_iterator_t);

	static  void SignalHandler(int);


	void dump_dm2();

	// globals
	IONotificationPortRef	gNotifyPort;
	io_iterator_t		gRawAddedIter;
	io_iterator_t		gRawRemovedIter;
	io_iterator_t		gBulkTestAddedIter;
	io_iterator_t		gBulkTestRemovedIter;

};



#endif