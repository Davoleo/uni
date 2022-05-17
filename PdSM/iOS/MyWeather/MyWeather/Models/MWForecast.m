//
// Created by Leo Dav on 15/05/22.
//

#import "MWForecast.h"
#import "MWUtils.h"

@implementation MWForecast

- (instancetype)initWithJSONData:(NSData*)data AndPoi: (MWPoi*)poi {
    self = [super init];

    if (self) {
        _location = poi;

        NSError* error;
        id obj = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingTopLevelDictionaryAssumed error:&error];

        if([obj isKindOfClass:[NSDictionary class]]) {
            NSDictionary* forecast = (NSDictionary*) obj;

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

- (void)refreshCurrentWeather {
    [MWUtils queryCurrentWeatherInLocation:self.location AndThen:^(MWWeatherData* currentWeather) {
        self.current = currentWeather;
    }];
}

@end