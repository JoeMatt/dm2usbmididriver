/*
 *  dm2.cpp
 *  USBNotificationExample
 *
 *  Created by Joseph Mattiello on 5/3/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "dm2.h"

DM2::DM2(){
	leds.right_1 = OFF;
	leds.right_2 = OFF;
	leds.right_3 = OFF;
	leds.right_4 = OFF;
	leds.right_5 = OFF;
	leds.right_6 = OFF;
	leds.right_7 = OFF;
	leds.right_8 = OFF;
	leds.left_1 = OFF;
	leds.left_2 = OFF;
	leds.left_3 = OFF;
	leds.left_4 = OFF;
	leds.left_5 = OFF;
	leds.left_6 = OFF;
	leds.left_7 = OFF;
	leds.left_8 = OFF;
	
	mach_port_t 		masterPort;
    CFMutableDictionaryRef 	matchingDict;
    CFRunLoopSourceRef		runLoopSource;
    kern_return_t		kr;
    SInt32			usbVendor = VendorID;
    SInt32			usbProduct = ProductID;

	
    // first create a master_port for my task
    kr = IOMasterPort(MACH_PORT_NULL, &masterPort);
    if (kr || !masterPort)
    {
        printf("ERR: Couldn't create a master IOKit Port(%08x)\n", kr);
       // return -1;
		EXIT_FAILURE;
	}
	
    printf("Looking for devices matching vendor ID=%ld and product ID=%ld\n", usbVendor, usbProduct);
	
    // Set up the matching criteria for the devices we're interested in
    matchingDict = IOServiceMatching(kIOUSBDeviceClassName);	// Interested in instances of class IOUSBDevice and its subclasses
    if (!matchingDict)
    {
        printf("Can't create a USB matching dictionary\n");
        mach_port_deallocate(mach_task_self(), masterPort);
        //return -1;
		EXIT_FAILURE;
	}
    
    // Add our vendor and product IDs to the matching criteria
    CFDictionarySetValue( 
						  matchingDict, 
						  CFSTR(kUSBVendorID), 
						  CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &usbVendor)); 
    CFDictionarySetValue( 
						  matchingDict, 
						  CFSTR(kUSBProductID), 
						  CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &usbProduct)); 
	
    // Create a notification port and add its run loop event source to our run loop
    // This is how async notifications get set up.
    gNotifyPort = IONotificationPortCreate(masterPort);
    runLoopSource = IONotificationPortGetRunLoopSource(gNotifyPort);
    
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);
    
    // Retain additional references because we use this same dictionary with four calls to 
    // IOServiceAddMatchingNotification, each of which consumes one reference.
    matchingDict = (CFMutableDictionaryRef) CFRetain( matchingDict ); 
    matchingDict = (CFMutableDictionaryRef) CFRetain( matchingDict ); 
    matchingDict = (CFMutableDictionaryRef) CFRetain( matchingDict ); 
    
    // Change the USB product ID in our matching dictionary to the one the device will have once the
    // bulktest firmware has been downloaded.
    usbProduct = ProductID;
    
    CFDictionarySetValue( 
						  matchingDict, 
						  CFSTR(kUSBProductID), 
						  CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &usbProduct)); 
	
    // Now set up two more notifications, one to be called when a bulk test device is first matched by I/O Kit, and the other to be
    // called when the device is terminated.
	//void (DM2::*BulkTestDeviceAdded) (void *refCon, io_iterator_t ) = &DM2::BulkTestDeviceAdded;
	
	
    kr = IOServiceAddMatchingNotification(  gNotifyPort,
                                            kIOFirstMatchNotification,
                                            matchingDict,
                                            BulkTestDeviceAdded,
                                            this,
                                            &gBulkTestAddedIter );
	
    BulkTestDeviceAdded(this, gBulkTestAddedIter);	// Iterate once to get already-present devices and
													// arm the notification
	
	kr = IOServiceAddMatchingNotification(  gNotifyPort,
                                            kIOTerminatedNotification,
                                            matchingDict,
                                            BulkTestDeviceRemoved, 
                                            this,
                                            &gBulkTestRemovedIter );
	
    BulkTestDeviceRemoved(NULL, gBulkTestRemovedIter); 	// Iterate once to arm the notification
	
    // Now done with the master_port
    mach_port_deallocate(mach_task_self(), masterPort);
    masterPort = 0;
	
    // Start the run loop. Now we'll receive notifications.
    CFRunLoopRun();
	
}

DM2::~DM2()
{
	// Clean up here
	IONotificationPortDestroy(gNotifyPort);
	
	if (gRawAddedIter) 
	{
		IOObjectRelease(gRawAddedIter);
		gRawAddedIter = 0;
	}
	
	if (gRawRemovedIter) 
	{
		IOObjectRelease(gRawRemovedIter);
		gRawRemovedIter = 0;
	}
	
	if (gBulkTestAddedIter) 
	{
		IOObjectRelease(gBulkTestAddedIter);
		gBulkTestAddedIter = 0;
	}
	
	if (gBulkTestRemovedIter) 
	{
		IOObjectRelease(gBulkTestRemovedIter);
		gBulkTestRemovedIter = 0;
	}
	
	(*dev)->USBDeviceClose(dev);
}
void DM2::testLights()
{
	int counter = 0;	
	do {
		counter = (counter + 1)%16;	
		int x;
		for(x=0;x<16;x++)
			toggleLED(x);
		
		clearLED();
		setLED(counter, ON);	
		sendLights();
		usleep(50000);
	}while(counter<15);
}

void DM2::WriteCompletion(void *refCon, IOReturn result, void *arg0)
{
    DM2 *dm2 = (DM2*) refCon;
	//UInt32 			numBytesWritten = (UInt32) arg0;
    
    printf("Async write complete.\n");
    if (kIOReturnSuccess != result)
    {
        printf("error from async bulk write (%08x)\n", result);
		(void) (*dm2->intf)->USBInterfaceClose(dm2->intf);
		(void) (*dm2->intf)->Release(dm2->intf);
        return;
    }
	
	//dm2->readData();
	// printf("Wrote \"%s\" (%ld bytes) to bulk endpoint\n", kTestMessage, numBytesWritten);
	/* READING CODE
		numBytesRead = sizeof(gBuffer) - 1; // leave one byte at the end for NUL termination
											//result = (*intf)->ReadPipeAsync(intf, 9, gBuffer, numBytesRead, ReadCompletion, refCon);
	
	result = (*intf)->ReadPipeAsync(intf, 1, gBuffer, numBytesRead, ReadCompletion, refCon);
	printf("Output: %s", gBuffer);
	if (kIOReturnSuccess != result)
    {
        printf("unable to do async bulk read (%08x)\n", result);
        (void) (*intf)->USBInterfaceClose(intf);
        (void) (*intf)->Release(intf);
        return;
    }
    */
}
void DM2::ReadCompletion(void *refCon, IOReturn result, void *arg0 )
{
	//IOUSBInterfaceInterface220	**intf = (IOUSBInterfaceInterface220 **) refCon;
	DM2 *dm2 = (DM2*) refCon;

	UInt32 			numBytesRead = (UInt32) arg0;
	UInt32			i,x;

	//printf("Buffer: \n");
	//for(x=0;x<numBytesRead;x++)
	//	printf("0x%04hx ",dm2->buffer[x]);
	//printf("\n");
	
	
	for (i = 0; i < 8; i++) {
		(((UInt8 *)(&dm2->status )) )[i] = dm2->buffer[i];
		// 				printf( " %x", buffer[i] );
	}
	dm2->status.accel_left = dm2->buffer[8];
	dm2->status.accel_right = dm2->buffer[9];
	
	if( memcmp(&dm2->status,&dm2->oldstatus,sizeof( struct dm_status )) != 0 ) 
	{
		dm2->dump_dm2();
		memcpy( &dm2->oldstatus, &dm2->status, sizeof( struct dm_status ));	
	}

	//printf("Async bulk read complete.\n");
	dm2->readData();
//		if (kIOReturnSuccess != result)
//		{
//			printf("error from async bulk read (%08x)\n", result);
//			(void) (*dm2->intf)->USBInterfaceClose(dm2->intf);
//			(void) (*dm2->intf)->Release(dm2->intf);
//			return;
//		}
		
}

