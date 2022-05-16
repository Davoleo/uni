//
//  Utils.h
//  MyWeather
//
//  Created by Leo Dav on 15/05/22.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "MWForecast.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWUtils : NSObject

+ (NSString*) getWeatherAPIKey;


+ (void)queryWeatherAPIInPoi:(MWPoi*)poi AndThen: (MWForecastConsumer) doThis;

+ (void)queryCurrentWeatherInLocation:(MWPoi*)poi AndThen:(MWWeatherDataConsumer)doThis;
@end

NS_ASSUME_NONNULL_END
