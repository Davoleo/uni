//
//  AppDelegate.m
//  MyWeather
//
//  Created by Leo Dav on 08/05/22.
//

#import "AppDelegate.h"
#import "MWSettings.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication*)application {
    MWThemeEnum themeOverrideValue = (MWThemeEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_THEME_PREF];
    if (themeOverrideValue != SYSTEM) {
        if (themeOverrideValue == LIGHT) {
            self.window.overrideUserInterfaceStyle = UIUserInterfaceStyleLight;
        }
        else { //DARK
            self.window.overrideUserInterfaceStyle = UIUserInterfaceStyleDark;
        }
    }
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}


@end
