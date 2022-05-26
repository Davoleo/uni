//
// Created by Leo Dav on 24/05/22.
//

#import <Foundation/Foundation.h>

static NSString* MW_TEMPERATURE_METRIC_PREF = @"temperature_metric_pref";
static NSString* MW_THEME_PREF = @"theme_pref";

typedef NS_ENUM(NSInteger, MWTemperatureMetricsEnum) {
    CELSIUS = 0,
    FAHRENHEIT = 1,
    KELVIN = 2
};

typedef NS_ENUM(NSInteger, MWThemeEnum) {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2
};