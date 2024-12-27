#import <CoreLocation/CoreLocation.h>

@interface ViewController()<CLLocationManagerDelegate>

@property (nonatomic, strong) CLLocationManager* manager;

@end

@implementation

//Deferences Object Creation (Lazy Loading)
// Creazione dell'oggetto solo quando mi serve [very good practice per property strong]
- (CLLocationManager*) locationManager {
	if (!_manager)
		_manager = [[CLLocationManager alloc] init];
	
	return _manager;
}

- (void) viewDidLoad {
	[super viewDidLoad];
	self.manager.desiredAccuracy = kCLocationAccuracyBest;
	self.manager.distanceFilter = 100;
	self.manager.delegate = self;
	[self.manager startUpdatingLocation];
}

- (void) locationManager:(CLLocationManager*)manager didUpdateLocations:(NSArray*)locations {
	CLLocation* current = [locations lastObject];
}

- (void) reverseGeocoding {
	CLGeocoder* geocoder [[CLGeocoder alloc] init];

	[geocoder reverseGeocodeLocation:location completionHandler:^(NSArray* placemarks, NSError* error) {
		//Uno dei modi per looppare su un array
		[placemarks enumerateObjectsUsingBlock:^(id obj, NSUInteger index, BOOL* stop) {
			if ([obj isKindOfClass:[CLPlacemark class]]) {
				CLPlacemark* pm = (CLPlacemark*)obj;
			}
		}];
	}];
}

@end