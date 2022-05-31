//
//  MWMyPositionViewController.m
//  MyWeather
//
//  Created by Leo Dav on 31/05/22.
//

#import "MWMyPositionViewController.h"
#import "MWPoi.h"
#import "MWCurrentWeatherDetailVC.h"
#import "MWManagers.h"

@interface MWMyPositionViewController()<CLLocationManagerDelegate>

@property (weak, nonatomic) IBOutlet UIView* container;
@property (nonatomic, strong) MWPoi* myPoi;

@end

@implementation MWMyPositionViewController

- (void)viewDidLoad {
    //Location Manager Setup
    CLLocationManager* manager = [MWManagers locationManager];
    manager.delegate = self;
}

- (void)viewWillAppear:(BOOL)animated {
    //View is becoming active -> start monitoring
    [[MWManagers locationManager] startUpdatingLocation];
}

- (void)viewWillDisappear:(BOOL)animated {
    //View is resigning from main position -> stop monitoring to save resources
    [[MWManagers locationManager] stopUpdatingLocation];
}

- (void)locationManager:(CLLocationManager*)manager didUpdateLocations:(NSArray<CLLocation*>*)locations {
    //Update location
    CLLocation* current = locations.lastObject;

    MWPoi* oldPoi = self.myPoi;
    self.myPoi = [MWPoi poiWithLatitude:current.coordinate.latitude longitude:current.coordinate.longitude];
    //First time position is assigned => we add the currentWeatherViewController to this VC's children
    if (oldPoi == nil) {
        [self displayCurrentWeatherController];
    }
}

//TODO Fix [Storyboard] Activity Indicator (Should probably be placed here now instead of the child VC)
- (void) displayCurrentWeatherController {
    MWCurrentWeatherDetailVC* viewController = [self.storyboard instantiateViewControllerWithIdentifier:@"currentWeatherVC"];
    [self addChildViewController:viewController];
    [self.container addSubview:viewController.view];
    viewController.view.frame = self.container.bounds;
    [viewController didMoveToParentViewController:self];
}



#pragma mark - Navigation

//Prepare and send information to the ViewContainers
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([[segue identifier] isEqualToString:@"CurrentWeatherSegue"]) {
        MWCurrentWeatherDetailVC* currentController = [segue destinationViewController];
        currentController.position = self.myPoi;
    }
}


@end
