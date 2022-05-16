//
// Created by Leo Dav on 15/05/22.
//

#import "MWWeatherData.h"

const double MW_UNDEFINED_TEMPERATURE = DBL_MAX;

@implementation MWWeatherData

- (void)initTemperatureAndHumidity:(NSDictionary*)jsonObj {
    id temperature = jsonObj[@"temp"];
    if ([temperature isKindOfClass:[NSDictionary class]]) {
        //We're deserializing daily forecast => current temperature stats not present
        _temperature = MW_UNDEFINED_TEMPERATURE;
        _maxTemperature = [temperature[@"max"] doubleValue];
        _minTemperature = [temperature[@"min"] doubleValue];
    }
    else {
        _temperature = [jsonObj[@"temp"] doubleValue];
        _maxTemperature = [jsonObj[@"temp_max"] doubleValue];
        _minTemperature = [jsonObj[@"temp_min"] doubleValue];
    }

    _humidity = [jsonObj[@"humidity"] intValue] / 100.0F;
}

- (void) initWindStatsWithDict:(NSDictionary*)jsonObj HasKeyPrefix:(BOOL) hasPrefix {
    NSString* prefix = hasPrefix ? @"wind_" : @"";
    _windSpeed = [jsonObj[[NSString stringWithFormat:@"%@speed", prefix]] doubleValue];
    int deg = [jsonObj[[NSString stringWithFormat:@"%@deg", prefix]] intValue];
    _windDirection = [MWWindDirection fromDegrees:deg];
}

- (instancetype)initWithJSONObj: (NSDictionary*) weatherData {
    self = [super init];

    if (self) {
        _timestamp = [weatherData[@"dt"] unsignedLongValue];

        NSDictionary* main = weatherData[@"main"];
        if (main != nil)
            [self initTemperatureAndHumidity:main];
        else
            [self initTemperatureAndHumidity:weatherData];

        NSDictionary* wind = weatherData[@"wind"];
        if (wind != nil)
            [self initWindStatsWithDict:wind HasKeyPrefix:NO];
        else
            [self initWindStatsWithDict:wind HasKeyPrefix:YES];

        id clouds = weatherData[@"clouds"];
        if ([clouds isKindOfClass:[NSDictionary class]])
            _cloudiness = [clouds[@"all"] floatValue];
        else if ([clouds isKindOfClass:[NSNumber class]])
            _cloudiness = [clouds floatValue];

        NSNumber* pop = weatherData[@"pop"];
        _pop = pop != nil ? [pop doubleValue] : -1;

        NSDictionary* weatherCondition = [weatherData[@"weather"] firstObject];
        _condition = [[MWWeatherCondition alloc] initWithJSONObject:weatherCondition];
    }

    return self;
}

- (instancetype)initWithJSONData:(NSData*)data {
    self = [super init];

    NSError* error;
    id obj = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingTopLevelDictionaryAssumed error:&error];
    if ([obj isKindOfClass:[NSDictionary class]]) {
        NSDictionary* weatherData = (NSDictionary*) obj;
        return [self initWithJSONObj:weatherData];
    }
    else return nil;
}

@end