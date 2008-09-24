//
//  NSFileManagerAdditions.h
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 9/1/07.
//  Copyright 2007 Joe Mattiello. All rights reserved.
//

//
//  NSFileManagerAdditions.h
//  TRKit
//

#import <Cocoa/Cocoa.h>


@interface NSFileManager (TRAdditions)
- (NSString *)newTmpFilePath;
- (BOOL)authorizedMovePath:(NSString *)source toPath:(NSString *)destination;
- (BOOL)authorizedCopyPath:(NSString *)source toPath:(NSString *)destination;
@end
