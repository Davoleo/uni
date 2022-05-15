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

    [MWUtils queryWeatherAPIForPoi:[MWPoi poiWithLatitude:44 longitude:33] AndThen:^(MWWeather* weather){/* noop test */}];

    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
