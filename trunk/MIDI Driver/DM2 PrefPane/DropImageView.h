//
//  DropImageView.h
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 2/13/08.
//  Copyright 2008 Joe Mattiello. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface DropImageView : NSImageView {
	NSString * fileLocation;
	NSArray * dragTypes;
	
	NSString * licenseXMLString;
	
	id target;
	SEL action;
}
- (void)setAction:(SEL)anAction;
- (void)setTarget:(id)aTarget;

- (NSString *)fileLocation;
- (NSString *)licenseXMLString;
- (void)registrationValid;

@end
 