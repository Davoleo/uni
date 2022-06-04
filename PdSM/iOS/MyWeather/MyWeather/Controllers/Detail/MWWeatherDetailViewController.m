//
//  MWWeatherDetailViewController.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWWeatherDetailViewController.h"
#import "MWUtils.h"

@interface MWWeatherDetailViewController ()

@property (weak, nonatomic) IBOutlet UIImageView* weatherIconView;

@property (weak, nonatomic) IBOutlet UILabel* placemarkLabel;
@property (weak, nonatomic) IBOutlet UILabel* temperatureLabel;
@property (weak, nonatomic) IBOutlet UILabel* conditionsLabel;

@property (weak, nonatomic) IBOutlet UIImageView* windIcon;
@property (weak, nonatomic) IBOutlet UILabel* windLabel;

@property (weak, nonatomic) IBOutlet UILabel* sunriseLabel;
@property (weak, nonatomic) IBOutlet UILabel* sunsetLabel;

@end

@implementation MWWeatherDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    UIActivityIndicatorView* loadingIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleLarge];
    loadingIndicator.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    loadingIndicator.center = self.view.center;
    loadingIndicator.backgroundColor = [UIColor systemBackgroundColor];
    loadingIndicator.hidesWhenStopped = YES;
    [self.view addSubview:loadingIndicator];
    [loadingIndicator bringSubviewToFront:self.view];
    [loadingIndicator startAnimating];

    if (self.forecast == nil) {
        [MWUtils queryForecastInLocation:self.position AndThen:^(MWForecast* data) {
            self.forecast = data;
            //Update UI on the main queue
            dispatch_async(dispatch_get_main_queue(), ^{
                [self setupUI];
                [loadingIndicator stopAnimating];
            });
        }];
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if (self.forecast != nil) {
        [self setupUI];
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

    MWWeatherData* currentWeather = self.forecast.current;

    self.placemarkLabel.text = self.position.placemarkCache.name;

    //Current Temperature formatting
    MWTemperatureMetrics tempMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%.1lf°%c", currentWeather.temperature, [MWUtils temperatureFormatCharForMetric:tempMetric]];

    BOOL isNight = currentWeather.timestamp > currentWeather.sunset || currentWeather.timestamp < currentWeather.sunrise;
    NSString* iconName = [currentWeather.condition decodeSystemImageNameAtNight:isNight];
    self.weatherIconView.image = [UIImage systemImageNamed:iconName];

    self.conditionsLabel.text = currentWeather.condition.name;

    //Wind direction icon
    self.windIcon.image = [UIImage systemImageNamed:currentWeather.windDirection.iconName];
    self.windLabel.text = [NSString stringWithFormat:@"Direction: %@ | Speed: %.2lfm/s", currentWeather.windDirection.direction, currentWeather.windSpeed];

    NSDate* currentSunrise = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunrise];
    self.sunriseLabel.text = [NSString stringWithFormat:@"Sunrise: %@", [NSDateFormatter localizedStringFromDate:currentSunrise dateStyle:NSDateFormatterNoStyle timeStyle: NSDateFormatterShortStyle]];
    NSDate* currentSunset = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunrise];
    self.sunsetLabel.text = [NSString stringWithFormat:@"Sunset: %@", [NSDateFormatter localizedStringFromDate:currentSunset dateStyle:NSDateFormatterNoStyle timeStyle: NSDateFormatterShortStyle]];

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
