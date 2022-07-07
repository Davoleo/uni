//
// Created by Leo Dav on 16/05/22.
//

#import "MWWeatherCondition.h"


@implementation MWWeatherCondition {

}

/// @return The System Icon name depending on the weather condition of self
- (NSString*) decodeSystemImageName {
    int id = self.id;

    //Group 2xx (Thunderstorm)
    if ((id >= 200 && id <= 202) || (id >= 230 && id <= 232)) {
        return @"cloud.bolt.rain.fill";
    }
    if (id >= 210 && id <= 221) {
        return @"cloud.bolt.fill";
    }

    //Group 3xx (Drizzle)
    if (id >= 300 && 330 > id) {
        return @"cloud.drizzle.fill";
    }

    //Group 5xx (Rain)
    if ((id >= 520 && id <= 531) || (id >= 502 && id <= 504)) {
        return @"cloud.heavyrain.fill";
    }
    if (id == 500 || id == 501) {
        return @"cloud.rain.fill";
    }
    if (id == 511) {
        return @"cloud.sleet.fill";
    }

    //Group 6xx (Snow)
    if (id == 600) {
        return @"snowflake";
    }
    if (id == 601 || id == 602 || (id > 620 && id <= 622)) {
        return @"cloud.snow.fill";
    }
    if (id >= 611 && id <= 616) {
        return @"cloud.sleet.fill";
    }

    //Group 7xx (Atmosphere)
    if (id == 701 || id == 741) {
        return @"cloud.fog.fill";
    }
    if (id == 711) {
        return @"smoke.fill";
    }
    if (id == 721) {
        return @"sun.haze.fill";
    }
    if (id == 731 || id == 751 || id == 761 || id == 762) {
        return @"sun.dust.fill";
    }
    if (id == 771) {
        return @"wind.snow";
    }
    if (id == 781) {
        return @"tornado";
    }

    //Group 800 (Clear)
    if (id == 800) {
        return self.night ? @"moon.fill" : @"sun.max.fill";
    }

    //Group 80x (Clouds)
    if (id == 801 || id == 802) {
        return self.night ? @"cloud.moon.fill" : @"cloud.sun.fill";
    }
    if (id == 803 || id == 804) {
        return @"cloud.fill";
    }

    NSLog(@"Unknown Weather condition, assuming \"variable\"");
    return self.night ? @"cloud.moon.rain.fill" : @"cloud.sun.rain.fill";
}

- (instancetype)initWithJSONObject:(NSDictionary*)json {
    self = [super init];

    if (self) {
        _id = [json[@"id"] intValue];
        _name = json[@"main"];
        _smallDesc = json[@"description"];
        //If icon has n at the end it means it's nighttime
        _night = [((NSString*)  json[@"icon"]) hasSuffix:@"n"];
    }

    return self;
}

@end