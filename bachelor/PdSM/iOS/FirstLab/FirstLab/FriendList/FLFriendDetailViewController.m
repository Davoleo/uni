//
//  FLFriendDetailViewController.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendDetailViewController.h"
#import "FLFriend.h"

@interface FLFriendDetailViewController ()

@property (weak, nonatomic) IBOutlet UILabel *firstnameLabel;
@property (weak, nonatomic) IBOutlet UILabel *lastnameLabel;
@property (weak, nonatomic) IBOutlet UILabel *emailLabel;

@end

@implementation FLFriendDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = self.theFriend.displayName;

    self.firstnameLabel.text = self.theFriend.firstname;
    self.lastnameLabel.text = self.theFriend.lastname;
    self.emailLabel.text = self.theFriend.email;
}

@end
