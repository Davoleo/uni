//
//  FLFriendListTableViewController.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendListTableViewController.h"
#import "FLExampleFriendDataSource.h"
#import "FLFriendTableDetailVC.h"
#import "FLGeoFriend.h"
#import "FLFriendMapVC.h"

@interface FLFriendListTableViewController ()

@property (nonatomic, strong) FLFriendList* friends;

@end

@implementation FLFriendListTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = @"My Friends";

    self.friends = [[FLFriendList alloc] init];

    self.dataSource = [[FLExampleFriendDataSource alloc] init];

    if (self.dataSource != nil) {
        self.friends = [self.dataSource getFriends];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView*)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section {
    return self.friends.size;
}


- (UITableViewCell*)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"friendCell" forIndexPath:indexPath];
    
    // Configure the cell...
    FLFriend* friend = [self.friends getAtIndex:indexPath.row];
    cell.textLabel.text = friend.displayName;
    
    return cell;
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue*)segue sender:(id)senderCell {
    if ([segue.identifier isEqualToString:@"ShowFriendDetails"]) {
        if ([segue.destinationViewController isKindOfClass:[FLFriendTableDetailVC class]]) {
            FLFriendTableDetailVC* viewController = segue.destinationViewController;

            NSIndexPath* indexPath = [self.tableView indexPathForCell:senderCell];
            FLFriend* fren = [self.friends getAtIndex:indexPath.row];
            viewController.theFriend = fren;
        }
    }

    if ([segue.identifier isEqualToString:@"ShowMap"]) {
        if ([segue.destinationViewController isKindOfClass:[FLFriendMapVC class]]) {
            FLFriendMapVC* viewController = segue.destinationViewController;

            //Da per scontato che tutti i friend siano di tipo FLGeoFriend
            //viewController.friends = [self.friends getAll];

            //Controlla l'array e filtra solo gli oggetti di tipo FLGeoFriend
            NSMutableArray* arr = [[NSMutableArray alloc] init];
            [[self.friends getAll] enumerateObjectsUsingBlock:^(id _Nonnull obj, NSUInteger index, BOOL* _Nonnull stop) {
                if ([obj isKindOfClass:[FLGeoFriend class]]) {
                    [arr addObject:obj];
                }
            }];
            viewController.friends = arr;
        }
    }
}

@end
