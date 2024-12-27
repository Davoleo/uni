//
//  FLGeoFriend.h
//  FirstLab
//
//  Created by Leo Dav on 30/04/2022.
//

#import "FLFriend.h"
#import "FLPoi.h"

NS_ASSUME_NONNULL_BEGIN

@interface FLGeoFriend : FLFriend

@property (nonatomic, strong) FLPoi* location;

@end

NS_ASSUME_NONNULL_END
