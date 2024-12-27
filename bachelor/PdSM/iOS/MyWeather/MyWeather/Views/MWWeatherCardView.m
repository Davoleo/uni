//
//  MWWeatherCardView.m
//  MyWeather
//
//  Created by Leo Dav on 05/06/22.
//

#import "MWWeatherCardView.h"

@interface MWWeatherCardView()

@property (strong, nonatomic) IBOutlet MWWeatherCardView *view;

@end

@implementation MWWeatherCardView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self myInit];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder*)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [self myInit];
    }
    return self;
}

- (void) myInit {
    //Load XIB file from the source code bundle
    [[NSBundle mainBundle] loadNibNamed:@"MWWeatherCardView" owner:self options:nil];

    //add our view as subview
    [self addSubview:self.view];
    //Constrain the XIB
    self.view.frame = self.bounds;

}


@end
