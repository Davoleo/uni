//
//  FLFriendListTableViewController.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendListTableViewController.h"
#import "FLFriendList.h"
#import "FLFriendTableDetailVC.h"
#import "FLGeoFriend.h"
#import "FLFriendMapVC.h"

@interface FLFriendListTableViewController ()

@property (nonatomic, strong) FLFriendList* friends;

- (void) setupData;

@end

@implementation FLFriendListTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = @"My Friends";

    self.friends = [[FLFriendList alloc] init];

    [self setupData];
}

- (void) setupData {
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Beltran" lastname:@"Jendrich" email:@"bjendrich0@dmoz.org"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Yale" lastname:@"Hallifax" email:@"yhallifax1@nhs.uk"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Adda" lastname:@"Cowlas" email:@"acowlas2@nationalgeographic.com"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Rodina" lastname:@"Cornish" email:@"rcornish3@histats.com"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Bobbye" lastname:@"Dunkerley" email:@"bdunkerley4@hibu.com"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Kincaid" lastname:@"Dunican" email:@"kdunican5@globo.com"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Renae" lastname:@"Pedracci" email:@"rpedracci6@simplemachines.org"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Langston" lastname:@"McDonell" email:@"lmcdonell7@cam.ac.uk"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Noak" lastname:@"Cuppitt" email:@"ncuppitt8@ebay.com"]];
    [self.friends add:[[FLGeoFriend alloc] initWithFirstname:@"Prentice" lastname:@"Geddes" email:@"pgeddes9@wix.com"]];

    NSArray* pois = [NSArray arrayWithObjects:
            [[FLPoi alloc] initWithName:@"Camp" latitude:44.1029482 longitude:10.8912385],
            [[FLPoi alloc] initWithName:@"Parc" latitude:44.1029322 longitude:10.2198322],
            [[FLPoi alloc] initWithName:@"Citt" latitude:44.4281722 longitude:10.2128947],
            [[FLPoi alloc] initWithName:@"Stattt" latitude:44.8391795 longitude:10.1023958],
            [[FLPoi alloc] initWithName:@"PAIL" latitude:44.1890273 longitude:10.1905812],
            [[FLPoi alloc] initWithName:@"Garara" latitude:44.1095781 longitude:10.1235823],
            [[FLPoi alloc] initWithName:@"Crocro" latitude:44.1297512 longitude:10.2934683],
            [[FLPoi alloc] initWithName:@"FEKJAKLFQJAWE" latitude:44.1290857 longitude:10.0239583],
            [[FLPoi alloc] initWithName:@"Staddd" latitude:44.1205978 longitude:10.4609863],
            [[FLPoi alloc] initWithName:@"CattaSu" latitude:44.1290484 longitude:10.1978512],
            nil];

    for (int i = 0; i < self.friends.size; i++) {
        FLFriend* f = [self.friends getAtIndex:i];
        f.avatar = [NSString stringWithFormat:@"https://robohash.org/%d.png?size=120x120", i];
        f.thumbnail = [NSString stringWithFormat:@"https://robohash.org/%d.png?size=36x36", i];
        if ([f isKindOfClass:[FLGeoFriend class]]) {
            FLGeoFriend* geofriend = (FLGeoFriend*) f;
            geofriend.location = [pois objectAtIndex:i];
        }
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
