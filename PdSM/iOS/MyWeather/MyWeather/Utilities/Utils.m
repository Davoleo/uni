//
//  Utils.m
//  MyWeather
//
//  Created by Leo Dav on 15/05/22.
//

#import "Utils.h"

@implementation Utils

+ (NSString*)getWeatherAPIKey {
    return [[[NSProcessInfo processInfo] environment] objectForKey:@"WEATHER_API_KEY"];
}


@end
