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

        MWTemperatureMetrics currentTempMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
        if (currentTempMetric != self.metricPreference) {
            self.metricPreference = currentTempMetric;
            [self setupUI];
        }
        else
            [self updateCurrentWeatherUI];
        //Debug Print
        //NSLog(@"APPARE RANMAN");
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    //Unregisters from position update notifications
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NEW_POSITION_NOTIFICATION_ID object:nil];
}

/// Method called whenever a notification about a new user location is broadcasted and intercepted by this VC
/// @param notification the intercepted notification
- (void) newPositionInterceptedVia: (NSNotification*) notification {
    //if the new intercepted position has the same placemark feature name of the old one we don't update anything
    if ([self.position.placemarkCache.name isEqualToString:self.position.placemarkCache.name])
        return;

    //Otherwise we assign the new position, query the new weather data for the new position and repaint the whole UI
    self.position = notification.userInfo[@"new_position"];
    [self refreshWeatherDataAndPaint];
}

/// This method queries the forecast in the currently assigned location and repaints the whole UI to display updated information
- (void)refreshWeatherDataAndPaint {
    //Show loading indicator popup during async call
    [LoadingAlert showInController:self];
    //Launch async call
    [MWUtils queryForecastInLocation:self.position AndThen:^(MWForecast* data) {
        self.forecast = data;
        //Update UI on the main queue
        dispatch_async(dispatch_get_main_queue(), ^{
            //Update ui and hide loading indicator popup
            [self setupUI];
            [LoadingAlert dismissFromController:self];
        });
    }];
}

/// Updates everything in the detail page UI with current location information
/// [Should be called on the main UI thread]
- (void) setupUI {

    //Update current weather section of the details page
    [self updateCurrentWeatherUI];

    //Clean up previous data in the stackView that contains hourly data (if any is present)
    [self.hourlyStack.subviews enumerateObjectsUsingBlock:^ (id object, NSUInteger index, BOOL* stop) {
        if ([object isKindOfClass:[UIView class]])
            [self.hourlyStack removeArrangedSubview:object];
    }];

    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"HH:mm"]; //Using this date format for hourly weather cards
    [self.forecast.hourly enumerateObjectsUsingBlock:^ (MWWeatherData* weather, NSUInteger index, BOOL* stop) {
        [self.hourlyStack addArrangedSubview:[self cardWith:weather AndDateFormatter:formatter]];
        //NSLog(@"Adding view...");
    }];

    //Adjust StackView size to the newly added elements
    [self.hourlyStack layoutIfNeeded];
    //Adjust ScrollView size (adding and enabling a new constraint to the top view width)
    [self.hourlyStack.superview.widthAnchor constraintEqualToConstant:self.view.frame.size.width - 20].active = YES;

    //Debug Prints
    //NSLog(@"scroll width: %f", self.hourlyStack.superview.frame.size.width);
    //NSLog(@"width: %f, x: %f", self.hourlyStack.frame.size.width, self.hourlyStack.frame.origin.x);
    //NSLog(@"view count %ld", self.hourlyStack.subviews.count);

    //Clean up previous data in the stackView that contains daily data (if any is present)
    [self.dailyStack.subviews enumerateObjectsUsingBlock:^ (id object, NSUInteger index, BOOL* stop) {
        if ([object isKindOfClass:[UIView class]])
            [self.dailyStack removeArrangedSubview:object];
    }];

    //Using this date format for daily weather cards
    [formatter setDateFormat:@"E HH:mm"];
    [self.forecast.daily enumerateObjectsUsingBlock:^ (MWWeatherData* weather, NSUInteger index, BOOL* stop) {
        [self.dailyStack addArrangedSubview:[self cardWith:weather AndDateFormatter:formatter]];
    }];

    //Adjust StackView size
    [self.dailyStack layoutIfNeeded];
    //Adjust ScrollView size
    [self.dailyStack.superview.widthAnchor constraintEqualToConstant:self.view.frame.size.width - 20].active = YES;

    //TODO ^ The above code can probably be deduplicated
}

