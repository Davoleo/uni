//
//  FLCounter.h
//  FirstLab
//
//  Created by Leo Dav on 26/03/2022.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FLCounter : NSObject

- (instancetype) init;
- (instancetype) initWithValue:(NSNumber*)value;

@property (strong, nonatomic) NSNumber* counter;
@property (readonly) int asInt;

-(void)increment;

@end

NS_ASSUME_NONNULL_END
