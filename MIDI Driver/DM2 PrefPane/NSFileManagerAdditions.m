//
//  NSFileManagerAdditions.m
//  DM2USBMIDIDriver
//
//  Created by Joseph Mattiello on 9/1/07.
//  Copyright 2007 Joe Mattiello. All rights reserved.
//

//
//  NSFileManagerAdditions.m
//  TRKit
//

#import "NSFileManagerAdditions.h"
#import "NSApplicationAdditions.h"
#import <Carbon/Carbon.h>
#import <Security/Security.h>

static AuthorizationRef authorizationRef = NULL;

@implementation NSFileManager (TRAdditions)

- (NSString *)newTmpFilePath
{
	NSString * tmpDirectory = NSTemporaryDirectory();
	NSString * identifier = [NSApp applicationIdentifier];
	
	if (tmpDirectory == nil || identifier == nil) return nil;
	
	for (;;)
	{
		NSString * tmpFileName = [NSString stringWithFormat:@"%@_%i",identifier,RandomIntBetween(0,100000)];
		NSString * path = [tmpDirectory stringByAppendingPathComponent:tmpFileName];
		path = [path stringByStandardizingPath];
		
		if ([self fileExistsAtPath:path])
		{
			continue;
		}
		else
		{
			// 'Touch' a file here so that it guarentees that another won't be created (rare chance).
			//[self createFileAtPath:path contents:nil attributes:nil];
			return path;
		}
	}
}

- (BOOL)authorizedMovePath:(NSString *)source toPath:(NSString *)destination
{
	NSBundle * trkitBundle = [NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"];//[NSBundle bundleForClass:NSClassFromString(@"TRIntegration")];
	NSString * trkitResourcePath = [trkitBundle resourcePath];
	NSString * trkitMoveUtilityPath = [trkitResourcePath stringByAppendingPathComponent:@"move"];
	
	if (![self fileExistsAtPath:trkitMoveUtilityPath])
	{
		NSLog(@"Cannot find move utility.");
		return NO;
	}
	
	/* The move utlity exists, we can now procede. */
	OSStatus status;
	
	if (authorizationRef == NULL)
	{
		// Get Authorization.
		status = AuthorizationCreate(NULL,
									 kAuthorizationEmptyEnvironment,
									 kAuthorizationFlagDefaults,
									 &authorizationRef);
	}
	else
	{
		status = noErr;
	}
	
	// Make sure we have authorization.
	if (status != noErr)
	{
		NSLog(@"Could not get authorization, failing.");
		return NO;
	}
	
	// Set up the arguments.
	char * args[2];
	args[0] = (char *)[[source stringByStandardizingPath] UTF8String];
	args[1] = (char *)[[destination stringByStandardizingPath] UTF8String];
	args[2] = NULL;
	
	status = AuthorizationExecuteWithPrivileges(authorizationRef,
												[[trkitMoveUtilityPath stringByStandardizingPath] UTF8String],
												0, args, NULL);
	
	if (status != noErr)
	{
		NSLog(@"Could not move file.");
		return NO;
	}
	else
	{
		return YES;
	}
	
	return NO;
}

- (BOOL)authorizedCopyPath:(NSString *)source toPath:(NSString *)destination
{
	NSString * tempFile = [self newTmpFilePath];
	[self copyPath:source toPath:tempFile handler:nil];
	[self authorizedMovePath:tempFile toPath:destination];
}

@end
