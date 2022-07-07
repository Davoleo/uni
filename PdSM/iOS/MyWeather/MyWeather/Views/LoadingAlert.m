//
// Created by Leo Dav on 16/06/22.
//

#import "LoadingAlert.h"

static UIAlertController* loadingAlert;

static UIVisualEffectView* blur;

@implementation LoadingAlert

/// Initializes necessary components, Visual effect, AlertController, and Indicator view
+ (void)initialize {
    //loadingAlert.view.tintColor = [UIColor blackColor];
    loadingAlert = [UIAlertController alertControllerWithTitle:nil message:@"Loading..." preferredStyle:UIAlertControllerStyleAlert];

    blur = [[UIVisualEffectView alloc] initWithEffect: [UIBlurEffect effectWithStyle:UIBlurEffectStyleDark]];

    UIActivityIndicatorView* loading = [[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(10, 5, 50, 50)];
    loading.hidesWhenStopped = YES;
    loading.activityIndicatorViewStyle = UIActivityIndicatorViewStyleMedium;
    [loading startAnimating];
    [loadingAlert.view addSubview:loading];
}

/// Displays the Loading alert on the specified controller
/// @param controller the controller to display the loading alert onto
+ (void)showInController:(UIViewController*)controller{
    blur.frame = controller.view.bounds;
    [controller.view addSubview:blur];
    [controller presentViewController:loadingAlert animated:YES completion:nil];
}

/// Hides the Loading alert from the controller
+ (void) dismissFromController: (UIViewController*) controller {
    if ([controller.presentedViewController isKindOfClass:[UIAlertController class]]) {
        [controller dismissViewControllerAnimated:NO completion:nil];
    }

    //Make sure to remove visual blur effect in the background
    [blur removeFromSuperview];
}

@end
