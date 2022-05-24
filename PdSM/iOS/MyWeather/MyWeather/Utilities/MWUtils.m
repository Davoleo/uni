//
//  Utils.m
//  MyWeather
//
//  Created by Leo Dav on 15/05/22.
//

#import "MWUtils.h"

/**
 * Contains different Convenience static methods
 */
@implementation MWUtils

+ (NSString*)getWeatherAPIKey {
    return [[[NSProcessInfo processInfo] environment] objectForKey:@"WEATHER_API_KEY"];
}

+ (void)queryWeatherAPIInPoi:(MWPoi*)poi AndThen:(MWForecastConsumer)doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/onecall?lat=%lf&lon=%lf&exclude=alerts,minutely&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil || data == nil) {
            NSLog(@"Error while requesting OneCall Weather Information");
            return;
        }
        MWForecast* forecast = [[MWForecast alloc] initWithJSONData:data AndPoi:poi];
        doThis(forecast);
    }];
    [task resume];
}

+ (void) queryCurrentWeatherInLocation: (MWPoi*) poi AndThen: (MWWeatherDataConsumer) doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/weather?lat=%lf&lon=%lf&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil || data == nil) {
            NSLog(@"Error while requesting OneCall Weather Information");
            return;
        }
        MWWeatherData* currentWeather = [[MWWeatherData alloc] initWithJSONData:data];
        doThis(currentWeather);
    }];

    [task resume];
}

+ (char)temperatureFormatCharForMetric:(MWTemperatureMetricsEnum)metric {
    switch (metric) {
        case CELSIUS:
            return 'C';
        case FAHRENHEIT:
            return 'F';
        case KELVIN:
            return 'K';
        default:
            NSAssert(false, @"No, non puoi essere qua dio bono");
            return '-';
    }
}


@end
