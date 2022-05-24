//
//  MWFavouritePoisViewController.m
//  MyWeather
//
//  Created by Leo Dav on 20/05/22.
//

#import "MWFavouritePoisViewController.h"

@interface MWFavouritePoisViewController ()

@end

@implementation MWFavouritePoisViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.favourites = [[MWFavouritesCache alloc] init];
    [self.favourites addFavoritePoi:[MWPoi poiWithLatitude:44 longitude:35]];
    [self.favourites addFavoritePoi:[MWPoi poiWithLatitude:44 longitude:33]];
}

#pragma mark - Table view data source

- (NSInteger) numberOfSectionsInTableView: (UITableView*)tableView {
    return 1;
}

- (NSInteger) tableView: (UITableView*)tableView numberOfRowsInSection: (NSInteger)section {
    return [self.favourites length];
}

- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"favouriteCell" forIndexPath:indexPath];

    MWForecast* cellForecast = [self.favourites getAllFavourites][(NSUInteger) indexPath.row];
    cell.textLabel.text = cellForecast.current.condition.name;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%lf°K", cellForecast.current.temperature];

    return cell;
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
