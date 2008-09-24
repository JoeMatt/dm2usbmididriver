//
//  DM2Preview.h
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 6/29/08.
//  Copyright 2008 Joe Mattiello. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface DM2Preview : NSObject {
		IBOutlet NSWindow * myWindow;
	IBOutlet NSMenuItem * alwaysOnTopButton;
}

- (IBAction)setAlwaysOnTop:(id)sender;

@end
