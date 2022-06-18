//
// Created by Leo Dav on 15/05/22.
//

#import "MWPoi.h"
#import "MWManagers.h"


@implementation MWPoi

///--- Initializers ---///

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude {
    return [self initWithLatitude:latitude longitude:longitude placemarkCache:nil];
}

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache {
    self = [super init];
    if (self) {
        _latitude = latitude;
        _longitude = longitude;
        _placemarkCache = placemarkCache;
        _timezoneOffset = NSIntegerMin;
    }

    return self;
}

+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache {
    return [[self alloc] initWithLatitude:latitude longitude:longitude placemarkCache:placemarkCache];
}
+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude {
    return [[self alloc] initWithLatitude:latitude longitude:longitude];
}


///--- Utility ---///

- (void) reverseGeocode {
    [self reverseGeocodeAndThen:^(CLPlacemark* placemark){ /* noop */ }];
}

- (void)reverseGeocodeAndThen:(MWPlacemarkHandler)handler {
    if (self.placemarkCache != nil) {
        handler(self.placemarkCache);
    }
    else {
        CLLocation* location = [[CLLocation alloc] initWithLatitude:self.latitude longitude:self.longitude];
        [MWManagers.geocoder reverseGeocodeLocation:location completionHandler:^(NSArray* placemarks, NSError* error) {
            if (error == nil && placemarks != nil) {
                id obj = placemarks.firstObject;
                if ([obj isKindOfClass:[CLPlacemark class]]) {
                    CLPlacemark* placemark = (CLPlacemark*) obj;
                    //Save current placemark in the cache so that we don't have to geocode it again
                    self.placemarkCache = placemark;
                    handler(placemark);
                }
            }
            else {
                NSLog(@"Error while reverse geocoding POI!");
            }
        }];
    }
}

- (void) invalidatePlacemark {
    self.placemarkCache = nil;
}

- (NSString*) toString {
    return [NSString stringWithFormat:@"%lf^%lf", self.latitude, self.longitude];
}

- (BOOL) hasTimezoneOffset {
    return self.timezoneOffset != NSIntegerMin;
}

+ (void)geocode: (NSString*)placeName AndThen: (void (^)(MWPoi* poi)) doThis {
    [[MWManagers geocoder] geocodeAddressString:placeName completionHandler:^(NSArray<CLPlacemark*>* placemarks, NSError* error) {
        CLLocationCoordinate2D coords = placemarks.firstObject.location.coordinate;
        MWPoi* poi = [MWPoi poiWithLatitude:coords.latitude longitude:coords.longitude];
        poi.placemarkCache = placemarks.firstObject;
        doThis(poi);
    }];
}

@end
