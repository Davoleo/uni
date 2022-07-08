//
//  MWWeatherMapViewController.m
//  MyWeather
//
//  Created by Leo Dav on 21/06/22.
//

#import <MapKit/MapKit.h>
#import "MWWeatherMapViewController.h"
#import "MWPoi+WeatherAnnotation.h"
#import "MWWeatherDetailViewController.h"

@interface MWWeatherMapViewController () <MKMapViewDelegate>

@property (weak, nonatomic) IBOutlet MKMapView *mapView;

@end

@implementation MWWeatherMapViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.mapView.delegate = self;

    [self.positions enumerateObjectsUsingBlock:^(MWPoi* poi, NSUInteger index, BOOL* stop) {
        if ([poi conformsToProtocol:@protocol(MKAnnotation)]) {
            [self.mapView addAnnotation:(id<MKAnnotation>) poi];
        }
    }];
}

- (nullable MKAnnotationView*)mapView:(MKMapView*)mapView viewForAnnotation:(id)annotation {

    //Static allocation -> Only initialized once
    static NSString* annotationIdentifier = @"MapAnnotationView";
    MKAnnotationView* view = [mapView dequeueReusableAnnotationViewWithIdentifier:annotationIdentifier];

    //If the annotation-view is null we create it with a custom reuseIdentifier
    if (!view) {
        view = [[MKAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:annotationIdentifier];
        view.canShowCallout = YES;
    }

    if ([annotation isKindOfClass:[MWPoi class]]) {
        view.annotation = annotation;

        //set up the annotation and it's callout
        MWPoi* position = annotation;
        MWWeatherCondition* condition = self.conditions[[self.positions indexOfObject:position]];
        UIImage* weatherImage = [UIImage systemImageNamed: [condition decodeSystemImageName]];
        view.image = [weatherImage imageWithTintColor:[UIColor colorNamed:@"AccentColor"] renderingMode:UIImageRenderingModeAutomatic];
        view.leftCalloutAccessoryView = [[UIImageView alloc] initWithImage:weatherImage];
        view.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeInfoDark];

        return view;
    }

    return nil;
}

- (void)mapView:(MKMapView*)mapView annotationView:(MKAnnotationView*)view calloutAccessoryControlTapped:(UIControl*)control {
    //if the users presses the right accessory view -> show the weather detail page for that position
    if ([control isEqual:view.rightCalloutAccessoryView]) {
        [self performSegueWithIdentifier:@"showDetails" sender:view];
    }
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"showDetails"] &&
            [segue.destinationViewController isKindOfClass:[MWWeatherDetailViewController class]]) {
        //Set up the correct position to show weather details
        MWWeatherDetailViewController* controller = segue.destinationViewController;
        if ([sender isKindOfClass:[MKAnnotationView class]]) {
            id<MKAnnotation> annotation = ((MKAnnotationView*) sender).annotation;
            if ([annotation isKindOfClass:[MWPoi class]]) {
                controller.position = annotation;
            }
        }
    }
}

@end
