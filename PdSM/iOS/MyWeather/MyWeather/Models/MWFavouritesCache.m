//
// Created by Leo Dav on 17/05/22.
//

#import "MWFavouritesCache.h"
#import "MWUtils.h"

NSString* MW_FAVOURITES_POI_ARRAY_KEY = @"favourites_poi_array";

@implementation MWFavouritesCache

- (void) populateForecastCacheForPOIs: (NSArray*) pois {

    _favoritesCache = [NSMutableDictionary dictionaryWithCapacity:pois.count];

    for (NSUInteger i = 0; i < pois.count; ++i) {
        [MWUtils queryWeatherAPIInPoi:pois[i] AndThen:^(MWForecast* forecast) {
            _favoritesCache[pois[i]] = forecast;
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

    return self;
}

- (void)saveFavourites {
    NSArray* favPOIs = self.favoritesCache.allKeys;
    [NSUserDefaults.standardUserDefaults setObject:favPOIs forKey:MW_FAVOURITES_POI_ARRAY_KEY];
}

- (void)addFavoritePoi:(MWPoi*)poi {
    [MWUtils queryWeatherAPIInPoi:poi AndThen:^(MWForecast* forecast) {
        self.favoritesCache[poi] = forecast;
    }];
}

- (NSArray<MWForecast*>*) getAllFavourites {
    return self.favoritesCache.allValues;
}


@end