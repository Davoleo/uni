//
// Created by Leo Dav on 16/06/22.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/// Simple class to show and hide loading alert popup when the app is busy doing asynchronous work
@interface LoadingAlert : NSObject

+ (void) showInController: (UIViewController*) controller;

+ (void)dismissFromController:(UIViewController*)controller;
@end