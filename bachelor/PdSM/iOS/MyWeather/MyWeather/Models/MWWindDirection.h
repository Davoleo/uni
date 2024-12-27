//
// Created by Leo Dav on 16/05/22.
//

#import <Foundation/Foundation.h>

@interface MWWindDirection : NSObject

@property (nonatomic, readonly) float degrees;
@property (nonatomic, readonly, strong) NSString* direction;
@property (nonatomic, readonly, strong) NSString* iconName;

+ (MWWindDirection*) fromDegrees:(float)degrees;

@end