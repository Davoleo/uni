//
//  MWFavouritePoisViewController.m
//  MyWeather
//
//  Created by Leo Dav on 20/05/22.
//

#import "MWFavouritePoisViewController.h"
#import "MWUtils.h"

@interface MWFavouritePoisViewController ()

@property (nonatomic) MWTemperatureMetrics temperatureMetric;

@end

@implementation MWFavouritePoisViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.favourites = [[MWFavouritesCache alloc] init];
    [self.favourites addPoi:[MWPoi poiWithLatitude:44 longitude:35] ThenExecuteSelector: @selector(refreshTableContents) OnObject: self];
    [self.favourites addPoi:[MWPoi poiWithLatitude:44 longitude:33] ThenExecuteSelector: @selector(refreshTableContents) OnObject: self];
}

- (void)viewDidAppear:(BOOL)animated {
    self.temperatureMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    [self refreshTableContents];
}

- (void) refreshTableContents {
    [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationAutomatic];
}

#pragma mark - Table view data source

- (NSInteger) numberOfSectionsInTableView: (UITableView*)tableView {
    return 1;
}

- (NSInteger) tableView: (UITableView*)tableView numberOfRowsInSection: (NSInteger)section {
    NSLog(@"%ld", [self.favourites length]);
    return [self.favourites length];
}

- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"favouriteCell" forIndexPath:indexPath];

    MWForecast* cellForecast = [self.favourites getAll][(NSUInteger) indexPath.row];
    NSLog(@"Condition %@", cellForecast.current.condition.smallDesc);
    cell.textLabel.text = cellForecast.current.condition.name;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%lf°%c", cellForecast.current.temperature, [MWUtils temperatureFormatCharForMetric:self.temperatureMetric]];

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
