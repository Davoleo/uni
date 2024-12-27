//
//  FLFriendList.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendList.h"

@interface FLFriendList()

@property (nonatomic, strong) NSMutableArray* list;

@end

@implementation FLFriendList

-(instancetype)init{
    if(self = [super init]) {
        _list = [[NSMutableArray alloc] init];
    }
    return self;
}

//L'array diventerà immutabile per l'esterno
- (NSArray *)getAll {
    return self.list;
}

- (void)add:(FLFriend *)frien {
    [self.list addObject:frien];
}

- (FLFriend *)getAtIndex:(NSInteger)index {
    return [self.list objectAtIndex:index];
}

- (long)size {
    return self.list.count;
}


@end
