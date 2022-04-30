//
//  FLFriend.h
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import <Foundation/Foundation.h>

@interface FLFriend : NSObject

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)last
                             email:(NSString*)email
                            avatar:(NSString*)avatar
                         thumbnail:(NSString*)thumbnail;

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)lastname
                             email:(NSString*)email
                            avatar:(NSString*)avatar;

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)last
                             email:(NSString*)email;

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)last;

@property (nonatomic, strong) NSString* firstname;
@property (nonatomic, strong) NSString* lastname;
@property (nonatomic, strong) NSString* email;
@property (nonatomic, strong) NSString* avatar;
@property (nonatomic, strong) NSString* thumbnail;

@property (nonatomic, readonly) NSString* displayName;

@end
