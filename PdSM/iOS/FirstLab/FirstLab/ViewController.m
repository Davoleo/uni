//
//  ViewController.m
//  FirstLab
//
//  Created by Leo Dav on 26/03/2022.
//

#import "ViewController.h"
#import "FLCounter.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *counterLabel;
@property (strong, nonatomic) FLCounter* counter;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.counterLabel.text = @"Count: --";
    self.counter = [[FLCounter alloc] init]; //equivalente a [NSNumber numberWithInt:0]
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateUI) name:@"CounterChanged" object:self.counter];
}

- (IBAction)buttonPressed {
    NSLog(@"Button has been pressed");
    
    [self.counter increment];
}

-(void)updateUI {
    self.counterLabel.text = [NSString stringWithFormat:@"Count: %d", self.counter.asInt];
}


@end
