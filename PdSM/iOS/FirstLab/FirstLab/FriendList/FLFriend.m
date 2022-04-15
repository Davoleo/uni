//
//  FLFriend.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriend.h"

@implementation FLFriend

- (instancetype)initWithFirstname:(NSString *)first lastname:(NSString *)last email:(NSString *)email {
    if (self = [super init]) {
        _firstname = [first copy];
        _lastname = [last copy];
        _email = [email copy];
    }
    
    return self;
}

- (instancetype)initWithFirstname:(NSString *)first lastname:(NSString *)last {
    return [self initWithFirstname:first lastname:last email:@""];
}

-(NSString*)displayName {
    return [NSString stringWithFormat:@"%@ %@", self.firstname, self.lastname];
}

@end
