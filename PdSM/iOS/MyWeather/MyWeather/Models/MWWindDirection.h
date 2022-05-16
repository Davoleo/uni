//
// Created by Leo Dav on 16/05/22.
//

#import <Foundation/Foundation.h>

@interface MWWindDirection : NSObject

@property (nonatomic, readonly) float degrees;
@property (nonatomic, strong) NSString* direction;

+ (MWWindDirection*) fromDegrees:(float)degrees;

@end