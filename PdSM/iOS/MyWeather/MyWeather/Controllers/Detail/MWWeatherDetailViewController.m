//
//  MWWeatherDetailViewController.m
//  MyWeather
//
//  Created by Leo Dav on 24/05/22.
//

#import "MWWeatherDetailViewController.h"
#import "MWUtils.h"
#import "MWWeatherCardView.h"
#import "MWMyPositionViewController.h"
#import "LoadingAlert.h"

@interface MWWeatherDetailViewController ()

@property (weak, nonatomic) IBOutlet UIImageView* weatherIconView;

@property (weak, nonatomic) IBOutlet UILabel* placemarkLabel;
@property (weak, nonatomic) IBOutlet UILabel* temperatureLabel;
@property (weak, nonatomic) IBOutlet UILabel* conditionsLabel;

@property (weak, nonatomic) IBOutlet UILabel *windSpeedLabel;
@property (weak, nonatomic) IBOutlet UIImageView* windDirectionIcon;
@property (weak, nonatomic) IBOutlet UILabel* windDirectionLabel;

@property (weak, nonatomic) IBOutlet UILabel* sunriseLabel;
@property (weak, nonatomic) IBOutlet UILabel* sunsetLabel;

@property (weak, nonatomic) IBOutlet UIStackView *hourlyStack;
@property (weak, nonatomic) IBOutlet UIStackView *dailyStack;

@property (nonatomic) MWTemperatureMetrics metricPreference;

@end

@implementation MWWeatherDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    if (self.forecast == nil)
        [self refreshWeatherDataAndPaint];
    else
        [self setupUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    //Register for position update notifications
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newPositionInterceptedVia:) name: NEW_POSITION_NOTIFICATION_ID object: nil];
    if (self.forecast != nil) {
        [self updateCurrentWeatherUI];
        self.metricPreference = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
        NSLog(@"APPARE RANMNAN");
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    //Unregisters from opsition update notifications
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NEW_POSITION_NOTIFICATION_ID object:nil];
}

- (void) newPositionInterceptedVia: (NSNotification*) notification {
    if ([self.position.placemarkCache.name isEqualToString:self.position.placemarkCache.name])
        return;
    self.position = notification.userInfo[@"new_position"];
    [self refreshWeatherDataAndPaint];
}

- (void)refreshWeatherDataAndPaint {
    [LoadingAlert showInController:self];
    [MWUtils queryForecastInLocation:self.position AndThen:^(MWForecast* data) {
        self.forecast = data;
        //Update UI on the main queue
        dispatch_async(dispatch_get_main_queue(), ^{
            [self setupUI];
            [LoadingAlert dismissFromController:self];
        });
    }];
}

- (void) setupUI {

    [self updateCurrentWeatherUI];

    //Clean up previous data (if any)
    [self.hourlyStack.subviews enumerateObjectsUsingBlock:^ (id object, NSUInteger index, BOOL* stop) {
        if ([object isKindOfClass:[UIView class]])
            [self.hourlyStack removeArrangedSubview:object];
    }];

    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"HH:mm"];
    [self.forecast.hourly enumerateObjectsUsingBlock:^ (MWWeatherData* weather, NSUInteger index, BOOL* stop) {
        [self.hourlyStack addArrangedSubview:[self cardWith:weather AndDateFormatter:formatter]];
        //NSLog(@"Adding view...");
    }];

    //Adjust StackView size
    [self.hourlyStack layoutIfNeeded];
    //Adjust ScrollView size
    [self.hourlyStack.superview.widthAnchor constraintEqualToConstant:self.view.frame.size.width - 20].active = YES;

    //Debug Prints
    //NSLog(@"scroll width: %f", self.hourlyStack.superview.frame.size.width);
    //NSLog(@"width: %f, x: %f", self.hourlyStack.frame.size.width, self.hourlyStack.frame.origin.x);
    //NSLog(@"view count %ld", self.hourlyStack.subviews.count);

    //Clean up previous data (if any)
    [self.dailyStack.subviews enumerateObjectsUsingBlock:^ (id object, NSUInteger index, BOOL* stop) {
        if ([object isKindOfClass:[UIView class]])
            [self.dailyStack removeArrangedSubview:object];
    }];

    [formatter setDateFormat:@"E HH:mm"];
    [self.forecast.daily enumerateObjectsUsingBlock:^ (MWWeatherData* weather, NSUInteger index, BOOL* stop) {
        [self.dailyStack addArrangedSubview:[self cardWith:weather AndDateFormatter:formatter]];
    }];

    //Adjust StackView size
    [self.dailyStack layoutIfNeeded];
    //Adjust ScrollView size
    [self.dailyStack.superview.widthAnchor constraintEqualToConstant:self.view.frame.size.width - 20].active = YES;
}


