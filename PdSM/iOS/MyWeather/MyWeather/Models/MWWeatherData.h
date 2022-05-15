//
// Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>

@interface MWWeatherData : NSObject

@property (nonatomic, readonly) NSUInteger timestamp;
@property (nonatomic, readonly) double temperature;
@property (nonatomic, readonly) double feltTemperature;

@property (nonatomic, readonly) float humidity;

@property (nonatomic, readonly) double windSpeed;
@property (nonatomic, readonly) NSString* windDirection;

@property (nonatomic, readonly) double pop;

@end