//
// Created by Leo Dav on 16/06/22.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface LoadingAlert : NSObject

+ (void) showInController: (UIViewController*) controller;

+ (void)dismissFromController:(UIViewController*)controller;
@end