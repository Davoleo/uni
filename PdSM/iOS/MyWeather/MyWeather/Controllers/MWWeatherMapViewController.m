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

    static NSString* annotationIdentifier = @"MapAnnotationView";
    MKAnnotationView* view = [mapView dequeueReusableAnnotationViewWithIdentifier:annotationIdentifier];

    if (!view) {
        view = [[MKAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:annotationIdentifier];
        view.canShowCallout = YES;
    }

    if ([annotation isKindOfClass:[MWPoi class]]) {
        view.annotation = annotation;

        MWPoi* position = annotation;
        UIImage* weatherImage = [UIImage systemImageNamed: position.conditionImageName];
        view.image = weatherImage;
        view.leftCalloutAccessoryView = [[UIImageView alloc] initWithImage:weatherImage];
        view.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeInfoDark];

        return view;
    }

    return nil;
}

- (void) panzoomMapToLocation: (CLLocationCoordinate2D) location withZoom: (double) zoom {
    MKCoordinateRegion mapRegion;
    mapRegion.center = location;
    mapRegion.span.latitudeDelta = zoom;
    mapRegion.span.longitudeDelta = zoom;

    [self.mapView setRegion:mapRegion];
}

- (void)mapView:(MKMapView*)mapView annotationView:(MKAnnotationView*)view calloutAccessoryControlTapped:(UIControl*)control {
    if ([control isEqual:view.rightCalloutAccessoryView]) {
        [self performSegueWithIdentifier:@"showDetails" sender:view];
    }
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"showDetails"] &&
            [segue.destinationViewController isKindOfClass:[MWWeatherDetailViewController class]]) {
        MWWeatherDetailViewController* controller = segue.destinationViewController;
        if ([sender isKindOfClass:[MWPoi class]]) {
            controller.position = sender;
        }
    }
}

@end
