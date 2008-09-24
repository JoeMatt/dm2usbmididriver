//
//  NSStringAdditions.m
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 6/23/08.
//  Copyright 2008 Joe Mattiello. All rights reserved.
//

#import "NSStringAdditions.h"


@implementation NSString (rot13)

+ (NSString *)rot13:(NSString *)theText {
    NSMutableString *holder = [[NSMutableString alloc] init];
    unichar theChar;
    int i;
    
    for(i = 0; i < [theText length]; i++) {
        theChar = [theText characterAtIndex:i];
        if(theChar <= 122 && theChar >= 97) {
            if(theChar + 13 > 122)
                theChar -= 13;
            else 
                theChar += 13;
            [holder appendFormat:@"%C", (char)theChar];
            
            
        } else if(theChar <= 90 && theChar >= 65) {
            if((int)theChar + 13 > 90)
                theChar -= 13;
            else
                theChar += 13;
            
            [holder appendFormat:@"%C", theChar];
			
        } else {
            [holder appendFormat:@"%C", theChar];
        }
    }
    
    return [NSString stringWithString:holder];
}

@end
