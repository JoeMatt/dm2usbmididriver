//
//  NSApplicationAdditions.h
//  TRKit
//

#import <Cocoa/Cocoa.h>


@interface NSApplication (TRAdditions)
+ (NSString *)applicationVersion;
- (NSString *)applicationVersion;
+ (NSString *)applicationIdentifier;
- (NSString *)applicationIdentifier;
+ (NSString *)applicationName;
- (NSString *)applicationName;
@end

static __inline__ int RandomIntBetween(int a, int b)
{
    int range = b - a < 0 ? b - a - 1 : b - a + 1; 
    int value = (int)(range * ((float)random() / (float) LONG_MAX));
    return value == range ? a : a + value;
}

static __inline__ float RandomFloatBetween(float a, float b)
{
    return a + (b - a) * ((float)random() / (float) LONG_MAX);
}