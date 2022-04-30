//
// Created by Leo Dav on 30/04/2022.
//

#import "FLPoi.h"


@implementation FLPoi

- (instancetype)initWithName:(NSString*)name latitude:(double)latitude longitude:(double)longitude {
    if (self = [super init]) {
        _name = [name copy];
        _latitude = latitude;
        _longitude = longitude;
    }

    return self;
}

@end