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

/// Called when the app is first started, populates the cache with all the geocoded positions and their weather data
/// @param serializedPois The placemark names that will be geocoded and queried for info
- (void) populateForecastCacheForPOIs: (NSArray<NSString*>*) serializedPois {

    //Allocate a dictionary with the same capacity as the serialized array
    _favoritesCache = [NSMutableDictionary dictionaryWithCapacity:serializedPois.count];

    //Create a new queue: to work on a different thread than the main one
    dispatch_queue_t dispatcherQueue = dispatch_queue_create("dispatcher_queue", NULL);

    dispatch_async(dispatcherQueue, ^{
        [self queryPositionFromArray:serializedPois AtIndex:0];
    });
}

/// Recursive method to query all the necessary info for all the favorite positions in the list
/// @param serializedPois the list of positions to geocode and query
/// @param index the position we're currently working on
- (void) queryPositionFromArray: (NSArray<NSString*>*) serializedPois  AtIndex: (NSUInteger) index {

    //if the current working index is >= than the list size we've finished working, hence we call the ready callback [if it's not null]
    if (index >= serializedPois.count) {
        if (onReady != nil) {
            dispatch_async(dispatch_get_main_queue(), ^{
                onReady();
            });
        }
        return;
    }

    //Geocode position from name
    [MWPoi geocode:serializedPois[index] AndThen:^(MWPoi* poi) {
        //Query forecast in the geocoded position
        [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* forecast) {
            //Assign the new queried forecast to the cache
            self.favoritesCache[serializedPois[index]] = forecast;
            //Recursively call this function on the next serialized poi
            [self queryPositionFromArray:serializedPois AtIndex:index+1];
        }];
        //Debug Print
        //NSLog(@"%@ | %@ %@", poi.placemarkCache.name, poi.placemarkCache.thoroughfare, poi.placemarkCache.locality);
    }];
}

- (instancetype)init {
    self = [super init];
    if (self) {

        id userDefObj = [NSUserDefaults.standardUserDefaults objectForKey:MW_FAVOURITES_POI_ARRAY_KEY];

        //If any serialized poi is present in the UserDefaults call the method to populate the cache
        if (userDefObj != nil && [userDefObj isKindOfClass:[NSArray class]]) {
            NSArray* favPOIs = (NSArray*) userDefObj;
            //Debug Print
            //NSLog(@"favPOIs: [%@]", [favPOIs componentsJoinedByString:@","]);
            [self populateForecastCacheForPOIs:favPOIs];
        }
        else {
            //Otherwise initialize the cache with an empty dictionary
            _favoritesCache = [NSMutableDictionary dictionary];
            if (onReady != nil)
                onReady();
            //^ ready callback
        }
    }

    return self;
}

/// Singleton pattern Cache reference method, will allocate a new favorites cache if it's not already present
/// @return A reference to a cache of self type
+ (MWFavouritesCache*)reference {
    if (cacheRef == nil) {
        cacheRef = [[MWFavouritesCache alloc] init];
    }
    return cacheRef;
}

/// Method to set a callback to be called when the cache is ready [initialized]
/// @param block The block to be executed
+ (void) onReadyCall: (void (^) (void)) block {
    onReady = block;
}

/// @return whether the cache is present or not
+ (BOOL) isPresent {
    return cacheRef != nil;
}

/// Persists changes made to the favorites cache at runtime inside the UserDefaults
- (void)saveFavourites {
    NSArray* favPOIs = self.favoritesCache.allKeys;
    [NSUserDefaults.standardUserDefaults setObject:favPOIs forKey:MW_FAVOURITES_POI_ARRAY_KEY];
}

/// Adds a new location to the Cache asynchronously
/// @param location The location to be added
/// @param doThis is Executed when the addition is successfully completed [On the main thread]
- (void) add:(NSString*)location
        Then: (dispatch_block_t) doThis {

    //Geocode location string
    [[MWManagers geocoder] geocodeAddressString:location completionHandler:^ (NSArray<CLPlacemark*>* placemarks, NSError* error){
        CLLocationCoordinate2D coords = placemarks.firstObject.location.coordinate;
        MWPoi* poi = [MWPoi poiWithLatitude: coords.latitude longitude:coords.longitude];
        poi.placemarkCache = placemarks.firstObject;

        //Query forecast in geocoded location
        [MWUtils queryForecastInLocation:poi AndThen:^(MWForecast* fforecast) {
            NSString* locationName =
                    poi.placemarkCache.thoroughfare != nil ?
                            [NSString stringWithFormat:@"%@ %@", poi.placemarkCache.thoroughfare, poi.placemarkCache.locality] :
                            poi.placemarkCache.name;

            assert(locationName != nil);

            //Add the new entry to the cache
            [self.favoritesCache setValue:fforecast forKey:locationName];
            //Callback on the main queue
            dispatch_async(dispatch_get_main_queue(), doThis);
        }];
    }];
}

/// @return All the forecast elements in the cache
- (NSArray<MWForecast*>*)getAll {
    return self.favoritesCache.allValues;
}

/// @param location to be checked
/// @return YES if location is in the cache NO otherwise
- (BOOL)has:(NSString*)location {
    return [self.favoritesCache objectForKey:location] != nil;
}

/// @param name placemark name of the location to get
/// @return the forecast in that placemark
- (MWForecast*)getByName:(NSString*)name {
    return [self.favoritesCache valueForKey:name];
}

/// @return count of the entries in the cache
- (NSUInteger) length {
    return self.favoritesCache.count;
}

/// Extra method to add a new location to the cache with optional prefetched data, no callback here though
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

/// Removes a location from the cache (given its placemark name)
/// @param location placemark name of the location to be removed
- (void) remove: (NSString*) location {
    [self.favoritesCache removeObjectForKey:location];
}

/// Removes all entries from the cache effectively clearing it
/// Also persist change to User Defaults
- (void)clear {
    [self.favoritesCache removeAllObjects];
    [self saveFavourites];
}


@end
