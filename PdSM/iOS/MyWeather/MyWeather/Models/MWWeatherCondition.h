//
// Created by Leo Dav on 16/05/22.
//

#import <Foundation/Foundation.h>


@interface MWWeatherCondition : NSObject

@property (nonatomic, readonly) int id;
@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSString* smallDesc;
@property (nonatomic, readonly) BOOL night;

- (NSString*)decodeSystemImageName;

- (instancetype)initWithJSONObject:(NSDictionary*) json;

@end