//
//  FLCounter.m
//  FirstLab
//
//  Created by Leo Dav on 26/03/2022.
//

#import "FLCounter.h"

@implementation FLCounter

-(instancetype)initWithValue:(NSNumber *)value {
    if (self = [super init]) {
        _counter = value;
    }
    return self;
}

- (instancetype)init {
    return [self initWithValue:@(0)];
}

- (void)increment {
    self.counter = @(self.counter.intValue + 1);
    [[NSNotificationCenter defaultCenter] postNotificationName:@"CounterChanged" object:self];
}

- (int)asInt {
    return self.counter.intValue;
}

@end
