//
// Created by Leo Dav on 06/05/22.
//

#import <Foundation/Foundation.h>
#import "FLFriendList.h"

NS_ASSUME_NONNULL_BEGIN

@protocol FLFriendDataSource <NSObject>

- (FLFriendList*) getFriends;

@end

NS_ASSUME_NONNULL_END