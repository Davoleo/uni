//
//  MWCurrentWeatherDetailVC.h
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import <UIKit/UIKit.h>
#import "MWWeatherData.h"
#import "MWPoi.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWCurrentWeatherDetailVC : UIViewController

//Weak since this object is actually property of the enclosing View Controller and I don't want to steal it
@property (nonatomic, weak) MWPoi* position;
@property (nonatomic, strong) MWWeatherData* currentWeather;

@end

NS_ASSUME_NONNULL_END
