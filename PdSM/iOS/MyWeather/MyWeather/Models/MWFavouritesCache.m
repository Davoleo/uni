//
// Created by Leo Dav on 17/05/22.
//

#import "MWFavouritesCache.h"
#import "MWUtils.h"
#import "MWManagers.h"

NSString* MW_FAVOURITES_POI_ARRAY_KEY = @"favourites_poi_array";

static MWFavouritesCache* cacheRef = nil;

static void (^onReady) (void) = nil;

@implementation MWFavouritesCache

- (void) populateForecastCacheForPOIs: (NSArray<NSString*>*) serializedPois {

    _favoritesCache = [NSMutableDictionary dictionaryWithCapacity:serializedPois.count];

    dispatch_queue_t dispatcherQueue = dispatch_queue_create("dispatcher_queue", NULL);

    dispatch_async(dispatcherQueue, ^{
        [self queryPositionFromArray:serializedPois AtIndex:0];
    });
}

- (void) queryPositionFromArray: (NSArray<NSString*>*) serializedPois  AtIndex: (NSUInteger) index {
    if (index >= serializedPois.count) {
        if (onReady != nil) {
            dispatch_async(dispatch_get_main_queue(), ^{
                onReady();
            });
        }
        return;
    }

    [MWPoi geocode:serializedPois[index] AndThen:^(MWPoi* poi) {
        [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* forecast) {
            self.favoritesCache[serializedPois[index]] = forecast;
            [self queryPositionFromArray:serializedPois AtIndex:index+1];
        }];
        NSLog(@"%@ | %@ %@", poi.placemarkCache.name, poi.placemarkCache.thoroughfare, poi.placemarkCache.locality);
    }];
}

- (instancetype)init {
    self = [super init];
    if (self) {

        id userDefObj = [NSUserDefaults.standardUserDefaults objectForKey:MW_FAVOURITES_POI_ARRAY_KEY];
        if (userDefObj != nil && [userDefObj isKindOfClass:[NSArray class]]) {
            NSArray* favPOIs = (NSArray*) userDefObj;
            NSLog(@"favPOIs: [%@]", [favPOIs componentsJoinedByString:@","]);
            [self populateForecastCacheForPOIs:favPOIs];
        }
        else {
            _favoritesCache = [NSMutableDictionary dictionary];
            if (onReady != nil)
                onReady();
        }
    }

    return self;
}

+ (MWFavouritesCache*)reference {
    if (cacheRef == nil) {
        cacheRef = [[MWFavouritesCache alloc] init];
    }
    return cacheRef;
}

+ (void) onReadyCall: (void (^) (void)) block {
    onReady = block;
}

+ (BOOL) isPresent {
    return cacheRef != nil;
}

- (void)saveFavourites {
    NSArray* favPOIs = self.favoritesCache.allKeys;
    [NSUserDefaults.standardUserDefaults setObject:favPOIs forKey:MW_FAVOURITES_POI_ARRAY_KEY];
}

- (void) add:(NSString*)location
        Then: (dispatch_block_t) doThis {
    [[MWManagers geocoder] geocodeAddressString:location completionHandler:^ (NSArray<CLPlacemark*>* placemarks, NSError* error){
        CLLocationCoordinate2D coords = placemarks.firstObject.location.coordinate;
        MWPoi* poi = [MWPoi poiWithLatitude: coords.latitude longitude:coords.longitude];
        poi.placemarkCache = placemarks.firstObject;

        [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* fforecast) {
            NSString* locationName =
                    poi.placemarkCache.thoroughfare != nil ?
                            [NSString stringWithFormat:@"%@ %@", poi.placemarkCache.thoroughfare, poi.placemarkCache.locality] :
                            poi.placemarkCache.name;

            assert(locationName != nil);

            [self.favoritesCache setValue:fforecast forKey:locationName];
            dispatch_async(dispatch_get_main_queue(), doThis);
        }];
    }];
}

- (NSArray<MWForecast*>*)getAll {
    return self.favoritesCache.allValues;
}

- (BOOL)has:(NSString*)location {
    return [self.favoritesCache objectForKey:location] != nil;
}

- (MWForecast*)getByName:(NSString*)name {
    return [self.favoritesCache valueForKey:name];
}

- (NSUInteger) length {
    return self.favoritesCache.count;
}

- (void)            add: (NSString*) location
     WithPrefetchedData: (MWForecast* __nullable) forecast
{
    if (forecast == nil) {
        [[MWManagers geocoder] geocodeAddressString:location completionHandler:^ (NSArray<CLPlacemark*>* placemarks, NSError* error){
            CLLocationCoordinate2D coords = placemarks.firstObject.location.coordinate;
            MWPoi* poi = [MWPoi poiWithLatitude: coords.latitude longitude:coords.longitude];
            poi.placemarkCache = placemarks.firstObject;

            [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* fforecast) {
                [self.favoritesCache setValue:fforecast forKey:location];
            }];
        }];
    }
    else
        [self.favoritesCache setValue:forecast forKey:location];
}

- (void) remove: (NSString*) location {
    [self.favoritesCache removeObjectForKey:location];
}

- (void)clear {
    [self.favoritesCache removeAllObjects];
    [self saveFavourites];
}


@end
