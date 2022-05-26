//
//  MWSettingsViewController.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWSettingsViewController.h"
#import "MWSettings.h"

const int MW_SETTINGS_VC_SECTION_TEMPERATURE = 0;
const int MW_SETTINGS_VC_SECTION_THEME = 1;

@implementation MWSettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //TODO set the right defaults depending on these values
    MWThemeEnum themePref = (MWThemeEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_THEME_PREF];
    if (themePref > 0) {

    }
    MWTemperatureMetricsEnum tempPref = (MWTemperatureMetricsEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
}

- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(NSIndexPath*)indexPath {
    UITableViewCell* selectedCell = [tableView cellForRowAtIndexPath:indexPath];

    //NSLog([NSString stringWithFormat:@"section: %d  row: %d", indexPath.section, indexPath.row]);

    if (indexPath.section <= 1 && selectedCell.accessoryType != UITableViewCellAccessoryCheckmark) {
        //Check the selected cell
        selectedCell.accessoryType = UITableViewCellAccessoryCheckmark;

        //Uncheck all the others cells
        for (int i = 0; i < [tableView numberOfRowsInSection:indexPath.section]; ++i) {
            if (i != indexPath.row)
                [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:i inSection:indexPath.section]].accessoryType = UITableViewCellAccessoryNone;
        }

        //Save New Choice to User Defaults
        switch (indexPath.section) {
            case MW_SETTINGS_VC_SECTION_TEMPERATURE:
                [[NSUserDefaults standardUserDefaults] setInteger:indexPath.row forKey:MW_TEMPERATURE_METRIC_PREF];
                break;
            case MW_SETTINGS_VC_SECTION_THEME:
                [[NSUserDefaults standardUserDefaults] setInteger:indexPath.row forKey:MW_THEME_PREF];
                break;
            default:
                NSAssert(false, @"FAILED ASSERTION ON USER DEFAULT PREFS SAVE [SETTINGS VC]");
                break;
        }
    }

    //Last Section
    if (indexPath.section == tableView.numberOfSections - 1) {

        for (int i = 0; i < [tableView numberOfRowsInSection:indexPath.section]; ++i) {
            NSString* webDetail = [tableView cellForRowAtIndexPath:indexPath].detailTextLabel.text;
            if (webDetail != nil && [webDetail hasPrefix:@"https://"]) {
                NSLog(@"HERE HERE HERE");
                UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Open Link?" message:@"Continue will open your default web browser on the link you clicked" preferredStyle:UIAlertControllerStyleAlert];
                [alert addAction:[UIAlertAction actionWithTitle:@"Continue" style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
                    //Open link
                    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:webDetail] options:[NSDictionary dictionary] completionHandler:nil];
                }]];
                [alert addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];
                [self presentViewController:alert animated:YES completion:nil];
            }
        }
    }
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
