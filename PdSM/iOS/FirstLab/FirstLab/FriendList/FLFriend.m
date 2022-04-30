//
//  FLFriend.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriend.h"

@implementation FLFriend

- (instancetype)initWithFirstname:(NSString*)first lastname:(NSString*)last email:(NSString*)email avatar:(NSString*)avatar thumbnail:(NSString*)thumbnail {
    if (self = [super init]) {
        _firstname = [first copy];
        _lastname = [last copy];
        _email = [email copy];
        _avatar = [avatar copy];
        _thumbnail = [thumbnail copy];
    }

    return self;
}

- (instancetype)initWithFirstname:(NSString*)first lastname:(NSString*)lastname email:(NSString*)email avatar:(NSString*)avatar {
    return [self initWithFirstname:first lastname:lastname email:email avatar:avatar thumbnail:nil];
}

- (instancetype)initWithFirstname:(NSString *)first lastname:(NSString *)last email:(NSString *)email {
    return [self initWithFirstname:first lastname:last email:email avatar:nil];
}

- (instancetype)initWithFirstname:(NSString *)first lastname:(NSString *)last {
    return [self initWithFirstname:first lastname:last email:@""];
}

-(NSString*)displayName {
    return [NSString stringWithFormat:@"%@ %@", self.firstname, self.lastname];
}

@end
