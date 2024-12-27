//
//  MWWeatherMapViewController.h
//  MyWeather
//
//  Created by Leo Dav on 21/06/22.
//

#import <UIKit/UIKit.h>
#import "MWPoi.h"
#import "MWWeatherCondition.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWWeatherMapViewController : UIViewController

@property (strong, nonatomic) NSArray<MWPoi*>* positions;
@property (strong, nonatomic) NSArray<MWWeatherCondition*>* conditions;

@end

NS_ASSUME_NONNULL_END
