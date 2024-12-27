//
// Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/// Contains Singleton instances of Service classes to be used inside the app
@interface MWManagers : NSObject

+ (CLGeocoder*) geocoder;

+ (CLLocationManager*) locationManager;

@end