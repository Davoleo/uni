//
// Created by Leo Dav on 16/05/22.
//

#import "MWWindDirection.h"


@implementation MWWindDirection


+ (MWWindDirection*)fromDegrees:(float)degrees {
    MWWindDirection* windDirection = [MWWindDirection alloc];

    if (degrees >= 326.25 || degrees < 33.75) {
        if (degrees >= 11.25)
            windDirection->_direction = @"NNE";
        else if (degrees >= 348.75)
            windDirection->_direction = @"N";
        else
            windDirection->_direction = @"NNW";

        windDirection->_iconName = @"arrow.up";
    }
    else if (degrees >= 33.75 && degrees < 56.25) {
        windDirection->_direction = @"NE";
        windDirection->_iconName = @"arrow.up.right";
    }
    else if (degrees >= 56.25 && degrees < 146.25) {
        if (degrees >= 101.25)
            windDirection->_direction = @"ESE";
        else if (degrees >= 78.75)
            windDirection->_direction = @"E";
        else
            windDirection->_direction = @"ENE";

        windDirection->_iconName = @"arrow.right";
    }
    else if (degrees >= 123.75 && degrees < 146.25) {
        windDirection->_direction = @"SE";
        windDirection->_iconName = @"arrow.down.right";
    }
    else if (degrees >= 146.25) {
        if (degrees >= 191.25)
            windDirection->_direction = @"SSW";
        else if (degrees >= 168.75)
            windDirection->_direction = @"S";
        else
            windDirection->_direction = @"SSE";

        windDirection->_iconName = @"arrow.down";
    }
    else if (degrees >= 213.75 && degrees < 236.25) {
        windDirection->_direction = @"SW";
        windDirection->_iconName = @"arrow.down.left";
    }
    else if (degrees >= 236.25) {
        if (degrees >= 281.25)
            windDirection->_direction = @"WNW";
        else if (degrees >= 258.75)
            windDirection->_direction = @"W";
        else
            windDirection->_direction = @"WSW";

        windDirection->_iconName = @"arrow.left";
    }
    else if (degrees >= 303.75 && degrees < 326.25) {
        windDirection->_direction = @"NW";
        windDirection->_iconName = @"arrow.up.left";
    }
    else {
        windDirection->_direction  = @"UNDEFINED";
        windDirection->_iconName = @"arrow.triangle.swap";
    }

    windDirection->_degrees = degrees;

    return windDirection;
}

@end

