//
// Created by Leo Dav on 21/06/22.
//

#import "MWPoi+WeatherAnnotation.h"


@implementation MWPoi (WeatherAnnotation)

- (CLLocationCoordinate2D)coordinate {
    CLLocationCoordinate2D coord;
    coord.latitude = self.latitude;
    coord.longitude = self.longitude;
    return coord;
}

- (NSString*)title {
    return self.placemarkCache.name;
}

@end