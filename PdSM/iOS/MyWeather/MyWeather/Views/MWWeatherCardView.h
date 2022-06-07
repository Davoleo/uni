//
//  MWWeatherCardView.h
//  MyWeather
//
//  Created by Leo Dav on 05/06/22.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MWWeatherCardView : UIView

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *dateLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *weatherIcon;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *conditionsLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *temperatureLabel;

@end

NS_ASSUME_NONNULL_END
