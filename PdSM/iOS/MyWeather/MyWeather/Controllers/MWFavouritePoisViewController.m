//
//  MWFavouritePoisViewController.m
//  MyWeather
//
//  Created by Leo Dav on 20/05/22.
//

#import "MWFavouritePoisViewController.h"
#import "MWUtils.h"
#import "MWWeatherDetailViewController.h"
#import "MWWeatherMapViewController.h"
#import "MWPoi+WeatherAnnotation.h"

@interface MWFavouritePoisViewController ()

@property (nonatomic) MWTemperatureMetrics temperatureMetric;

@end

@implementation MWFavouritePoisViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.favourites = [MWFavouritesCache reference];
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
    return [self.favourites length];
}

- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"favouriteCell" forIndexPath:indexPath];

    MWForecast* cellForecast = [self.favourites getAll][(NSUInteger) indexPath.row];

    //NSString* location = self.favourites.favoritesCache.allKeys[(NSUInteger) indexPath.row];

    cell.textLabel.text = cellForecast.location.placemarkCache.name;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@", [MWUtils temperature:cellForecast.current.temperature FormattedInMetric:self.temperatureMetric]];

    return cell;
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {

    if ([segue.identifier isEqualToString:@"showWeatherDetail"] &&
            [[segue destinationViewController] isKindOfClass:[MWWeatherDetailViewController class]]) {

        MWWeatherDetailViewController* controller = [segue destinationViewController];

        NSIndexPath* index = [self.tableView indexPathForCell:sender];
        MWForecast* forecast =  [self.favourites getAll][(NSUInteger) index.row];
        controller.forecast = forecast;
        controller.position = forecast.location;
    }

    if ([segue.identifier isEqualToString:@"showWeatherMap"] &&
            [[segue destinationViewController] isKindOfClass:[MWWeatherMapViewController class]]) {
        MWWeatherMapViewController* mapController = [segue destinationViewController];

        NSMutableArray* array = [NSMutableArray arrayWithCapacity:[self.favourites length]];
        [[self.favourites getAll] enumerateObjectsUsingBlock:^(MWForecast* forecast, NSUInteger index, BOOL* stop) {
            MWPoi* extendedPoi = forecast.location;
            //TODO crash: Unknown selector sent to MWPoi
            extendedPoi.conditionImageName = [forecast.current.condition decodeSystemImageName];
            [array addObject:extendedPoi];
        }];
        mapController.positions = array;
    }

}

@end
