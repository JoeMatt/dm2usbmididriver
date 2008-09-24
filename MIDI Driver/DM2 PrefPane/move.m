// move.m
#import <Foundation/Foundation.h>

int main (int argc, const char * argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	{
		// Make sure we have 3 args (1: path 2: source 3: destination).
		if (argc != 3) return -1;
		NSString * source = [NSString stringWithUTF8String:argv[1]];
		NSString * destination = [NSString stringWithUTF8String:argv[2]];
		
		source = [source stringByStandardizingPath];
		destination = [destination stringByStandardizingPath];
		
		printf("Moving \"%s\" to \"%s\"...",[source UTF8String],[destination UTF8String]);
		
		NSFileManager * manager = [NSFileManager defaultManager];
		if (![manager fileExistsAtPath:source])
		{
			printf("failed\n***No source file at \"%s\".\n",[source UTF8String]);
			return -1;
		}
		
		[manager movePath:source toPath:destination handler:nil];
		
		printf("done\n");
	}
    [pool release];
    return 0;
}