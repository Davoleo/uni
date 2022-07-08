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
#import "LoadingAlert.h"

@interface MWFavouritePoisViewController ()

@property (nonatomic) MWTemperatureMetrics temperatureMetric;

@end

@implementation MWFavouritePoisViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    //If the cache is not present show loading popup until it's ready (then dismiss it)
    if (![MWFavouritesCache isPresent]) {
        [LoadingAlert showInController:self];
        [MWFavouritesCache onReadyCall:^{
            [self refreshTableContents];
            [LoadingAlert dismissFromController:self];
        }];
    }
    //Save a reference to the favorites cache
    self.favourites = [MWFavouritesCache reference];
}

- (void)viewDidAppear:(BOOL)animated {
    //When the view appears we set the new temperature metric preference and refresh table contents so that if the old one was wrong it gets updated
    self.temperatureMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    [self refreshTableContents];
}

///Refreshes all the table rows, filling with new content
- (void) refreshTableContents {
    [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationAutomatic];
}

- (nullable UIContextMenuConfiguration*)tableView:(UITableView*)tableView contextMenuConfigurationForRowAtIndexPath:(NSIndexPath*)indexPath point:(CGPoint)point {
    return [UIContextMenuConfiguration
            configurationWithIdentifier:nil
                        previewProvider:nil
                         actionProvider:^(NSArray<UIMenuElement*>* suggestedActions) {

        //Build a UIAction to add to the context menu
        UIAction* deleteAction = [UIAction
                actionWithTitle:@"Delete"
                          image:[UIImage systemImageNamed:@"trash.fill"]
                     identifier:@"delete_action"
                        handler:^(UIAction* action){
                            //Remove the placemark location identified by the placemark name (cell name) from the favourites
                            UITableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
                            [[MWFavouritesCache reference] remove:cell.text];
                            //Persist favorites changes
                            [[MWFavouritesCache reference] saveFavourites];
                            dispatch_async(dispatch_get_main_queue(), ^{
                                //Refresh table contents on the main thread so that the UI reflects the changes
                                [self refreshTableContents];
                            });
                        }];
        return [UIMenu menuWithTitle:@"" children:@[deleteAction]];
    }];
}


#pragma mark - Table view data source

- (NSInteger) numberOfSectionsInTableView: (UITableView*)tableView {
    return 1;
}

- (NSInteger) tableView: (UITableView*)tableView numberOfRowsInSection: (NSInteger)section {
    return [self.favourites length];
}

///Builds the favorite cell with the correct information about the favorite location
- (UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"favouriteCell" forIndexPath:indexPath];

    MWForecast* cellForecast = [self.favourites getAll][(NSUInteger) indexPath.row];

    //NSString* location = self.favourites.favoritesCache.allKeys[(NSUInteger) indexPath.row];
    CLPlacemark* placemark = cellForecast.location.placemarkCache;
    cell.textLabel.text = placemark.thoroughfare != nil ? [NSString stringWithFormat:@"%@ %@", placemark.thoroughfare, placemark.locality] : placemark.name;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@", [MWUtils temperature:cellForecast.current.temperature FormattedInMetric:self.temperatureMetric]];
    cell.image = [UIImage systemImageNamed:[cellForecast.current.condition decodeSystemImageName]];

    return cell;
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {

    //Handles selection [short tap] of the cell -> Show Weather detail page
    if ([segue.identifier isEqualToString:@"showWeatherDetail"] &&
            [[segue destinationViewController] isKindOfClass:[MWWeatherDetailViewController class]]) {

        MWWeatherDetailViewController* controller = [segue destinationViewController];

        NSIndexPath* index = [self.tableView indexPathForCell:sender];
        MWForecast* forecast =  [self.favourites getAll][(NSUInteger) index.row];
        controller.forecast = forecast;
        controller.position = forecast.location;
    }

    //Handles map BarButton tap -> Show weather Map with placemarks
    if ([segue.identifier isEqualToString:@"showWeatherMap"] &&
            [[segue destinationViewController] isKindOfClass:[MWWeatherMapViewController class]]) {
        MWWeatherMapViewController* mapController = [segue destinationViewController];

        NSMutableArray* posArray = [NSMutableArray arrayWithCapacity:[self.favourites length]];
        NSMutableArray* icoArray = [NSMutableArray arrayWithCapacity:[self.favourites length]];
        [[self.favourites getAll] enumerateObjectsUsingBlock:^(MWForecast* forecast, NSUInteger index, BOOL* stop) {
            //Extended poi refers to the category: MWPoi+WeatherAnnotation
            MWPoi* extendedPoi = forecast.location;
            [posArray addObject:extendedPoi];
            [icoArray addObject:forecast.current.condition];
        }];
        //Update mapController with the data to display
        mapController.positions = posArray;
        mapController.conditions = icoArray;
    }

}

@end
