//
// Created by Leo Dav on 16/05/22.
//

#import "MWWeatherCondition.h"


@implementation MWWeatherCondition {

}
- (instancetype)initWithJSONObject:(NSDictionary*)json {
    self = [super init];

    if (self) {
        _id = [json[@"id"] intValue];
        _name = json[@"main"];
        _smallDesc = json[@"description"];
    }

    return self;
}

@end