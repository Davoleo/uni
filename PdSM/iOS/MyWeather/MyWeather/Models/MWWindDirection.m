//
// Created by Leo Dav on 16/05/22.
//

#import "MWWindDirection.h"


@implementation MWWindDirection


+ (MWWindDirection*)fromDegrees:(float)degrees {
    MWWindDirection* windDirection = [MWWindDirection alloc];

    if (degrees >= 348.75 || degrees < 11.25)
        windDirection->_direction = @"N";
    else if (degrees >= 11.25 && degrees < 33.75)
        windDirection->_direction = @"NNE";
    else if (degrees >= 33.75 && degrees < 56.25)
        windDirection->_direction = @"NE";
    else if (degrees >= 56.25 && degrees < 78.75)
        windDirection->_direction = @"ENE";
    else if (degrees >= 78.75 && degrees < 101.25)
        windDirection->_direction = @"E";
    else if (degrees >= 101.25 && degrees < 123.75)
        windDirection->_direction = @"ESE";
    else if (degrees >= 123.75 && degrees < 146.25)
        windDirection->_direction = @"SE";
    else if (degrees >= 146.25 && degrees < 168.75)
        windDirection->_direction = @"SSE";
    else if (degrees >= 168.75 && degrees < 191.25)
        windDirection->_direction = @"S";
    else if (degrees >= 191.25 && degrees < 213.75)
        windDirection->_direction = @"SSW";
    else if (degrees >= 213.75 && degrees < 236.25)
        windDirection->_direction = @"SW";
    else if (degrees >= 236.25 && degrees < 258.75)
        windDirection->_direction = @"WSW";
    else if (degrees >= 258.75 && degrees < 281.25)
        windDirection->_direction = @"W";
    else if (degrees >= 281.25 && degrees < 303.75)
        windDirection->_direction = @"WNW";
    else if (degrees >= 303.75 && degrees < 326.25)
        windDirection->_direction = @"NW";
    else if (degrees >= 326.25 && degrees < 348.75)
        windDirection->_direction = @"NW";
    else
        windDirection->_direction  = @"UNDEFINED";


    windDirection->_degrees = degrees;

    return windDirection;
}

@end

