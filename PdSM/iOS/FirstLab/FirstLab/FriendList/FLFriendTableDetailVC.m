//
//  FLFriendTableDetailVC.m
//  FirstLab
//
//  Created by Leo Dav on 15/04/2022.
//

#import "FLFriendTableDetailVC.h"

@interface FLFriendTableDetailVC ()

@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *surnameLabel;
@property (weak, nonatomic) IBOutlet UILabel *emailLabel;

@end

@implementation FLFriendTableDetailVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = self.theFriend.displayName;
    
    self.nameLabel.text = self.theFriend.firstname;
    self.surnameLabel.text = self.theFriend.lastname;
    self.emailLabel.text = self.theFriend.email;
}

@end