void DM2::readData()
{
	IOReturn ioreturn;
	bzero(buffer, sizeof(buffer));
#ifndef USE_ASYNC_IO
		UInt32 numBytesRead = sizeof(buffer);
		int x,i;
		ioreturn = (*intf)->ReadPipe(intf, 1, buffer, &numBytesRead);
		for (i = 0; i < 8; i++) {
			(((UInt8 *)(&this->status )) )[i] = buffer[i];
			// 				printf( " %x", buf[i] );
		}
		this->status.accel_left = buffer[8];
		this->status.accel_right = buffer[9];	
		//	printf("Buffer: ");
		//	for(x=0;x<10;x++)
		//		printf("0x%04hx ",buffer[x]);
		//	printf("\n");
		//	bzero(buffer, sizeof(buffer));
		//	dump_dm2();
		//		usleep(10000);
		//	}while(1);*/
#else
		ioreturn = (*intf)->ReadPipeAsync(intf, 1, buffer, 10, &DM2::ReadCompletion, (void*) this );
		if(ioreturn != kIOReturnSuccess)
		{
			printf("unable to do bulk read (%08x)\n", ioreturn);
			(void) (*intf)->USBInterfaceClose(intf);
			(void) (*intf)->Release(intf);			
		}
#endif
}

void DM2::sendLights()
{
	
	IOReturn ioreturn;
	bzero(buffer, sizeof(buffer));
		
	*((uint16_t *) buffer + 1) = 0xFFFF;
	*((uint16_t *) buffer ) = *((uint16_t *) &leds );
#ifndef USE_ASYNC_IO
	ioreturn = (*intf)->WritePipe(intf, 2, buffer, strlen(buffer));
#else
	ioreturn = (*intf)->WritePipeAsync(intf, 2, buffer, strlen(buffer), WriteCompletion, (void *) this);
#endif

	if (ioreturn != kIOReturnSuccess)
	{
		printf("unable to do bulk write (%08x)\n", ioreturn);
		(void) (*intf)->USBInterfaceClose(intf);
		(void) (*intf)->Release(intf);
	}
		
	//printf("Wrote \"%4X\" (%ld bytes) to bulk endpoint\n", buffer[0], (UInt32) strlen(buffer));
}
void DM2::toggleLED(int ledNum)
{
	ledNum = ledNum % 16; //insted of dying, we're mod'ing if the number is too big
	
	*((uint16_t *) &leds) ^= (1 << ledNum);
	
	/* That code is brilliant, I'm not even sure what it does but I kept
		typing stuff til it worked. No actually, what it does is
		it type casts the struct led_status into a 16bit long int so the 
		OS knows how to operate with it. Then we bitshift a sinde bit
		the number of slots we want. Then we XOR that bit with the original value
		and set it to itself. got it?
		*/
}

