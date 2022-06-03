//
// Created by Leo Dav on 15/05/22.
//

#import "MWForecast.h"
#import "MWUtils.h"

@implementation MWForecast

- (instancetype)initWithOneCallJSONData:(NSData*)data AndPoi: (MWPoi*)poi {
    self = [super init];

    if (self) {
        _location = poi;

        NSError* error;
        id obj = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingTopLevelDictionaryAssumed error:&error];
        NSAssert(error == nil, @"Error while deserializing forecast information");

        if([obj isKindOfClass:[NSDictionary class]]) {

            //Current Weather Deserialization
            _current = [[MWWeatherData alloc] initWithJSONObj:obj[@"current"]];

            //Hourly Weather Deserialization
            NSArray* jsonArr = obj[@"hourly"];
            NSMutableArray<MWWeatherData*>* hourlyArr = [NSMutableArray arrayWithCapacity:jsonArr.count];
            [jsonArr enumerateObjectsUsingBlock:^(id hourlyObj, NSUInteger index, BOOL* stop) {
                if ([hourlyObj isKindOfClass:[NSDictionary class]]) {
                    [hourlyArr addObject:[[MWWeatherData alloc] initWithJSONObj:hourlyObj]];
                }
            }];
            _hourly = hourlyArr;

            //Daily Weather Deserialization
            jsonArr = obj[@"daily"];
            NSMutableArray<MWWeatherData*>* dailyArr = [NSMutableArray arrayWithCapacity:jsonArr.count];
            [jsonArr enumerateObjectsUsingBlock:^(id dailyObj, NSUInteger index, BOOL* stop) {
                if ([dailyObj isKindOfClass:[NSDictionary class]]) {
                    [hourlyArr addObject:[[MWWeatherData alloc] initWithJSONObj:dailyObj]];
                }
            }];
            _daily = dailyArr;
        }
    }

    return self;
}

- (instancetype)initWithJSONForecast:(NSData*)forecast AndCurrentWeather:(MWWeatherData*)currentWeather InPoi: (MWPoi*)poi {
    self = [super init];

    if (self) {
        _location = poi;
        _current = currentWeather;

        NSError* error;
        id forecastObj = [NSJSONSerialization JSONObjectWithData:forecast options:NSJSONReadingTopLevelDictionaryAssumed error:&error];
        NSAssert(error == nil, @"Error while deserializing forecast information");

        if([forecastObj isKindOfClass:[NSDictionary class]]) {

            NSArray* weatherList = forecastObj[@"list"];
            NSMutableArray<MWWeatherData*>* hourlyArr = [NSMutableArray array];
            NSMutableArray<MWWeatherData*>* dailyArr = [NSMutableArray array];
            [weatherList enumerateObjectsUsingBlock:^(id weatherObj, NSUInteger index, BOOL* stop) {
                if ([weatherObj isKindOfClass:[NSDictionary class]]) {
                    NSUInteger timestamp = [weatherObj[@"dt"] unsignedLongValue];
                    if ([NSDate dateWithTimeIntervalSince1970:timestamp].timeIntervalSinceNow < 60 * 60 * 24) {
                        [hourlyArr addObject:[[MWWeatherData alloc] initWithJSONObj:weatherObj]];
                    }
                    else {
                        [dailyArr addObject:[[MWWeatherData alloc] initWithJSONObj:weatherObj]];
                    }
                }
            }];

            _hourly = hourlyArr;
            _daily = dailyArr;
        }
    }

    return self;
}


- (void)refreshCurrentWeather {
    [MWUtils queryCurrentWeatherInLocation:self.location AndThen:^(MWWeatherData* currentWeather) {
        self.current = currentWeather;
    }];
}

@end