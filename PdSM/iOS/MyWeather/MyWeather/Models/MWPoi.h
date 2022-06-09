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

@property (nonatomic) NSInteger timezoneOffset;

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;

- (instancetype)initWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache;

+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude placemarkCache:(CLPlacemark*)placemarkCache;

+ (instancetype)poiWithLatitude:(double)latitude longitude:(double)longitude;

// -------------------------

+ (MWPoi*)poiFromString:(NSString*)serializedPoi;

- (void)reverseGeocode;

-(void)reverseGeocodeAndThen: (MWPlacemarkHandler)handler;

- (void)invalidatePlacemark;

- (NSString*)toString;
@end
