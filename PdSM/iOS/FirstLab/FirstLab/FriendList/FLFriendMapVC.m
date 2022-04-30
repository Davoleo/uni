//
//  FLFriendMapVC.m
//  FirstLab
//
//  Created by Leo Dav on 30/04/2022.
//

#import <CoreData/CoreData.h>
#import "FLFriendMapVC.h"
#import "MapKit/MapKit.h"
#import "FLGeoFriend+MapAnnotation.h"
#import "FLFriendTableDetailVC.h"

//Conform to MapViewDelegate (to allow map customization)
@interface FLFriendMapVC ()<MKMapViewDelegate>

@property (weak, nonatomic) IBOutlet MKMapView *mapView;

- (void) centerMapToLocation:(CLLocationCoordinate2D)location
                   zoomLevel:(double)zoom;

@end

@implementation FLFriendMapVC

- (void)viewDidLoad {
    [super viewDidLoad];

    NSLog(@"%s: Got %ld friends", __FUNCTION__, self.friends.count);
    self.mapView.delegate = self;

    //[self centerMapToLocation:CLLocationCoordinate2DMake(44, 10) zoomLevel:0.5];

    [self.friends enumerateObjectsUsingBlock:^(id _Nonnull obj, NSUInteger index, BOOL* _Nonnull stop) {
        if ([obj isKindOfClass:[FLGeoFriend class]]) {
            FLGeoFriend* geoFriend = obj;
            [self.mapView addAnnotation:geoFriend];
        }
    }];
}

- (nullable MKAnnotationView*)mapView:(MKMapView*)mapView viewForAnnotation:(id)annotation {

    static NSString* annotationIdentifier = @"MapAnnotationView";
    MKAnnotationView* view = [mapView dequeueReusableAnnotationViewWithIdentifier:annotationIdentifier];

    if (!view) {
        view = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:annotationIdentifier];
        view.canShowCallout = YES;
    }

    view.annotation = annotation;

    UIImageView* imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 36, 36)];
    imageView.image = [UIImage imageNamed:@"userinfo"];
    view.leftCalloutAccessoryView = imageView;
    view.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeInfoDark];

    return view;
}


- (void)centerMapToLocation:(CLLocationCoordinate2D)location zoomLevel:(double)zoom {
    MKCoordinateRegion mapRegion;
    mapRegion.center = location;
    mapRegion.span.latitudeDelta = zoom;
    mapRegion.span.longitudeDelta = zoom;

    [self.mapView setRegion:mapRegion];
}

- (void)mapView:(MKMapView*)mapView didSelectAnnotationView:(MKAnnotationView*)view {
    if ([view.leftCalloutAccessoryView isKindOfClass:[UIImageView class]]) {
        UIImageView* imageView = (UIImageView*) view.leftCalloutAccessoryView;
        id<MKAnnotation> annotation = view.annotation;
        if ([annotation isKindOfClass:[FLGeoFriend class]]) {
            FLGeoFriend* geoFriend = annotation;
            if (geoFriend.thumbnail != nil) {
                dispatch_queue_t queue = dispatch_queue_create("imageDownload", NULL);
                dispatch_async(queue, ^{
                    NSURL* url = [NSURL URLWithString:geoFriend.thumbnail];
                    NSData* data = [NSData dataWithContentsOfURL:url];
                    UIImage* image = [UIImage imageWithData:data];
                    //Setting image in the main queue because we're updating UI
                    dispatch_queue_t mainQueue = dispatch_get_main_queue();
                    dispatch_async(mainQueue, ^{
                        imageView.image = image;
                    });
                });
            }
        }
    }
}

- (void)mapView:(MKMapView*)mapView annotationView:(MKAnnotationView*)view calloutAccessoryControlTapped:(UIControl*)control {
    if ([control isEqual:view.rightCalloutAccessoryView]) {
        [self performSegueWithIdentifier:@"ShowFriendFromMap" sender:view];
    }
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ShowFriendFromMap"]) {
        if ([segue.destinationViewController isKindOfClass:[FLFriendTableDetailVC class]]) {
            FLFriendTableDetailVC* viewController = segue.destinationViewController;
            if ([sender isKindOfClass:[MKAnnotationView class]]) {
                id<MKAnnotation> annotation = ((MKAnnotationView*) sender).annotation;
                if ([annotation isKindOfClass:[FLFriend class]]) {
                    viewController.theFriend = (FLFriend*) annotation;
                }
            }
        }
    }
}

@end
