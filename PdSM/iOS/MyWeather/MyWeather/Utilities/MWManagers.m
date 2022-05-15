//
// Created by Leo Dav on 15/05/22.
//

#import "MWManagers.h"

static CLGeocoder* _geocoder;

@implementation MWManagers

+ (CLGeocoder*)geocoder {
    if (!_geocoder) {
        _geocoder = [[CLGeocoder alloc] init];
    }
    return _geocoder;
}

@end