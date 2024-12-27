//
// Created by Leo Dav on 21/06/22.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "MWPoi.h"

/// Extension of the MWPoi class to conform to the protocol MKAnnotation (to be added as annotation on the app map)
@interface MWPoi (WeatherAnnotation)<MKAnnotation>

@end