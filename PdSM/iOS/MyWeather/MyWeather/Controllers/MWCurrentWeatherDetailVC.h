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

@property (nonatomic, strong) MWPoi* position;
@property (nonatomic, strong) MWWeatherData* weather;

@end

NS_ASSUME_NONNULL_END
