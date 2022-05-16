//
//  main.m
//  MyWeather
//
//  Created by Leo Dav on 08/05/22.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MWUtils.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }

    [MWUtils queryWeatherAPIInPoi:[MWPoi poiWithLatitude:44 longitude:33] AndThen:^(MWForecast* forecast) {
        NSLog(@"%@", forecast.current.windDirection.direction);
    }];

    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
