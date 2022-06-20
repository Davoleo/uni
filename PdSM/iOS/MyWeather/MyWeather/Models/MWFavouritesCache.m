//
// Created by Leo Dav on 17/05/22.
//

#import "MWFavouritesCache.h"
#import "MWUtils.h"
#import "MWManagers.h"

NSString* MW_FAVOURITES_POI_ARRAY_KEY = @"favourites_poi_array";

static MWFavouritesCache* cacheRef = nil;

@implementation MWFavouritesCache

- (void) populateForecastCacheForPOIs: (NSArray<NSString*>*) serializedPois {

    _favoritesCache = [NSMutableDictionary dictionaryWithCapacity:serializedPois.count];

    //TODO fix async semantics
    for (NSUInteger i = 0; i < serializedPois.count; ++i) {
        [MWPoi geocode:serializedPois[i] AndThen:^(MWPoi* poi) {
            [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* forecast) {
                self.favoritesCache[serializedPois[i]] = forecast;
            }];
        }];
//        [MWUtils queryOneCallAPIInPoi:poi AndThen:^(MWForecast* forecast) {
//            self.favoritesCache[serializedPois[i]] = forecast;
//        }];
    }
}

- (instancetype)init {
    self = [super init];
    if (self) {

        id userDefObj = [NSUserDefaults.standardUserDefaults objectForKey:MW_FAVOURITES_POI_ARRAY_KEY];
        if (userDefObj != nil && [userDefObj isKindOfClass:[NSArray class]]) {
            NSArray* favPOIs = (NSArray*) userDefObj;
            [self populateForecastCacheForPOIs:favPOIs];
        }
        else
            _favoritesCache = [NSMutableDictionary dictionary];
    }

    return self;
}

+ (MWFavouritesCache*)reference {
    if (cacheRef == nil) {
        cacheRef = [[MWFavouritesCache alloc] init];
    }
    return cacheRef;
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
            [self.favoritesCache setValue:fforecast forKey:location];
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

@end