void DM2::setLED(int ledNum, bool value)
{
	if(value == 1) //Turn off
		*((uint16_t *) &leds) |= (1 << ledNum);
	else           //Turn on (to 0)
	{
		*((uint16_t *) &leds) = ~*((uint16_t *) &leds);
		*((uint16_t *) &leds) |= (1 << ledNum);
		*((uint16_t *) &leds) = ~*((uint16_t *) &leds);
		
	}
}
void DM2::clearLED()
{
	*((uint16_t *) &leds) = 0xFFFF;	
}

IOUSBInterfaceInterface220 ** DM2::interface()
{
	return intf;
}

IOReturn DM2::USBConfigure()
{
	UInt8				numConf;
    IOReturn				kr;
    IOUSBConfigurationDescriptorPtr	confDesc;
    
    kr = (*dev)->GetNumberOfConfigurations(dev, &numConf);
    if (!numConf)
        return -1;
	printf("Number of configurations: %d\n",numConf); 
    // get the configuration descriptor for index 0
    kr = (*dev)->GetConfigurationDescriptorPtr(dev, 0, &confDesc);
    if (kr)
    {
        printf("\tunable to get config descriptor for index %d (err = %08x)\n", 0, kr);
        return -1;
    }
	
    kr = (*dev)->SetConfiguration(dev, confDesc->bConfigurationValue);
    if (kr)
    {
        printf("\tunable to set configuration to value %d (err=%08x)\n", 0, kr);
        return -1;
    }
    
    return kIOReturnSuccess;
}


