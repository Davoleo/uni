//
//  MWSettingsViewController.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWSettingsViewController.h"
#import "MWSettings.h"

@implementation MWSettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(NSIndexPath*)indexPath {
    UITableViewCell* selectedCell = [tableView cellForRowAtIndexPath:indexPath];

    if (indexPath.section > 1)
        return;

    if (selectedCell.accessoryType != UITableViewCellAccessoryCheckmark) {
        //Check the selected cell
        selectedCell.accessoryType = UITableViewCellAccessoryCheckmark;

        //Uncheck all the others cells
        for (int i = 0; i < [tableView numberOfRowsInSection:indexPath.section]; ++i) {
            if (i != indexPath.row)
                [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:i inSection:indexPath.section]].accessoryType = UITableViewCellAccessoryNone;
        }

        //Save New Choice to User Defaults
        [[NSUserDefaults standardUserDefaults] setInteger:indexPath.row forKey:MW_TEMPERATURE_METRIC_PREF];
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
