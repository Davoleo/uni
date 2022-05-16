//
// Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef void (^MWPlacemarkHandler)(CLPlacemark* placemark);

@interface MWPoi : NSObject

@property (nonatomic, readonly) double latitude;
@property (nonatomic, readonly) double longitude;

@property (nonatomic, strong) CLPlacemark* placemarkCache;

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache;

+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache;

+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude;

// -------------------------

- (void)reverseGeocode;

-(void)reverseGeocodeAndThen: (MWPlacemarkHandler)handler;

- (void)invalidatePlacemark;

@end