IOReturn DM2::FindInterfaces()
{
    IOReturn			kr;
    IOUSBFindInterfaceRequest	request;
    io_iterator_t		iterator;
    io_service_t		usbInterface;
	
	
    IOCFPlugInInterface 	**plugInInterface = NULL;
    //IOUSBInterfaceInterface220 	**intf = intf;
    HRESULT 			res;
    SInt32 			score;
    UInt8			intfClass;
    UInt8			intfSubClass;
    UInt8			intfNumEndpoints;
    int				pipeRef;
#ifndef USE_ASYNC_IO
    UInt32			numBytesRead;
    UInt32			i;
#else
    CFRunLoopSourceRef		runLoopSource;
#endif
	
    request.bInterfaceClass = kIOUSBFindInterfaceDontCare;
    request.bInterfaceSubClass = kIOUSBFindInterfaceDontCare;
    request.bInterfaceProtocol = kIOUSBFindInterfaceDontCare;
    request.bAlternateSetting = kIOUSBFindInterfaceDontCare;
	
    kr = (*dev)->CreateInterfaceIterator(dev, &request, &iterator);
    
    while ( (usbInterface = IOIteratorNext(iterator) ) )
    {
        printf("Interface found.\n");
		
        kr = IOCreatePlugInInterfaceForService(usbInterface, kIOUSBInterfaceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
        kr = IOObjectRelease(usbInterface);				// done with the usbInterface object now that I have the plugin
        if ((kIOReturnSuccess != kr) || !plugInInterface)
        {
            printf("unable to create a plugin (%08x)\n", kr);
            break;
        }
		
        // I have the interface plugin. I need the interface interface
		//ORIG C Version
		// res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID), (LPVOID) &intf);
		
        res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID), (void**) &intf );
        IODestroyPlugInInterface(plugInInterface);			// done with this
		
        if (res || !intf)
        {
            printf("couldn't create an IOUSBInterfaceInterface (%08x)\n", (int) res);
            break;
        }
        
        kr = (*intf)->GetInterfaceClass(intf, &intfClass);
        kr = (*intf)->GetInterfaceSubClass(intf, &intfSubClass);
        
        printf("Interface class %d, subclass %d\n", intfClass, intfSubClass);
        
        // Now open the interface. This will cause the pipes to be instantiated that are 
        // associated with the endpoints defined in the interface descriptor.
        kr = (*intf)->USBInterfaceOpen(intf);
        if (kIOReturnSuccess != kr)
        {
            printf("unable to open interface (%08x)\n", kr);
            (void) (*intf)->Release(intf);
            break;
        }
        
    	kr = (*intf)->GetNumEndpoints(intf, &intfNumEndpoints);
        if (kIOReturnSuccess != kr)
        {
            printf("unable to get number of endpoints (%08x)\n", kr);
            (void) (*intf)->USBInterfaceClose(intf);
            (void) (*intf)->Release(intf);
            break;
        }
        
        printf("Interface has %d endpoints.\n", intfNumEndpoints);
		
        for (pipeRef = 0; pipeRef <= intfNumEndpoints; pipeRef++)
        {
            IOReturn	kr2;
            UInt8	direction;
            UInt8	number;
            UInt8	transferType;
            UInt16	maxPacketSize;
            UInt8	interval;
            char	*message;
            
            kr2 = (*intf)->GetPipeProperties(intf, pipeRef, &direction, &number, &transferType, &maxPacketSize, &interval);
            if (kIOReturnSuccess != kr)
                printf("unable to get properties of pipe %d (%08x)\n", pipeRef, kr2);
            else {
                printf("pipeRef %d: ", pipeRef);
				
                switch (direction) {
                    case kUSBOut:
                        message = "out";
                        break;
                    case kUSBIn:
                        message = "in";
                        break;
                    case kUSBNone:
                        message = "none";
                        break;
                    case kUSBAnyDirn:
                        message = "any";
                        break;
                    default:
                        message = "???";
                }
                printf("direction %s, ", message);
                
                switch (transferType) {
                    case kUSBControl:
                        message = "control";
                        break;
                    case kUSBIsoc:
                        message = "isoc";
                        break;
                    case kUSBBulk:
                        message = "bulk";
                        break;
                    case kUSBInterrupt:
                        message = "interrupt";
                        break;
                    case kUSBAnyType:
                        message = "any";
                        break;
                    default:
                        message = "???";
                }
                printf("transfer type %s, maxPacketSize %d\n", message, maxPacketSize);
            }
        }
        
        // We can now address endpoints 1 through intfNumEndpoints. Or, we can also address endpoint 0,
        // the default control endpoint. But it's usually better to use (*usbDevice)->DeviceRequest() instead.
#ifndef USE_ASYNC_IO
      		
		///testLights();
		
        
        /*
		 numBytesRead = 16;//sizeof(gBuffer) - 1; // leave one byte at the end for NUL termination
						   // kr = (*intf)->ReadPipe(intf, 9, gBuffer, &numBytesRead);
						   //kr = (*intf)->ReadPipe(intf, 1, gBuffer, &numBytesRead);
		 
		 if (kIOReturnSuccess != kr)
		 {
			 printf("unable to do bulk read (%08x)\n", kr);
			 (void) (*intf)->USBInterfaceClose(intf);
			 (void) (*intf)->Release(intf);
			 break;
		 }
		 // The firmware we downloaded echoes the 1's complement of what we wrote, so
		 // complement the buffer contents to see if we get the original data
		 for (i = 0; i < numBytesRead; i++)
		 gBuffer[i] = ~gBuffer[i];
		 
		 printf("Read \"%x\" (%ld bytes) from bulk endpoint\n", gBuffer, numBytesRead);
		 */
#else
        // Just like with service matching notifications, we need to create an event source and add it 
        //  to our run loop in order to receive async completion notifications.
        kr = (*intf)->CreateInterfaceAsyncEventSource(intf, &runLoopSource);
        if (kIOReturnSuccess != kr)
        {
            printf("unable to create async event source (%08x)\n", kr);
            (void) (*intf)->USBInterfaceClose(intf);
            (void) (*intf)->Release(intf);
            break;
        }
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);
        
        printf("Async event source added to run loop.\n");
		
		if (kIOReturnSuccess != kr)
        {
            printf("unable to do async bulk write (%08x)\n", kr);
            (void) (*intf)->USBInterfaceClose(intf);
            (void) (*intf)->Release(intf);
            break;
        }
