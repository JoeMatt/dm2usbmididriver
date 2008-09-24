//
//  NSApplicationAdditions.m
//  TRKit
//

#import "NSApplicationAdditions.h"


@implementation NSApplication (TRAdditions)

+ (NSString *)applicationVersion
{
	return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
}

- (NSString *)applicationVersion
{
	return [[self class] applicationVersion];
}

+ (NSString *)applicationIdentifier
{
	return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"];
}

- (NSString *)applicationIdentifier
{
	return [[self class] applicationIdentifier];
}

+ (NSString *)applicationName
{
	return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleExecutable"];
}

- (NSString *)applicationName
{
	return [[self class] applicationName];
}

@end
