//
//  MWFavouritePoisViewController.h
//  MyWeather
//
//  Created by Leo Dav on 20/05/22.
//

#import <UIKit/UIKit.h>
#import "MWFavouritesCache.h"

NS_ASSUME_NONNULL_BEGIN

@interface MWFavouritePoisViewController : UITableViewController

@property (nonatomic, strong) MWFavouritesCache* favourites;

@end

NS_ASSUME_NONNULL_END
