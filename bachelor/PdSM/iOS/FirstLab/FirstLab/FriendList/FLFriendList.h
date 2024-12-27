//
//  FLFriendList.h
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import <Foundation/Foundation.h>
#import "FLFriend.h"

NS_ASSUME_NONNULL_BEGIN

@interface FLFriendList : NSObject

-(NSArray*)getAll;
-(void)add:(FLFriend*)frien;
-(FLFriend*)getAtIndex:(NSInteger)index;
-(long)size;

@end

NS_ASSUME_NONNULL_END
