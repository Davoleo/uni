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

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *loadingIndicator;

@end

@implementation MWCurrentWeatherDetailVC

- (void)viewDidLoad {
    [super viewDidLoad];

    NSAssert(self.position != nil, @"View Controller can't be initialized with nil position");
    if (self.currentWeather == nil) {
        [MWUtils queryCurrentWeatherInLocation:self.position AndThen:^(MWWeatherData* data) {
            self.currentWeather = data;
            [self setupUI];
            [self.loadingIndicator stopAnimating];
        }];
    }
}

- (void) setupUI {
    //Attach map pin image to location name & create NSString
    NSTextAttachment* attachment = [[NSTextAttachment alloc] init];
    attachment.image = [UIImage systemImageNamed:@"mappin"];
    NSAttributedString* attachmentString = [NSAttributedString attributedStringWithAttachment:attachment];
    NSMutableAttributedString* string = [[NSMutableAttributedString alloc] initWithString:self.position.placemarkCache.name];
    [string appendAttributedString:attachmentString];

    //Current Temperature formatting
    MWTemperatureMetricsEnum tempMetric = (MWTemperatureMetricsEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%lf°%c", self.currentWeather.temperature, [MWUtils temperatureFormatCharForMetric:tempMetric]];

    BOOL isNight = self.currentWeather.timestamp > self.currentWeather.sunset || self.currentWeather.timestamp < self.currentWeather.sunrise;
    NSString* iconName = [self.currentWeather.condition decodeSystemImageNameAtNight:isNight];
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
