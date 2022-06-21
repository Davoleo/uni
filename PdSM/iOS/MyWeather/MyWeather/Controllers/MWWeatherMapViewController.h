//
//  MWWeatherMapViewController.h
//  MyWeather
//
//  Created by Leo Dav on 21/06/22.
//

#import <UIKit/UIKit.h>
#import "MWPoi.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWWeatherMapViewController : UIViewController

@property (strong, nonatomic) NSArray<MWPoi*>* positions;

@end

NS_ASSUME_NONNULL_END
