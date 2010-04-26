/* DM2_PreferencesPref */

#import <Cocoa/Cocoa.h>
#import <PreferencePanes/NSPreferencePane.h>
#import <CoreFoundation/CoreFoundation.h>
#import "Update.h"
#import "NSFileManagerAdditions.h"
//#import <Quartz/Quartz.h>
 
@interface DM2_PreferencesPref : NSPreferencePane
{
	
	/* Main View */
	IBOutlet NSButton * saveButton;
	IBOutlet NSButton * helpButton;
	IBOutlet NSTabView * tabView;	
		/* Tabs */
	NSTabViewItem * bank1Tab;
	NSTabViewItem * bank2Tab;
	NSTabViewItem * bank3Tab;
	NSTabViewItem * bank4Tab;
	NSTabViewItem * traktorTab;
	NSTabViewItem * statusTab;
	NSTabViewItem * aboutTab;
	/* Global */
	IBOutlet NSButton * checkForUpdateButton;
	IBOutlet NSButton * resetCalibrationButton;
	IBOutlet NSButton * clearLEDsButton;
	IBOutlet NSButton * checkAutomaticallyCheckbox;
	IBOutlet NSPopUpButton * softwareModeButton;
	IBOutlet NSButton * resetInterface;
	IBOutlet NSButton * growlSupportCheckbox;
	/* Banks 1-4 */
	IBOutlet NSButton * bank1DisplaysMIDIClockCheckbox;
	IBOutlet NSButton * bank2DisplaysMIDIClockCheckbox;
	IBOutlet NSButton * bank3DisplaysMIDIClockCheckbox;
	IBOutlet NSButton * bank4DisplaysMIDIClockCheckbox;

	IBOutlet NSPopUpButton * bank1WhoControlsLEDsPopUpButton; 
	IBOutlet NSPopUpButton * bank2WhoControlsLEDsPopUpButton;
	IBOutlet NSPopUpButton * bank3WhoControlsLEDsPopUpButton;
	IBOutlet NSPopUpButton * bank4WhoControlsLEDsPopUpButton;

	IBOutlet NSPopUpButton * bank1ScratchRingBumpIgnorePopUpButton;
	IBOutlet NSPopUpButton * bank2ScratchRingBumpIgnorePopUpButton;
	IBOutlet NSPopUpButton * bank3ScratchRingBumpIgnorePopUpButton;
	IBOutlet NSPopUpButton * bank4ScratchRingBumpIgnorePopUpButton;
	
    IBOutlet NSButton * bank1StickyButtonsCheckbox;
	IBOutlet NSButton * bank2StickyButtonsCheckbox;
    IBOutlet NSButton * bank3StickyButtonsCheckbox;
    IBOutlet NSButton * bank4StickyButtonsCheckbox;
	
	IBOutlet NSButton * bank1InvertLedsCheckbox;
	IBOutlet NSButton * bank2InvertLedsCheckbox;
    IBOutlet NSButton * bank3InvertLedsCheckbox;
    IBOutlet NSButton * bank4InvertLedsCheckbox;
	/* Status */
	IBOutlet NSTextField * osWarningTextField;
	/* Traktor */
	IBOutlet NSButton * exportTraktorButton;
	/* About */
	IBOutlet NSButton * registerButton;
    IBOutlet NSButton * visitHomepageButton;
    IBOutlet NSButton * contactAuthorButton;
	IBOutlet NSTextView * readmeTextView;
	IBOutlet NSTextField * regEmail;
	IBOutlet NSTextField * regName;
	IBOutlet NSTextField * nameLabel;
	IBOutlet NSTextField * emailLabel;
	IBOutlet NSTextField * versionLabel;
	
	/* Other */
	Updater * updater;
	CFStringRef appID;
	NSString * versionString;
}

/******* Bank pages ***********/
- (IBAction)bank1StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank2StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank3StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank4StickyButtonsCheckboxClicked:(id)sender;

- (IBAction)bank1InvertLedsCheckboxClicked:(id)sender;
- (IBAction)bank2InvertLedsCheckboxClicked:(id)sender;
- (IBAction)bank3InvertLedsCheckboxClicked:(id)sender;
- (IBAction)bank4InvertLedsCheckboxClicked:(id)sender;

- (IBAction)displaysMIDIClockCheckboxClicked:(id)sender;
- (IBAction)whoControlsLEDsPopUpButtonChanged:(id)sender;
- (IBAction)scratchRingBumpIgnorePopUpButtonChanged:(id)sender;
/******** Global Page ************/
- (IBAction)clearLEDsButtonClicked:(id)sender;
- (IBAction)resetCalibrationButtonClicked:(id)sender;
- (IBAction)checkForUpdateButtonClicked:(id)sender;
- (IBAction)checkAutomaticallyCheckboxClicked:(id)sender;
- (IBAction)softwareModeComboBoxChanged:(id)sender;
- (IBAction)resetInterfaceButtonClicked:(id)sender;
- (IBAction)growlSupportCheckboxClicked:(id)sender;
/********* About Page *************/
- (IBAction)contactAuthorButtonClicked:(id)sender;
- (IBAction)visitHomepageButtonClicked:(id)sender;
- (IBAction)donateButtonClicked:(id)sender;

/********* All Pages *************/
- (IBAction)saveButtonClicked:(id)sender;
- (IBAction)helpButtonClicked:(id)sender;
/********* Traktor Page *********/
- (IBAction)exportTraktorButtonClicked:(id)sender;

/******** Utility functions *********/
- (void)changeModeTo:(NSString*)mode;
- (void)sendDriverMessage:(CFStringRef)message;
- (void)openReadme:(id)sender;
- (void)loadQuartz:(id)sender;
- (void)checkIfPluginIsUpToDate:(id)sender;
- (void)copyPluginToSystem:(id)sender;

@end
