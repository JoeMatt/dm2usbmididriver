/* DM2_PreferencesPref */

#import <Cocoa/Cocoa.h>

@interface DM2_PreferencesPref : NSPreferencePane
{
    IBOutlet id bank1StickyButtonsCheckbox;
    IBOutlet id bank2StickyButtonsCheckbox;
    IBOutlet id bank3StickyButtonsCheckbox;
    IBOutlet id bank4StickyButtonsCheckbox;
    IBOutlet id saveButton;
}
- (IBAction)bank1StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank2StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank3StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)bank4StickyButtonsCheckboxClicked:(id)sender;
- (IBAction)saveButtonClicked:(id)sender;
@end
