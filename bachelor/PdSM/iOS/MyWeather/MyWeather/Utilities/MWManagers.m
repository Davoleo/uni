//
// Created by Leo Dav on 15/05/22.
//

#import "MWManagers.h"

static CLGeocoder* _geocoder;
static CLLocationManager* _locationManager;

@implementation MWManagers

/// @return CLGeocoder service class instance, if it's present, otherwise it allocates and returns it
+ (CLGeocoder*)geocoder {
    if (!_geocoder) {
        _geocoder = [[CLGeocoder alloc] init];
    }
    return _geocoder;
}

/// @return CLLocationManager service instance, if it's present, otherwise it allocates and configures it and return the new instance
+ (CLLocationManager*)locationManager {
    if (!_locationManager) {
        _locationManager = [[CLLocationManager alloc] init];
        _locationManager.desiredAccuracy = kCLLocationAccuracyKilometer;
        _locationManager.distanceFilter = 500;
        _locationManager.activityType = CLActivityTypeOther;
    }
    return _locationManager;
}


@end