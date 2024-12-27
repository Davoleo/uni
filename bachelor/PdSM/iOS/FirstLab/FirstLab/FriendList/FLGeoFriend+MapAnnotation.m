//
// Created by Leo Dav on 30/04/2022.
//

#import "FLGeoFriend+MapAnnotation.h"


@implementation FLGeoFriend (MapAnnotation)

- (CLLocationCoordinate2D)coordinate {
    CLLocationCoordinate2D result;
    result.latitude = self.location.latitude;
    result.longitude = self.location.longitude;
    return result;
}

- (NSString*)title {
    return self.displayName;
}


@end