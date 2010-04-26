#import "DM2_PreferencesPref.h"
#import <Foundation/NSString.h>
#import <Foundation/Foundation.h>
#import "DropImageView.h"
#import <AppKit/NSBitmapImageRep.h>
#import <ApplicationServices/ApplicationServices.h>
#import "NSApplicationAdditions.h"
#import "NSStringAdditions.h"

#ifdef DEBUG
	#define DEBUGLog(a)				NSLog(@#a)
	#define IGNORE_REGISTRATION
#else
	#define DEBUGLog(a)
#endif



@implementation DM2_PreferencesPref

- (void)sendDriverMessage:(CFStringRef)message
{
	CFNotificationCenterRef center;
	center = CFNotificationCenterGetDistributedCenter();
	CFNotificationCenterPostNotification(center,
										 message, CFSTR("com.joemattiello.driver.dm2"), NULL, TRUE);
}

- (IBAction)saveButtonClicked:(id)sender
{
	CFPreferencesAppSynchronize(appID);
	[self sendDriverMessage:CFSTR("Preferences Changed") ];	
}

- (IBAction)helpButtonClicked:(id)sender
{
	
}

- (id)initWithBundle:(NSBundle *)bundle
{
    if ( ( self = [super initWithBundle:bundle] ) != nil ) {
        appID = CFSTR("com.joemattiello.driver.dm2");
    }
	
    return self;
}
- (NSPreferencePaneUnselectReply)shouldUnselect
{
	CFPreferencesAppSynchronize(appID);
	[self sendDriverMessage:CFSTR("Preferences Changed") ];	
	return NSUnselectNow;
}
- (void)mainViewDidLoad
{

    CFPropertyListRef value;
	
	//Craate updater
	updater = [Updater new];
	versionString = [[[NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"] infoDictionary] objectForKey:@"CFBundleVersion"];

	/* Set version string */
	[versionLabel setStringValue:[NSString stringWithFormat:@"Version: %@",versionString]];
	
    /* Initialize the checkbox */
    value = CFPreferencesCopyAppValue( CFSTR("bank1StickyButtons"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank1StickyButtonsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank1StickyButtonsCheckbox setState:NO];
    }
	
	value = CFPreferencesCopyAppValue( CFSTR("bank2StickyButtons"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank2StickyButtonsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank2StickyButtonsCheckbox setState:NO];
    }
	
	value = CFPreferencesCopyAppValue( CFSTR("bank3StickyButtons"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank3StickyButtonsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank3StickyButtonsCheckbox setState:NO];
    }
	
	value = CFPreferencesCopyAppValue( CFSTR("bank4StickyButtons"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank4StickyButtonsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank4StickyButtonsCheckbox setState:NO];
    }
	
	value = CFPreferencesCopyAppValue( CFSTR("bank1InvertLeds"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank1InvertLedsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank1InvertLedsCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank2InvertLeds"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank2InvertLedsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank2InvertLedsCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank3InvertLeds"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank3InvertLedsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank3InvertLedsCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank4InvertLeds"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank4InvertLedsCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank4InvertLedsCheckbox setState:NO];
    }
	/** Displays MIDI Clock Setting **/
	value = CFPreferencesCopyAppValue( CFSTR("bank1DisplaysMIDIClock"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank1DisplaysMIDIClockCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank1DisplaysMIDIClockCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank2DisplaysMIDIClock"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank2DisplaysMIDIClockCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank2DisplaysMIDIClockCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank3DisplaysMIDIClock"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank3DisplaysMIDIClockCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank3DisplaysMIDIClockCheckbox setState:NO];
    }
	value = CFPreferencesCopyAppValue( CFSTR("bank4DisplaysMIDIClock"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [bank4DisplaysMIDIClockCheckbox setState:CFBooleanGetValue(value)];
    } else {
        [bank4DisplaysMIDIClockCheckbox setState:NO];
    }
	/** Who Controls LEDs ***/
	value = CFPreferencesCopyAppValue( CFSTR("bank1WhoControlsLEDs") , appID );
	int row = 0;
	if( value && CFStringCompare((CFStringRef) value,CFSTR("MIDI Messages Only"),0) == 0)
	{
		row = 1;
	}
	else if( value && CFStringCompare(value,CFSTR("Driver & MIDI Messages"),0) == 0)
	{
		row = 2;
	}
	[bank1WhoControlsLEDsPopUpButton selectItemAtIndex:row];
	
	value = CFPreferencesCopyAppValue( CFSTR("bank2WhoControlsLEDs") , appID );
	row = 0;
	if( value && CFStringCompare((CFStringRef) value,CFSTR("MIDI Messages Only"),0) == 0)
	{
		row = 1;
	}
	else if( value && CFStringCompare(value,CFSTR("Driver & MIDI Messages"),0) == 0)
	{
		row = 2;
	}
	[bank2WhoControlsLEDsPopUpButton selectItemAtIndex:row];
	
	value = CFPreferencesCopyAppValue( CFSTR("bank3WhoControlsLEDs") , appID );
	row = 0;
	if( value && CFStringCompare((CFStringRef) value,CFSTR("MIDI Messages Only"),0) == 0)
	{
		row = 1;
	}
	else if( value && CFStringCompare(value,CFSTR("Driver & MIDI Messages"),0) == 0)
	{
		row = 2;
	}
	[bank3WhoControlsLEDsPopUpButton selectItemAtIndex:row];
	
	value = CFPreferencesCopyAppValue( CFSTR("bank4WhoControlsLEDs") , appID );
	row = 0;
	if( value && CFStringCompare((CFStringRef) value,CFSTR("MIDI Messages Only"),0) == 0)
	{
		row = 1;
	}
	else if( value && CFStringCompare(value,CFSTR("Driver & MIDI Messages"),0) == 0)
	{
		row = 2;
	}
	[bank4WhoControlsLEDsPopUpButton selectItemAtIndex:row];
	
	/** Advanced **/
	value = CFPreferencesCopyAppValue( CFSTR("midiClockResolution") , appID );
	row = 0;
	if( value && CFStringCompare((CFStringRef) value,CFSTR("32nd"),0) == 0)
	{
		row = 1;
	}
	else if( value && CFStringCompare(value,CFSTR("1/4"),0) == 0)
	{
		row = 2;
	}
	[midiClockResolutionMatrix selectCellAtRow:row column:0];
	
	value = CFPreferencesCopyAppValue( CFSTR("autoUpdate"),  appID );
    if ( value && CFGetTypeID(value) == CFBooleanGetTypeID()  ) {
        [checkAutomaticallyCheckbox setState:CFBooleanGetValue(value)];
		if(CFBooleanGetValue(value) == TRUE)
		   {
			[checkForUpdateButton setEnabled:NO];
			//[NSThread detachNewThreadSelector:@selector(checkForUpdates:) toTarget:updater withObject:self];
			//[updater checkForUpdates:self];
		   }
    } else {
        [checkAutomaticallyCheckbox setState:NO];
		[checkForUpdateButton setEnabled:YES];
    }
 
	/* END read preferences */
	bank1Tab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"bank1"]];
	bank2Tab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"bank2"]];
	bank3Tab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"bank3"]];
	bank4Tab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"bank4"]];
	statusTab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"status"]];
	aboutTab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"about"]];
	traktorTab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"traktor"]];
