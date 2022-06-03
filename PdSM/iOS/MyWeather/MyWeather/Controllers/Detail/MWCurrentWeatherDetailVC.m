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

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *currentWeatherLoadingIndicator;

@end

@implementation MWCurrentWeatherDetailVC

- (void)viewDidLoad {
    [super viewDidLoad];

    //self.currentWeatherLoadingIndicator.hidden = NO;
    //[self.currentWeatherLoadingIndicator startAnimating];

    NSAssert(self.position != nil, @"Current Weather Details View Controller can't be initialized with NIL POSITION");

    if (self.currentWeather == nil) {
        [MWUtils queryCurrentWeatherInLocation:self.position AndThen:^(MWWeatherData* data) {
            self.currentWeather = data;
            //Update UI on the main queue
            dispatch_async(dispatch_get_main_queue(), ^{
                [self setupUI];
                [self.currentWeatherLoadingIndicator stopAnimating];
            });
        }];
    }
}

- (void) setupUI {
    //Attach map pin image to location name & create NSString
    /*
    NSTextAttachment* placemarkAttachment = [[NSTextAttachment alloc] init];
    placemarkAttachment.image = [UIImage systemImageNamed:@"mappin"];
    NSAttributedString* placemarkAttachString = [NSAttributedString attributedStringWithAttachment:placemarkAttachment];
    NSMutableAttributedString* placemarkString = [[NSMutableAttributedString alloc] initWithString:self.position.placemarkCache.name];
    [placemarkString appendAttributedString:placemarkAttachString];
    */
    self.placemarkLabel.text = self.position.placemarkCache.name;

    //Current Temperature formatting
    MWTemperatureMetricsEnum tempMetric = (MWTemperatureMetricsEnum) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%.1lf°%c", self.currentWeather.temperature, [MWUtils temperatureFormatCharForMetric:tempMetric]];

    BOOL isNight = self.currentWeather.timestamp > self.currentWeather.sunset || self.currentWeather.timestamp < self.currentWeather.sunrise;
    NSString* iconName = [self.currentWeather.condition decodeSystemImageNameAtNight:isNight];
    self.weatherIconView.image = [UIImage systemImageNamed:iconName];

    self.conditionsLabel.text = self.currentWeather.condition.name;
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
