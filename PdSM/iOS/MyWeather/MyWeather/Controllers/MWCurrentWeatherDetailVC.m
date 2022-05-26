//
//  MWCurrentWeatherDetailVC.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWCurrentWeatherDetailVC.h"
#import "MWUtils.h"

@interface MWCurrentWeatherDetailVC ()

@property (weak, nonatomic) IBOutlet UIImageView *weatherIconView;

@property (weak, nonatomic) IBOutlet UILabel *placemarkLabel;
@property (weak, nonatomic) IBOutlet UILabel *temperatureLabel;
@property (weak, nonatomic) IBOutlet UILabel *conditionsLabel;

@end

@implementation MWCurrentWeatherDetailVC

- (void)viewDidLoad {
    [super viewDidLoad];

    //Attach map pin image to location name & create NSString
    NSTextAttachment* attachment = [[NSTextAttachment alloc] init];
    attachment.image = [UIImage systemImageNamed:@"mappin"];
    NSAttributedString* attachmentString = [NSAttributedString attributedStringWithAttachment:attachment];
    NSMutableAttributedString* string = [[NSMutableAttributedString alloc] initWithString:self.position.placemarkCache.name];
    [string appendAttributedString:attachmentString];

    //Current Temperature formatting
    MWTemperatureMetricsEnum tempMetric = (MWTemperatureMetricsEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%lf°%c", self.weather.temperature, [MWUtils temperatureFormatCharForMetric:tempMetric]];

    BOOL isNight = self.weather.timestamp > self.weather.sunset || self.weather.timestamp < self.weather.sunrise;
    NSString* iconName = [self.weather.condition decodeSystemImageNameAtNight:isNight];
    self.weatherIconView.image = [UIImage systemImageNamed:iconName];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