#endif
      
    //     For this test we just want to use the first interface, so exit the loop.
       break;
   }
    
    return kr;
}

void DM2::init(){
	kern_return_t		kr;

	
	kr = (*dev)->USBDeviceOpenSeize(dev);
	if (kIOReturnSuccess != kr)
	{
		printf("unable to open device: %08x\n", kr);
		(*dev)->Release(dev);
		EXIT_FAILURE;
	}

	kr = USBConfigure();
	if (kIOReturnSuccess != kr)
	{
		printf("unable to configure device: %08x\n", kr);
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		EXIT_FAILURE;
	}
	kr = FindInterfaces();
	if (kIOReturnSuccess != kr)
	{
		printf("unable to find interfaces on device: %08x\n", kr);
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		EXIT_FAILURE;
	}
	
	//	(*intf)->USBInterfaceOpen(intf);
	//	(*intf)->SetPipePolicy(intf,1,8,10);
	//	(*intf)->AbortPipe(intf,1);
	//	(*intf)->ClearPipeStallBothEnds(intf, 2);
	//	(*intf)->USBInterfaceOpenSeize(intf);
	//(*dev)->USBDeviceSuspend(dev,false);
	//	(*dev)->USBDeviceReEnumerate(dev,0);

}

void DM2::dump_dm2()
{

	printf( "DM2 Status:\n" );
	printf( "slider: %d\n", (unsigned int) this->status.slider );
	printf( "wheel: %d, %d\n", (int) this->status.x, (int) this->status.y );
	if( this->status.accel_left != 0 )
		printf( "accel left: %d\n", (int) this->status.accel_left );
	if( this->status.accel_right != 0 )
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
	
	
	printf( "f4 %d\n", this->status.field1 );
	printf( "f5 %d\n", this->status.field2 );
	

}

