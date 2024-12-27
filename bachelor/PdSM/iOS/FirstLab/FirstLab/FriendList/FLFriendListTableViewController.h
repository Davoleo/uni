//
//  FLFriendListTableViewController.h
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import <UIKit/UIKit.h>
#import "FLFriendDataSource.h"

NS_ASSUME_NONNULL_BEGIN

@interface FLFriendListTableViewController : UITableViewController

@property (nonatomic, strong) id<FLFriendDataSource> dataSource;

@end

NS_ASSUME_NONNULL_END