//	advancedTab = [tabView tabViewItemAtIndex:[tabView indexOfTabViewItemWithIdentifier:@"advanced"]];
	
	[softwareModeButton setAutoenablesItems:NO];

	// Set software Mode
	value = CFPreferencesCopyAppValue( CFSTR("softwareMode"),  appID );
	if(value)
	{	
		[self changeModeTo:(NSString *)value];
		[softwareModeButton selectItemWithTitle:(NSString *)value];
	}
	else
	{
			[softwareModeButton selectItemAtIndex:0];
		[self changeModeTo:@"Generic MIDI"];
	}
	
	/* Load info Quartz file */
	[self loadQuartz:self];

	/* Fill in readme textview */
	[self openReadme:self];
	/* Check for updates */
	[self checkIfPluginIsUpToDate:self];
	
    if ( value ) CFRelease(value);
	
	[[NSWindow alloc] init] ;
}
/**** Bank Buttons Start ****/
- (IBAction)bank1StickyButtonsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank1StickyButtons"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank1StickyButtons"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank2StickyButtonsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank2StickyButtons"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank2StickyButtons"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank3StickyButtonsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank3StickyButtons"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank3StickyButtons"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank4StickyButtonsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank4StickyButtons"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank4StickyButtons"),
								  kCFBooleanFalse, appID );
}

- (IBAction)displaysMIDIClockCheckboxClicked:(id)sender
{
	NSButton * checkbox = sender;
	bool value = [checkbox state];
	
	NSString * containerTabName = [[tabView selectedTabViewItem] identifier];
	NSString * key = [NSString stringWithFormat:@"%@DisplaysMIDIClock",containerTabName];
		
	if(value)
		CFPreferencesSetAppValue( (CFStringRef)key,
									  kCFBooleanTrue, appID);
	else
		CFPreferencesSetAppValue( (CFStringRef)key,
								  kCFBooleanFalse, appID);
}

