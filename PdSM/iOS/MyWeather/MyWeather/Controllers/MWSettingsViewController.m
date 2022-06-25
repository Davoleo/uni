//
//  MWSettingsViewController.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWSettingsViewController.h"
#import "MWSettings.h"
#import "MWFavouritesCache.h"

const int MW_SETTINGS_VC_SECTION_TEMPERATURE = 0;
const int MW_SETTINGS_VC_SECTION_THEME = 1;

@implementation MWSettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    //View Has appeared -> we set default checkmarked rows
    MWTemperatureMetrics tempPref = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    NSIndexPath* cellIndex = [NSIndexPath indexPathForRow:tempPref inSection:MW_SETTINGS_VC_SECTION_TEMPERATURE];
    [self.tableView cellForRowAtIndexPath:cellIndex].accessoryType = UITableViewCellAccessoryCheckmark;

    MWThemeEnum themePref = (MWThemeEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_THEME_PREF];
    cellIndex = [NSIndexPath indexPathForRow:themePref inSection:MW_SETTINGS_VC_SECTION_THEME];
    [self.tableView cellForRowAtIndexPath:cellIndex].accessoryType = UITableViewCellAccessoryCheckmark;
    NSLog(@"TempPref: %ld", (long) themePref);
}

- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(NSIndexPath*)indexPath {
    UITableViewCell* selectedCell = [tableView cellForRowAtIndexPath:indexPath];

    //NSLog([NSString stringWithFormat:@"section: %d  row: %d", indexPath.section, indexPath.row]);

    if (indexPath.section <= 1 && selectedCell.accessoryType != UITableViewCellAccessoryCheckmark) {
        //Check the selected cell
        selectedCell.accessoryType = UITableViewCellAccessoryCheckmark;

        //Uncheck previously selected cell
        MWThemeEnum themeId = (MWThemeEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_THEME_PREF];
        if (indexPath.section == 1 && themeId == indexPath.row)
            return;
        [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:themeId inSection:indexPath.section]].accessoryType = UITableViewCellAccessoryNone;


        MWTemperatureMetrics originalMetrics = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
        if (indexPath.section == 0 && originalMetrics == indexPath.row)
            return;
        [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:originalMetrics inSection:indexPath.section]].accessoryType = UITableViewCellAccessoryNone;

        //Save New Choice to User Defaults
        switch (indexPath.section) {
            case MW_SETTINGS_VC_SECTION_TEMPERATURE:
                [[NSUserDefaults standardUserDefaults] setInteger:indexPath.row forKey:MW_TEMPERATURE_METRIC_PREF];
                break;
            case MW_SETTINGS_VC_SECTION_THEME:
                [[NSUserDefaults standardUserDefaults] setInteger:indexPath.row forKey:MW_THEME_PREF];
                switch (indexPath.row) {
                    case MWThemeSystem:
                        UIApplication.sharedApplication.keyWindow.overrideUserInterfaceStyle = UIUserInterfaceStyleUnspecified;
                        break;
                    case MWThemeLight:
                        UIApplication.sharedApplication.keyWindow.overrideUserInterfaceStyle = UIUserInterfaceStyleLight;
                        break;
                    case MWThemeDark:
                        UIApplication.sharedApplication.keyWindow.overrideUserInterfaceStyle = UIUserInterfaceStyleDark;
                        break;
                    default:
                        NSAssert(false, @"FAILED ASSERTION ON THEME OVERRIDING [SETTINGS VC]");
                        break;
                }
                break;
            default:
                NSAssert(false, @"FAILED ASSERTION ON USER DEFAULT PREFS SAVE [SETTINGS VC]");
                break;
        }
    }

    //Danger Section
    if (indexPath.section == 2) {
        UITableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
        if ([cell.text isEqualToString:@"Clear Favourites"]) {
            UIAlertController* alert = [UIAlertController
                    alertControllerWithTitle:@"Are you sure?"
                                     message:@"\"Clear\" will remove all positions from Favourites"
                              preferredStyle:UIAlertControllerStyleAlert];

            [alert addAction:[UIAlertAction actionWithTitle:@"Clear" style:UIAlertActionStyleDestructive handler:^(UIAlertAction* action) {
                [[MWFavouritesCache reference] clear];
            }]];
            [alert addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
        }
    }

    //Last Section
    if (indexPath.section == tableView.numberOfSections - 1) {

        for (int i = 0; i < [tableView numberOfRowsInSection:indexPath.section]; ++i) {
            NSString* webDetail = [tableView cellForRowAtIndexPath:indexPath].detailTextLabel.text;
            if (webDetail != nil && [webDetail hasPrefix:@"https://"]) {
                UIAlertController* alert = [UIAlertController
                        alertControllerWithTitle:@"Open Link?"
                                         message:@"Continue will open your default web browser on the link you clicked"
                                  preferredStyle:UIAlertControllerStyleAlert];

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
