//
//  MWSearchViewController.m
//  MyWeather
//
//  Created by Leo Dav on 16/06/22.
//

#import "MWSearchViewController.h"
#import "MWManagers.h"
#import "MWUtils.h"
#import "MWWeatherDetailViewController.h"
#import "MWFavouritesCache.h"

@interface MWSearchViewController () <UISearchBarDelegate, UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UISearchBar *searchBox;
@property (weak, nonatomic) IBOutlet UITableView *resultsTable;

@property (strong, nonatomic) NSArray<CLPlacemark*>* placemarks;

//@property (strong, nonatomic) UISearchController* searchController;

@end

@implementation MWSearchViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.searchBox.delegate = self;
    self.resultsTable.dataSource = self;

}

- (void)searchBarSearchButtonClicked:(UISearchBar*)searchBar {

    NSString* searchString = searchBar.text;
    [MWManagers.geocoder geocodeAddressString:searchString completionHandler:^(NSArray<CLPlacemark*>* results, NSError* error) {
        if (results.count == 0) {
            if (error != nil) {
                NSLog(@"%ld - %@", error.code, error.localizedDescription);
            }
            self.placemarks = [NSArray array];
        }
        else
            self.placemarks = results;

        [self.resultsTable reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationTop];

    }];
    [searchBar resignFirstResponder];
}

- (NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section {
    return self.placemarks.count;
}

- (UITableViewCell*)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath*)indexPath {
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"searchResultCell"];

    //Show weather icon
    CLPlacemark* mark = self.placemarks[(NSUInteger) indexPath.row];
    cell.textLabel.text = mark.name;
    CLLocationCoordinate2D coords = mark.location.coordinate;
    [MWUtils queryCurrentWeatherInLocation:[MWPoi poiWithLatitude:coords.latitude longitude:coords.longitude]
                                   AndThen:^(MWWeatherData* weather) {
        UIImage* weatherImage = [UIImage systemImageNamed:[weather.condition decodeSystemImageName]];
        dispatch_async(dispatch_get_main_queue(), ^{
            cell.imageView.image = weatherImage;
        });
    }];
    
    //Add Accessory view
    UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];

    //TODO fix issue if user searches before accessing favorites for the first time not causing initialization of favorites cache
    MWFavouritesCache* cache = [MWFavouritesCache reference];
    BOOL isInFavorites = [cache has:mark.name];
    [button setImage:[UIImage systemImageNamed: isInFavorites ? @"star.fill" : @"star"] forState:UIControlStateNormal];
    [button sizeToFit];
    [button addTarget:self action:@selector(handleStarButtonTap:) forControlEvents:UIControlEventTouchUpInside];
    button.tag = indexPath.row;
    cell.accessoryView = button;

    return cell;
}

- (void) handleStarButtonTap: (UIButton*) button {
    CLPlacemark* placemark = self.placemarks[(NSUInteger) button.tag];
    MWFavouritesCache* cache = [MWFavouritesCache reference];
    if ([button.imageView.image isEqual:[UIImage systemImageNamed:@"star"]]) {
        [button setImage:[UIImage systemImageNamed:@"rays"] forState:UIControlStateNormal];
        __weak typeof(cache) weakCache = cache;
        [cache add:placemark.name Then:^{
            [button setImage:[UIImage systemImageNamed:@"star.fill"] forState:UIControlStateNormal];
            [weakCache saveFavourites];
        }];
    }
    else {
        [cache remove:placemark.name];
        [button setImage:[UIImage systemImageNamed:@"star"] forState:UIControlStateNormal];
    }
}

- (IBAction) backgroundTouched {
    [self.searchBox resignFirstResponder];
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"showCurrentWeather"] &&
            [[segue destinationViewController] isKindOfClass:[MWWeatherDetailViewController class]]) {

        NSUInteger posIndex = (NSUInteger) [self.resultsTable indexPathForCell:sender].row;

        MWWeatherDetailViewController* controller = [segue destinationViewController];
        CLPlacemark* placemark = self.placemarks[posIndex];
        controller.position = [MWPoi poiWithLatitude:placemark.location.coordinate.latitude longitude:placemark.location.coordinate.longitude];
    }
}


@end