- (IBAction)whoControlsLEDsPopUpButtonChanged:(id)sender
{
	NSPopUpButton * popUpButton = sender;
	NSString * value = [popUpButton titleOfSelectedItem];
	
	NSString * containerTabName = [[tabView selectedTabViewItem] identifier];
	NSString * key = [NSString stringWithFormat:@"%@WhoControlsLEDs",containerTabName];

	if(value)
		CFPreferencesSetAppValue( (CFStringRef)key,
								 (CFStringRef) value, appID);
	else
		CFPreferencesSetAppValue( (CFStringRef)key,
								  CFSTR("Driver Only"), appID);
}

- (IBAction)scratchRingBumpIgnorePopUpButtonChanged:(id)sender
{
	NSPopUpButton * popUpButton = sender;
	int value = [popUpButton indexOfSelectedItem];
	
	NSString * containerTabName = [[tabView selectedTabViewItem] identifier];
	NSString * key = [NSString stringWithFormat:@"%@ScratchRingBumpIgnore",containerTabName];
	
	if(value==-1)
		value = 0;
	
	CFPreferencesSetAppValue( (CFStringRef)key,
								CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &value), appID);	
}

#pragma mark -
#pragma mark LED Check boxes
	/******** Invert LEDS *************/
- (IBAction)bank1InvertLedsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank1InvertLeds"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank1InvertLeds"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank2InvertLedsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank2InvertLeds"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank2InvertLeds"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank3InvertLedsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank3InvertLeds"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank3InvertLeds"),
								  kCFBooleanFalse, appID );
}
- (IBAction)bank4InvertLedsCheckboxClicked:(id)sender
{
    if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("bank4InvertLeds"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("bank4InvertLeds"),
								  kCFBooleanFalse, appID );
}

/******** Bank Buttons End *******/
/******** Advanced Page ***********/
- (IBAction)midiClockResolutionMatrixChanged:(id)sender
{
	NSMatrix * matrix = (NSMatrix *)sender;
	NSString * setting;
	int row = [matrix selectedRow];
	switch(row)
	{
		//case 0:
		//	setting = [NSString stringWithString:@"16th"];
		//	break;
		case 1:
			setting = [NSString stringWithString:@"32nd"];
			break;
		case 2:
			setting = [NSString stringWithString:@"1/4"];
			break;
		default:
			setting = [NSString stringWithString:@"16th"];
	}
	CFPreferencesSetAppValue( CFSTR("midiClockResolution"),
							 (CFStringRef)setting,appID);
	if(setting)
		[setting release];
}

/********* About Page *************/
- (IBAction)contactAuthorButtonClicked:(id)sender
{
	NSString *stringURL = @"mailto:dm2@joemattiello.com";
	[[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:stringURL]];
}
- (IBAction)visitHomepageButtonClicked:(id)sender
{
	NSString *stringURL = @"http://www.joemattiello.com/dm2/";
	[[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:stringURL]];
}

- (IBAction)donateButtonClicked:(id)sender
{
	NSString *stringURL = @"http://www.joemattiello.com/dm2/";
	[[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:stringURL]];
}

/********** Global Page **********/

- (IBAction)checkForUpdateButtonClicked:(id)sender
{
	[updater checkForUpdates:self];
}
- (IBAction)clearLEDsButtonClicked:(id)sender
{
	[self sendDriverMessage:CFSTR("Clear All LEDs")];
}
- (IBAction)resetCalibrationButtonClicked:(id)sender
{
	[self sendDriverMessage:CFSTR("Reset Calibration") ];
}
- (IBAction)checkAutomaticallyCheckboxClicked:(id)sender
{
	if ( [sender state] )
	{
		[checkForUpdateButton setEnabled:NO];
        CFPreferencesSetAppValue( CFSTR("autoUpdate"),
								  kCFBooleanTrue, appID );
    }
	else
    {
		[checkForUpdateButton setEnabled:YES];
		CFPreferencesSetAppValue( CFSTR("autoUpdate"),
								  kCFBooleanFalse, appID );
	}
}
- (IBAction)softwareModeComboBoxChanged:(id)sender
{
	NSString * currentSelection = [softwareModeButton titleOfSelectedItem];
	CFPreferencesSetAppValue( CFSTR("softwareMode"),
							  currentSelection, appID );
	[self changeModeTo:currentSelection];
}
- (IBAction)resetInterfaceButtonClicked:(id)sender
{
	[self sendDriverMessage:CFSTR("Reset Interface") ];
}
- (IBAction)growlSupportCheckboxClicked:(id)sender
{
	if ( [sender state] )
        CFPreferencesSetAppValue( CFSTR("growlSuport"),
								  kCFBooleanTrue, appID );
    else
        CFPreferencesSetAppValue( CFSTR("growlSupport"),
								  kCFBooleanFalse, appID );
}