- (MWWeatherCardView*) cardWith: (MWWeatherData*) weatherData AndDateFormatter: (NSDateFormatter*) formatter {
    MWWeatherCardView* card = [[MWWeatherCardView alloc] init];

    //Hour/Day
    NSDate* date = [NSDate dateWithTimeIntervalSince1970:weatherData.timestamp + self.forecast.location.timezoneOffset];
    card.dateLabel.text = [formatter stringFromDate:date];

    //Weather Icon
    card.weatherIcon.image = [UIImage systemImageNamed:[weatherData.condition decodeSystemImageName]];

    //Weather Condition
    card.conditionsLabel.text = weatherData.condition.name;

    //Min and Max Temperatures Label
    NSString* minTemperature = [MWUtils temperature:weatherData.minTemperature FormattedInMetric:self.metricPreference];
    NSString* convertedMaxTemperature = [MWUtils temperature:weatherData.maxTemperature FormattedInMetric:self.metricPreference];
    NSString* temperatureString = [NSString stringWithFormat:@"Min: %@\nMax: %@", minTemperature, convertedMaxTemperature];
    NSArray<NSString*>* temperatureComponents = [temperatureString componentsSeparatedByString:@"\n"];
    NSMutableAttributedString* temperatureAttrString = [[NSMutableAttributedString alloc] initWithString:temperatureString];
    [temperatureAttrString addAttribute:NSForegroundColorAttributeName value:[UIColor systemBlueColor] range:[temperatureString rangeOfString:temperatureComponents.firstObject]];
    [temperatureAttrString addAttribute:NSForegroundColorAttributeName value:[UIColor systemRedColor] range:[temperatureString rangeOfString:temperatureComponents.lastObject]];
    card.temperatureLabel.attributedText = temperatureAttrString;

    card.translatesAutoresizingMaskIntoConstraints = NO;
    [card.heightAnchor constraintEqualToConstant:150].active = YES;
    [card.widthAnchor constraintEqualToConstant:120].active = YES;

    return card;
}

- (void) updateCurrentWeatherUI {
    MWWeatherData* currentWeather = self.forecast.current;

    self.placemarkLabel.text = self.position.placemarkCache.name;

    //Current Temperature formatting
    MWTemperatureMetrics tempMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%@", [MWUtils temperature:currentWeather.temperature FormattedInMetric:tempMetric]];

    NSString* iconName = [currentWeather.condition decodeSystemImageName];
    self.weatherIconView.image = [UIImage systemImageNamed:iconName];

    self.conditionsLabel.text = [currentWeather.condition.smallDesc capitalizedString];

    //Wind direction icon
    self.windSpeedLabel.text = [NSString stringWithFormat:@"Speed: %.2lfm/s", currentWeather.windSpeed];
    self.windDirectionIcon.image = [UIImage systemImageNamed:currentWeather.windDirection.iconName];
    self.windDirectionLabel.text = [NSString stringWithFormat:@"Direction: %@", currentWeather.windDirection.direction];

    NSDate* currentSunrise = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunrise + self.forecast.location.timezoneOffset];
    self.sunriseLabel.text = [NSString stringWithFormat:@"Sunrise: %@", [NSDateFormatter localizedStringFromDate:currentSunrise dateStyle:NSDateFormatterNoStyle timeStyle: NSDateFormatterShortStyle]];
    NSDate* currentSunset = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunset + self.forecast.location.timezoneOffset];
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
