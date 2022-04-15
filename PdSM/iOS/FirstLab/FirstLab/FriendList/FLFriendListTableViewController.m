//
//  FLFriendListTableViewController.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendListTableViewController.h"
#import "FLFriendList.h"
#import "FLFriendTableDetailVC.h"

@interface FLFriendListTableViewController ()

@property (nonatomic, strong) FLFriendList* friends;

@end

@implementation FLFriendListTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = @"My Friends";

    self.friends = [[FLFriendList alloc] init];

    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Beltran" lastname:@"Jendrich" email:@"bjendrich0@dmoz.org"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Yale" lastname:@"Hallifax" email:@"yhallifax1@nhs.uk"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Adda" lastname:@"Cowlas" email:@"acowlas2@nationalgeographic.com"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Rodina" lastname:@"Cornish" email:@"rcornish3@histats.com"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Bobbye" lastname:@"Dunkerley" email:@"bdunkerley4@hibu.com"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Kincaid" lastname:@"Dunican" email:@"kdunican5@globo.com"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Renae" lastname:@"Pedracci" email:@"rpedracci6@simplemachines.org"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Langston" lastname:@"McDonell" email:@"lmcdonell7@cam.ac.uk"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Noak" lastname:@"Cuppitt" email:@"ncuppitt8@ebay.com"]];
    [self.friends add:[[FLFriend alloc] initWithFirstname:@"Prentice" lastname:@"Geddes" email:@"pgeddes9@wix.com"]];
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
}

@end
