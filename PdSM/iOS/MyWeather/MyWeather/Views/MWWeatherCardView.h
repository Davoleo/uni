//
//  MWWeatherCardView.h
//  MyWeather
//
//  Created by Leo Dav on 05/06/22.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// Card view widget component that stores:
/// <ol>
/// <li>The Date/Time of the displayed weather</li>
/// <li>The Icon, representing the weather condition </li>
/// <li>Small name of the current weather condition </li>
/// <li>Minimum and Maximum Temperature at that time </li>
/// </ol>
@interface MWWeatherCardView : UIView

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *dateLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *weatherIcon;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *conditionsLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *temperatureLabel;

@end

NS_ASSUME_NONNULL_END
