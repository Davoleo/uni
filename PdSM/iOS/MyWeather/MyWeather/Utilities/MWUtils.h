//
//  Utils.h
//  MyWeather
//
//  Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "MWForecast.h"
#import "MWSettings.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWUtils : NSObject

+ (NSString*) getWeatherAPIKey;


+ (void)queryOneCallAPIInPoi:(MWPoi*)poi AndThen: (MWForecastConsumer) doThis;

+ (void)queryCurrentWeatherInLocation:(MWPoi*)poi AndThen:(MWWeatherDataConsumer)doThis;

+ (void)queryForecastInLocation:(MWPoi*)poi AndThen:(MWForecastConsumer)doThis;

+ (NSString*)temperature:(double)temperature FormattedInMetric:(MWTemperatureMetrics)metric;

@end

NS_ASSUME_NONNULL_END
