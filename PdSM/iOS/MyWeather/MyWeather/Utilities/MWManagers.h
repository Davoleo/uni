//
// Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


@interface MWManagers : NSObject

+ (CLGeocoder*) geocoder;

+ (CLLocationManager*) locationManager;

@end