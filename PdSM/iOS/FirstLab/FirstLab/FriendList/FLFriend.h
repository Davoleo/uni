//
//  FLFriend.h
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FLFriend : NSObject

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)last
                             email:(NSString*)email;

- (instancetype) initWithFirstname:(NSString*)first
                          lastname:(NSString*)last;

@property (nonatomic, strong) NSString* firstname;
@property (nonatomic, strong) NSString* lastname;
@property (nonatomic, strong) NSString* email;

@property (nonatomic, readonly) NSString* displayName;

@end

NS_ASSUME_NONNULL_END
