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


+ (void) queryWeatherAPIForPoi: (MWPoi*) poi AndThen: (MWForecastConsumer) doThis;



@end

NS_ASSUME_NONNULL_END
