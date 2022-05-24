//
// Created by Leo Dav on 17/05/22.
//

#import <Foundation/Foundation.h>
#import "MWForecast.h"

FOUNDATION_EXPORT NSString* MW_FAVOURITES_POI_ARRAY_KEY;

@interface MWFavouritesCache : NSObject

@property (strong, nonatomic) NSMutableDictionary<NSString*, MWForecast*>* favoritesCache;

- (void) saveFavourites;

- (void) addFavoritePoi: (MWPoi*) poi;


- (NSArray<MWForecast*>*)getAllFavourites;

- (NSUInteger)length;
@end