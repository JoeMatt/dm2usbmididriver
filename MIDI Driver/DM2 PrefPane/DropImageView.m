//
//  DropImageView.m
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 2/13/08.
//  Copyright 2008 Joe Mattiello. All rights reserved.
//

#import "DropImageView.h"
#import "Carbon/Carbon.h"
#import "NSStringAdditions.h"

@implementation DropImageView

/* <Alloc/De-alloc> */

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];

	if(self)
	{
		dragTypes = [[NSArray alloc] initWithObjects:
					 NSFileContentsPboardType,
					 NSTIFFPboardType, 
					 NSFilenamesPboardType,
					 NSRTFDPboardType,
					 NSURLPboardType,
					 nil];
		
		[self setImageFrameStyle:NSImageFrameGrayBezel];
		[self setImageAlignment:NSImageAlignCenter];
		[self setImageScaling:NSScaleToFit];
		//Drag from safari candidates that still have valid xml are, com.apple.webarchive, "NeXT RTFD pasteboard type"
		[self registerForDraggedTypes:dragTypes];
	#if DEBUG	
		NSLog(@"DropImageView initialized");
	#endif
    }
	return self;
}

- (void)dealloc
{
    [self unregisterDraggedTypes];
    [super dealloc];
}

/* </Alloc/De-alloc> */

/* <DragNDrop> */
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    if ((NSDragOperationGeneric & [sender draggingSourceOperationMask]) 
		== NSDragOperationGeneric)
    {
        //this means that the sender is offering the type of operation we want
        //return that we want the NSDragOperationGeneric operation that they 
		//are offering
		SetThemeCursor(1);

        return NSDragOperationGeneric;
    }
    else
    {
        //since they aren't offering the type of operation we want, we have 
		//to tell them we aren't interested
        return NSDragOperationNone;
    }
}

- (void)draggingExited:(id <NSDraggingInfo>)sender
{
    //we aren't particularily interested in this so we will do nothing
    //this is one of the methods that we do not have to implement
	SetThemeCursor(0);
}

- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender
{
    if ((NSDragOperationGeneric & [sender draggingSourceOperationMask]) 
		== NSDragOperationGeneric)
    {
		//[[NSCursor disappearingItemCursor] set];
        //this means that the sender is offering the type of operation we want
        //return that we want the NSDragOperationGeneric operation that they 
		//are offering
        return NSDragOperationGeneric;
    }
    else
    {
        //since they aren't offering the type of operation we want, we have 
		//to tell them we aren't interested
        return NSDragOperationNone;
    }
}

- (void)draggingEnded:(id <NSDraggingInfo>)sender
{
    //we don't do anything in our implementation
    //this could be ommitted since NSDraggingDestination is an infomal
	//protocol and returns nothing
}

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
    return YES;
}

- (void)concludeDragOperation:(id <NSDraggingInfo>)sender
{
    //re-draw the view with our new data
	SetThemeCursor(0);
    [self setNeedsDisplay:YES];
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{
    NSPasteboard *paste = [sender draggingPasteboard];
	//gets the dragging-specific pasteboard from the sender

	//a list of types that we can accept	
    NSString *desiredType = [paste availableTypeFromArray:dragTypes];
    NSData *carriedData = [paste dataForType:desiredType];
	
    if (nil == carriedData)
    {
        //the operation failed for some reason
        NSRunAlertPanel(@"Paste Error", @"Sorry, but the paste operation failed", 
						nil, nil, nil);
        return NO;
    }
    else
    {
        //the pasteboard was able to give us some meaningful data
        if ([desiredType isEqualToString:NSTIFFPboardType])
        {
            //we have TIFF bitmap data in the NSData object
            NSImage *newImage = [[NSImage alloc] initWithData:carriedData];
            [self setImage:newImage];
            [newImage release];    
			//we are no longer interested in this so we need to release it
			NSData * xmlData = [paste dataForType:@"com.apple.flat-rtfd"];
			
			if(xmlData)
			{
				NSLog(@"Found RTF Data");
				/* Looking for byte pattern 70 65 6e 31 35 which is "pen15" in ASCII */
				
				Byte * bytes = (Byte*)[xmlData bytes];
				int length = [xmlData length],
				startLocation=-1,
				endLocation=-1,
				i;
				
				for(i=0; i+4<length; i++)
				{
					if(bytes[i] == 0x70)
					{
						if( bytes[i+1] == 0x65 && bytes[i+2] == 0x6E && bytes[i+3] == 0x31 && bytes[i+4] == 0x35 )
						{
							startLocation = i+5;
							break;
						}
					}
				}
				
				if(startLocation != -1)
				{
					NSLog(@"Found start of XML");
					/* Looking for byte pattern 35 31 6E 65 70   which is "51nep" in ASCII */
					for(i=startLocation; i+4<length; i++)
					{
						if(bytes[i] == 0x35)
						{
							if( bytes[i+1] == 0x31 && bytes[i+2] == 0x6E && bytes[i+3] == 0x65 && bytes[i+4] == 0x70)
							{
								endLocation = i;
								break;
							}
						}
					}
					
					if(endLocation != -1)
					{
						NSLog(@"Found XML at %i to %i", startLocation, endLocation);
						NSRange xmlStringRange = NSMakeRange(startLocation, endLocation-startLocation);
						
						NSData * xmlRawData = [xmlData subdataWithRange:xmlStringRange];
						NSString * xmlString = [[NSString alloc] initWithData:xmlRawData encoding:NSASCIIStringEncoding];
						if(xmlString)
							licenseXMLString = [[NSString rot13:xmlString] retain];
					}
				}
				
			}
        
		}
        else if ([desiredType isEqualToString:NSFilenamesPboardType])  //This is a file drag, and doesn't need to be handled seperately for the XML file
        {
            //we have a list of file names in an NSData object
            NSArray *fileArray = 
			[paste propertyListForType:@"NSFilenamesPboardType"];
			//be caseful since this method returns id.  
			//We just happen to know that it will be an array.
            NSString *path = [fileArray objectAtIndex:0];
			//assume that we can ignore all but the first path in the list
            NSImage *newImage = [[NSImage alloc] initWithContentsOfFile:path];
			
            if (nil == newImage)
            {
                //we failed for some reason
                NSRunAlertPanel(@"File Reading Error", 
								[NSString stringWithFormat:
								 @"Sorry, but I failed to open the file at \"%@\"",
								 path], nil, nil, nil);
                return NO;
            }
            else
            {
                //newImage is now a new valid image
				fileLocation = path;
                [self setImage:newImage];
            }
            [newImage release];
        }
        else
        {
            //this can't happen
            NSAssert(NO, @"This can't happen");
            return NO;
        }
    }
		
	//Perform target operation after successful drag
	if (target)
	{
		[target performSelector:action withObject:self];
	}
    [self setNeedsDisplay:YES];    //redraw us with the new image
    return YES;
}

/* </DragNDrop> */

/* IB Integration */
- (void)setTarget:(id)aTarget
{
	target = aTarget;
}

- (void)setAction:(SEL)anAction
{
	action = anAction;
}

- (NSString *)fileLocation
{
	return fileLocation;
}

- (NSString *)licenseXMLString
{
	return licenseXMLString;
}

- (void)registrationValid
{
//	[[self window] close];
}

@end
