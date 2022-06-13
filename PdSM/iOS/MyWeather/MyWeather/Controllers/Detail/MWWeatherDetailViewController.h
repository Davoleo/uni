//
//  MWWeatherDetailViewController.h
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import <UIKit/UIKit.h>
#import "MWPoi.h"
#import "MWForecast.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWWeatherDetailViewController : UIViewController

//~~Weak since this object is actually property of the enclosing View Controller and I don't want to steal it~~
@property (nonatomic, strong) MWPoi* position;
@property (nonatomic, strong) MWForecast* forecast;

@end

NS_ASSUME_NONNULL_END
