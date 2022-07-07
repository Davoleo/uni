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

/// @return the weather API KEY from the environment variables
+ (NSString*)getWeatherAPIKey {
    return [[[NSProcessInfo processInfo] environment] objectForKey:@"WEATHER_API_KEY"];
}

/// Queries the OneCall API of https://openweathermap.org [currently unused]
+ (void)queryOneCallAPIInPoi:(MWPoi*)poi AndThen:(MWForecastConsumer)doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/onecall?lat=%lf&lon=%lf&exclude=alerts,minutely&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil || data == nil) {
            NSLog(@"Error while requesting OneCall Weather Information");
            return;
        }
        MWForecast* forecast = [[MWForecast alloc] initWithOneCallJSONData:data AndPoi:poi];
        doThis(forecast);
    }];
    [task resume];
}

/// Queries the CurrentWeather from https://openweathermap.org
+ (void) queryCurrentWeatherInLocation: (MWPoi*) poi AndThen: (MWWeatherDataConsumer) doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/weather?lat=%f&lon=%lf&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil || data == nil) {
            NSLog(@"Error while requesting Current Weather Information");
            return;
        }
        MWWeatherData* currentWeather = [[MWWeatherData alloc] initWithJSONData:data];
        doThis(currentWeather);
    }];

    [task resume];
}

/// Queries the Forecast 2.5 object from https://openweathermap.org API
+ (void) queryForecastInLocation: (MWPoi*) poi AndThen: (MWForecastConsumer) doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/forecast?lat=%lf&lon=%lf&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil || data == nil) {
            NSLog(@"Error while requesting Forecast Information");
            return;
        }
        [MWUtils queryCurrentWeatherInLocation:poi AndThen:^(MWWeatherData* current) {
            MWForecast* currentForecast = [[MWForecast alloc] initWithJSONForecast:data AndCurrentWeather:current InPoi:poi];
            doThis(currentForecast);
        }];
    }];

    [task resume];
}

/// Converts temperature in a certain metrics and returns with the correct format as a string
/// @param temperature The input temperature [in Kelvins]
/// @param metric The metric to convert the temperature to
/// @return The output temperature, formatted correctly as a string and converted to the specified metric
+(NSString*) temperature: (double) temperature FormattedInMetric: (MWTemperatureMetrics) metric {

    switch (metric) {
        case MWTemperatureMetricCelsius:
            return [NSString stringWithFormat:@"%.1f°C", temperature - 273.15];
        case MWTemperatureMetricFahrenheit:
            return [NSString stringWithFormat:@"%.1f°F", ((temperature - 273.15) * 9/5) + 32];
        case MWTemperatureMetricKelvin:
            return [NSString stringWithFormat:@"%.1f°K", temperature];
        default:
            NSAssert(false, @"Unknown Temperature Metric not allowed!");
            return @"---";
    }
}


@end
