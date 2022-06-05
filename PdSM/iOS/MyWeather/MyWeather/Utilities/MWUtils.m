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

+ (char)temperatureFormatCharForMetric:(MWTemperatureMetrics)metric {
    switch (metric) {
        case MWTemperatureMetricCelsius:
            return 'C';
        case MWTemperatureMetricFahrenheit:
            return 'F';
        case MWTemperatureMetricKelvin:
            return 'K';
        default:
            NSAssert(false, @"Unknown Temperature Metric not allowed!");
            return '-';
    }
}

+ (double)getTemperature:(double)temperature InMetric:(MWTemperatureMetrics)metric {
    switch (metric) {
        case MWTemperatureMetricCelsius:
            return temperature - 273.15;
        case MWTemperatureMetricFahrenheit:
            return ((temperature - 273.15) * 9/5) + 32;
        case MWTemperatureMetricKelvin:
            return temperature;
        default:
            NSAssert(false, @"Unknown Temperature Metric not allowed!");
            return temperature;
    }
}


@end