// Update with README file
- (void)openReadme:(id)sender
{
	CFBundleRef prefBundle = CFBundleGetBundleWithIdentifier(CFSTR("com.joemattiello.driver.dm2.prefpanel"));
	CFStringRef readmeFile = CFSTR("Read me");
	CFStringRef extension = CFSTR("rtfd");
	
	CFURLRef fileName = CFBundleCopyResourceURL(prefBundle, readmeFile, extension, NULL);
	NSString * filePath = (NSString *)CFURLCopyFileSystemPath(fileName, kCFURLPOSIXPathStyle);
	/* The next line imports the Graphics too, which I don't want... */
	//[readmeTextView readRTFDFromFile:filePath];
	
	/* ..., so go inside the RTFD bundle and grab just the RTF file */
	NSData *rtfData = [NSData dataWithContentsOfFile:[NSString stringWithFormat:@"%@/TXT.rtf",filePath]];
	[readmeTextView replaceCharactersInRange:NSMakeRange(0, [[readmeTextView string] length]) withRTF:rtfData];
}

// Change GUI
- (void)changeModeTo:(NSString*)mode
{	
	if([mode isEqualToString:@"Traktor"])
	{
		if([tabView indexOfTabViewItemWithIdentifier:@"bank1"] != NSNotFound)
		{
			[bank1Tab retain];
			[tabView removeTabViewItem:bank1Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank2"] != NSNotFound) 
		{
			[bank2Tab retain];
			[tabView removeTabViewItem:bank2Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank3"] != NSNotFound) 
		{
			[bank3Tab retain];
			[tabView removeTabViewItem:bank3Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank4"] != NSNotFound) 
		{
			[bank4Tab retain];
			[tabView removeTabViewItem:bank4Tab];			
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"traktor"] != NSNotFound)
		{
			[traktorTab retain];
			[tabView removeTabViewItem:traktorTab];
		}

		[tabView insertTabViewItem:traktorTab atIndex:1];
		
	}		
	else if([mode isEqualToString:@"Generic MIDI with Banks"] || [mode isEqualToString:@"Mixxx"] || [mode isEqualToString:@"Generic MIDI"])
	{
		if([tabView indexOfTabViewItemWithIdentifier:@"bank1"] != NSNotFound)
		{
			[bank1Tab retain];
			[tabView removeTabViewItem:bank1Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank2"] != NSNotFound) 
		{
			[bank2Tab retain];
			[tabView removeTabViewItem:bank2Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank3"] != NSNotFound) 
		{
			[bank3Tab retain];
			[tabView removeTabViewItem:bank3Tab];
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"bank4"] != NSNotFound) 
		{
			[bank4Tab retain];
			[tabView removeTabViewItem:bank4Tab];			
		}
		if([tabView indexOfTabViewItemWithIdentifier:@"traktor"] != NSNotFound)
		{
			[traktorTab retain];
			[tabView removeTabViewItem:traktorTab];
		}		
		
		if( [mode isNotEqualTo:@"Mixxx"] && [mode isNotEqualTo:@"Generic MIDI"])
		{
			[tabView insertTabViewItem:bank4Tab atIndex:1];
			[tabView insertTabViewItem:bank3Tab atIndex:1];
			[tabView insertTabViewItem:bank2Tab atIndex:1];
		}
		[tabView insertTabViewItem:bank1Tab atIndex:1];
	}	
}

- (void)loadQuartz:(id)sender
{
	SInt32 MacVersion;
	
	if (Gestalt(gestaltSystemVersion, &MacVersion) == noErr)
	{
		if (MacVersion < 0x1040)
		{
			[osWarningTextField setHidden:NO];
			return;
		}
		/* Load the Quartz framework on 10.4+ */
		NSBundle * quartz = [NSBundle bundleWithIdentifier:@"com.apple.quartzframework"];
		if(!quartz)
			quartz = [NSBundle bundleWithPath:@"/System/Library/Frameworks/Quartz.framework"];

		if( [quartz isLoaded] )
			NSLog(@"Quartz already loaded");
		else if( quartz == NULL || ![quartz load] )
		{
			NSLog(@"Could not load Quartz.framework");
			[osWarningTextField setStringValue:@"Error loading Quartz."];
			[osWarningTextField setHidden:NO];
			return;
		}
		else
			NSLog(@"Loaded Quartz.framework");
		
		Class QCViewPtr = NSClassFromString(@"QCView");

		id qtzview = [[QCViewPtr alloc] initWithFrame:[[statusTab view] frame]];
		
		//Class QCView = NSClassFromString(@"QCView");
		//Class * qtzview = [[[quartz classNamed:@"QCView"] alloc] initWithFrame:[[statusTab view] frame]];
		//QCView * qtzview = [[QCView alloc] initWithFrame:[[statusTab view] frame]];
		
		NSString * path = [[NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"] bundlePath];
		path = [path stringByAppendingString:@"/Contents/Resources/DM2.qtz"];
		
		/* quartz framework can't be linked against for 10.3 compatability, so performSelector: is used after dynamic loading */
		if(![qtzview performSelector:@selector(loadCompositionFromFile:) withObject:path])
		{
			NSLog(@"Could not load Quartz File");
			[osWarningTextField setStringValue:@"Could not load Quartz file."];
			[osWarningTextField setHidden:NO];
			return;
		}

		NSNumber * yes = [[NSNumber alloc] initWithInt:1];
		[qtzview performSelector:@selector(setAutostartsRendering:) withObject:yes];
		[[statusTab view] addSubview:qtzview];
	}
}
/********* Traktor Page *********/
- (IBAction)exportTraktorButtonClicked:(id)sender
{
	NSSavePanel *mySavePanel;
	int runResult;
	
	NSString * path = [[NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"] bundlePath];
	path = [path stringByAppendingString:@"/Contents/Resources/DM2.tks"];
	NSFileWrapper * tksFile = [[NSFileWrapper alloc] initWithPath:path];
		
	/* create or get the shared instance of NSSavePanel */
	mySavePanel = [NSSavePanel savePanel];
	
	/* set up new attributes */
	[mySavePanel setRequiredFileType:@"tks"];
	
	/* display the NSSavePanel */
	runResult = [mySavePanel runModalForDirectory:NSHomeDirectory() 
											 file:@"DM2.tks"];
	
	/* if successful, save file under designated name */
	if (runResult == NSOKButton) {
		if (![tksFile writeToFile:[mySavePanel filename] 
					   atomically:YES 
				  updateFilenames:NO])
			NSBeep();
	}
}	

- (void)checkIfPluginIsUpToDate:(id)sender
{
	NSString * path = [[NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"] bundlePath];
	path = [path stringByAppendingString:@"/Contents/Resources/DM2USBMIDIDriver.plugin"];
	
	NSBundle * internalBundle = [NSBundle bundleWithPath:path];
	if( internalBundle == nil)
	{
		NSLog(@"Error: Can not find internal plugin");
		return;
	}
	if(path)
		CFRelease(path);
	
	path = [NSString stringWithString:@"/Library/Audio/MIDI Drivers/DM2USBMIDIDriver.plugin"];
	NSBundle * installedBundle = [NSBundle bundleWithPath:path];
	if( installedBundle == nil)
	{
		CFRelease(internalBundle);
		NSLog(@"Plugin not installed, prompting to install");
		[self copyPluginToSystem:self];
	}
	else
	{
		NSLog(@"Checking version of installed plugin");
		
	//	NSString * internalBundleVersion = [[internalBundle objectForInfoDictionaryKey:@"CFBundleVersion"] copy];//[[internalBundle infoDictionary] objectForKey:@"CFBundleVersion"];
	//	NSString * installedBundleVersion = [[installedBundle objectForInfoDictionaryKey:@"CFBundleVersion"] copy];
	//	if([internalBundleVersion compare:installedBundleVersion options:NSCaseInsensitiveSearch] == 1)
		{
			CFRelease(installedBundle);
			CFRelease(internalBundle);
			NSLog(@"Plugin is out of date, prompting to update");
		//	[self copyPluginToSystem:self];
		}	
	}
}

- (void)copyPluginToSystem:(id)sender
{
	NSString * source = [[NSBundle bundleWithIdentifier:@"com.joemattiello.driver.dm2.prefpanel"] bundlePath];
	source = [source stringByAppendingString:@"/Contents/Resources/DM2USBMIDIDriver.plugin"];

	NSString * destination = [NSString stringWithString:@"/Library/Audio/MIDI Drivers/DM2USBMIDIDriver.plugin"];
	
	//source = [source stringByStandardizingPath];
	//destination = [destination stringByStandardizingPath];
	
	NSFileManager * manager = [NSFileManager defaultManager];
	if (![manager fileExistsAtPath:source])
	{
		NSLog(@"failed\n***No source file at \"%@\".\n",source);
		return;
	}
	//[manager movePath:source toPath:destination handler:nil];
	[manager authorizedCopyPath:source toPath:destination];
}

@end
