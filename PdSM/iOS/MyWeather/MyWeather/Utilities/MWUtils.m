//
//  Utils.m
//  MyWeather
//
//  Created by Leo Dav on 15/05/22.
//

#import "MWUtils.h"

@implementation MWUtils

+ (NSString*)getWeatherAPIKey {
    return [[[NSProcessInfo processInfo] environment] objectForKey:@"WEATHER_API_KEY"];
}

+ (void)queryWeatherAPIForPoi:(MWPoi*)poi AndThen:(MWForecastConsumer)doThis {
    NSString* urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/onecall?lat=%lf&lon=%lf&exclude=alerts,minutely&appid=%@",
            poi.latitude, poi.longitude, [MWUtils getWeatherAPIKey]];
    NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    NSURLSessionTask* task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData* data, NSURLResponse* response, NSError* error) {
        if (error != nil)
        {
            NSLog(@"Error while requesting OneCall Weather Information");
        }
        NSLog(@"%@", [NSString stringWithUTF8String:[data bytes]]);
    }];
    [task resume];
}

//+ (void) queryCurrentWeatherInLocation: (MWPoi*) poi

@end