void DM2::BulkTestDeviceAdded(void *refCon, io_iterator_t iterator)
{
    kern_return_t		kr;
    io_service_t		usbDevice;
    IOCFPlugInInterface 	**plugInInterface=NULL;
    IOUSBDeviceInterface187 	**dev = NULL;
	    HRESULT 		res;
		SInt32 			score;
		UInt16			vendor;
		UInt16			product;
		UInt16			release;
		DM2 *dm2 = (DM2*) refCon;
		
		while ( (usbDevice = IOIteratorNext(iterator)) )
		{
			printf("Bulk test device added.\n");
			
			kr = IOCreatePlugInInterfaceForService(usbDevice, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
			kr = IOObjectRelease(usbDevice);				// done with the device object now that I have the plugin
			if ((kIOReturnSuccess != kr) || !plugInInterface)
			{
				printf("unable to create a plugin (%08x)\n", kr);
				continue;
			}
			
			// I have the device plugin, I need the device interface
			// ORIG C Version
			//res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID)&dev);
			res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID*)&dev);
			IODestroyPlugInInterface(plugInInterface);			// done with this
			
			if (res || !dev)
			{
				printf("couldn't create a device interface (%08x)\n", (int) res);
				continue;
			}
			// technically should check these kr values
			kr = (*dev)->GetDeviceVendor(dev, &vendor);
			kr = (*dev)->GetDeviceProduct(dev, &product);
			kr = (*dev)->GetDeviceReleaseNumber(dev, &release);
			
			if ((vendor != VendorID) || (product != ProductID))// || (release != 1))
			{
				// We should never get here because the matching criteria we specified above
				// will return just those devices with our vendor and product IDs
				printf("found bulk device i didn't want (vendor = %d, product = %d)\n", vendor, product);
				(*dev)->Release(dev);
				continue;
			}
					
			////////////////// ----- Device Verified, now start DM2 object
			dm2->dev = dev;
			dm2->init();
			dm2->testLights();
			dm2->readData();

#ifndef USE_ASYNC_IO
			//kr = (*dm2.dev)->USBDeviceClose(dm2.dev);
			//kr = (*dm2.dev)->Release(dm2.dev);
#endif
		}
}

void DM2::BulkTestDeviceRemoved(void *refCon, io_iterator_t iterator)
{
    kern_return_t	kr;
    io_service_t	obj;
    
    while ( (obj = IOIteratorNext(iterator)) )
    {
        printf("Bulk test device removed.\n");
        kr = IOObjectRelease(obj);
    }
}



