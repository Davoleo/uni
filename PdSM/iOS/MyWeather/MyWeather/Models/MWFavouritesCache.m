//
// Created by Leo Dav on 17/05/22.
//

#import "MWFavouritesCache.h"
#import "MWUtils.h"
#import "MWManagers.h"

NSString* MW_FAVOURITES_POI_ARRAY_KEY = @"favourites_poi_array";

static MWFavouritesCache* cacheRef;

@implementation MWFavouritesCache

- (void) populateForecastCacheForPOIs: (NSArray<NSString*>*) serializedPois {

    _favoritesCache = [NSMutableDictionary dictionaryWithCapacity:serializedPois.count];

    for (NSUInteger i = 0; i < serializedPois.count; ++i) {
        MWPoi* poi = [MWPoi poiFromString:serializedPois[i]];
        [MWUtils queryOneCallAPIInPoi:poi AndThen:^(MWForecast* forecast) {
            self.favoritesCache[serializedPois[i]] = forecast;
        }];
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

    cacheRef = self;
    return self;
}

+ (MWFavouritesCache*)reference {
    return cacheRef;
}

- (void)saveFavourites {
    NSArray* favPOIs = self.favoritesCache.allKeys;
    [NSUserDefaults.standardUserDefaults setObject:favPOIs forKey:MW_FAVOURITES_POI_ARRAY_KEY];
}

- (void)addPoi:(MWPoi*)poi ThenExecuteSelector: (SEL) method OnObject: (id) object {
    [MWUtils queryOneCallAPIInPoi:poi AndThen:^(MWForecast* forecast) {
        [self.favoritesCache setValue:forecast forKey:[poi toString]];
        [object performSelectorOnMainThread:method withObject:nil waitUntilDone:false];
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

- (void) add: (NSString*) location WithPrefetchedData: (MWForecast* __nullable) forecast {
    if (forecast == nil) {
        [[MWManagers geocoder] geocodeAddressString:location completionHandler:^ (NSArray<CLPlacemark*>* placemarks, NSError* error){
            CLLocationCoordinate2D coords = placemarks.firstObject.location.coordinate;
            MWPoi* poi = [MWPoi poiWithLatitude: coords.latitude longitude:coords.longitude];
            [MWUtils queryOneCallAPIInPoi:poi AndThen:^(MWForecast* fforecast) {
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
