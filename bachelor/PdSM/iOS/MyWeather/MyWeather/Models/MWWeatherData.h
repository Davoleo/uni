//
// Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import "MWWeatherCondition.h"
#import "MWWindDirection.h"

FOUNDATION_EXPORT const double MW_UNDEFINED_TEMPERATURE;

@interface MWWeatherData : NSObject

@property (nonatomic, readonly) NSUInteger timestamp;
@property (nonatomic, readonly) NSUInteger sunset;
@property (nonatomic, readonly) NSUInteger sunrise;

@property (nonatomic, readonly) double temperature;
@property (nonatomic, readonly) double maxTemperature;
@property (nonatomic, readonly) double minTemperature;

@property (nonatomic, readonly) float humidity;


@property (nonatomic, readonly) double windSpeed;
@property (nonatomic, readonly) MWWindDirection* windDirection;

@property (nonatomic, readonly) float cloudiness;

@property (nonatomic, readonly) double pop;

@property (nonatomic, strong) MWWeatherCondition* condition;


- (instancetype)initWithJSONObj:(NSDictionary*)weatherData;

- (instancetype)initWithJSONData:(NSData*)data;

@end

typedef void (^MWWeatherDataConsumer)(MWWeatherData* weatherInfo);