/// Builds a weather card with weatherData information for a specific timestamp
/// @param weatherData The weather data to create the card for [also contains timestamp information]
/// @param formatter The formatter to format the DateTime timestamp
/// @return The newly created card
- (MWWeatherCardView*) cardWith: (MWWeatherData*) weatherData AndDateFormatter: (NSDateFormatter*) formatter {
    MWWeatherCardView* card = [[MWWeatherCardView alloc] init];

    //Get Timestamp
    NSDate* date = [NSDate dateWithTimeIntervalSince1970:weatherData.timestamp + self.forecast.location.timezoneOffset];
    //Format and set timestamp to the card top label
    card.dateLabel.text = [formatter stringFromDate:date];

    //Weather Icon
    card.weatherIcon.image = [UIImage systemImageNamed:[weatherData.condition decodeSystemImageName]];

    //Weather Condition Name
    card.conditionsLabel.text = weatherData.condition.name;

    //Min and Max Temperatures Label
    NSString* minTemperature = [MWUtils temperature:weatherData.minTemperature FormattedInMetric:self.metricPreference];
    NSString* convertedMaxTemperature = [MWUtils temperature:weatherData.maxTemperature FormattedInMetric:self.metricPreference];
    //Build string via template
    NSString* temperatureString = [NSString stringWithFormat:@"Min: %@\nMax: %@", minTemperature, convertedMaxTemperature];
    //Get Temperature components from the string
    NSArray<NSString*>* temperatureComponents = [temperatureString componentsSeparatedByString:@"\n"];
    //Initialize a new Attributed string coloring the first component blue and the second component red [Min and max temperature]
    NSMutableAttributedString* temperatureAttrString = [[NSMutableAttributedString alloc] initWithString:temperatureString];
    [temperatureAttrString addAttribute:NSForegroundColorAttributeName value:[UIColor systemBlueColor] range:[temperatureString rangeOfString:temperatureComponents.firstObject]];
    [temperatureAttrString addAttribute:NSForegroundColorAttributeName value:[UIColor systemRedColor] range:[temperatureString rangeOfString:temperatureComponents.lastObject]];
    card.temperatureLabel.attributedText = temperatureAttrString;

    //Disable automatic constraints
    card.translatesAutoresizingMaskIntoConstraints = NO;
    //Set Fixed width and height constraints
    [card.heightAnchor constraintEqualToConstant:150].active = YES;
    [card.widthAnchor constraintEqualToConstant:120].active = YES;

    return card;
}

/// Updates the current weather UI section of the details page with current weather info in current location
- (void) updateCurrentWeatherUI {
    MWWeatherData* currentWeather = self.forecast.current;

    self.placemarkLabel.text = self.position.placemarkCache.name;

    //Current Temperature formatting
    MWTemperatureMetrics tempMetric = (MWTemperatureMetrics) [[NSUserDefaults standardUserDefaults] integerForKey:MW_TEMPERATURE_METRIC_PREF];
    self.temperatureLabel.text = [NSString stringWithFormat:@"%@", [MWUtils temperature:currentWeather.temperature FormattedInMetric:tempMetric]];

    NSString* iconName = [currentWeather.condition decodeSystemImageName];
    self.weatherIconView.image = [UIImage systemImageNamed:iconName];

    //Weather Condition Description
    self.conditionsLabel.text = [currentWeather.condition.smallDesc capitalizedString];

    //Wind Direction & Speed
    self.windSpeedLabel.text = [NSString stringWithFormat:@"Speed: %.2lfkm/h", currentWeather.windSpeed];
    self.windDirectionIcon.image = [UIImage systemImageNamed:currentWeather.windDirection.iconName];
    self.windDirectionLabel.text = [NSString stringWithFormat:@"Direction: %@", currentWeather.windDirection.direction];

    //Sunrise and Sunset labels
    NSDate* currentSunrise = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunrise + self.forecast.location.timezoneOffset];
    self.sunriseLabel.text = [NSString stringWithFormat:@"Sunrise: %@", [NSDateFormatter localizedStringFromDate:currentSunrise dateStyle:NSDateFormatterNoStyle timeStyle: NSDateFormatterShortStyle]];
    NSDate* currentSunset = [NSDate dateWithTimeIntervalSince1970:currentWeather.sunset + self.forecast.location.timezoneOffset];
    self.sunsetLabel.text = [NSString stringWithFormat:@"Sunset: %@", [NSDateFormatter localizedStringFromDate:currentSunset dateStyle:NSDateFormatterNoStyle timeStyle: NSDateFormatterShortStyle]];
}

@end
