//
//  DM2Preview.m
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 6/29/08.
//  Copyright 2008 Joe Mattiello. All rights reserved.
//

#import "DM2Preview.h"
//#import <Quartz/Quartz.h>

@implementation DM2Preview

- (void)awakeFromNib
{
	[myWindow setLevel:NSFloatingWindowLevel];
}

 - (IBAction)setAlwaysOnTop:(id)sender
{
	BOOL shouldBeOnTop = [alwaysOnTopButton state];
	
	if(!shouldBeOnTop)
	{
		[myWindow setLevel: NSFloatingWindowLevel];
	}
	else
	{
		[myWindow setLevel:NSNormalWindowLevel];
	}
	[alwaysOnTopButton setState:!shouldBeOnTop];
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)proposedFrameSize
{
    // this choses the minimum, > choses the maximum
	float ratio = 3.0/4.0;
	
    if (proposedFrameSize.width < proposedFrameSize.height * ratio) {
        proposedFrameSize.width = proposedFrameSize.height * 1.0/ratio;
    } else {
        proposedFrameSize.height = proposedFrameSize.width * ratio;
    }
	
    return proposedFrameSize;
}

@end
