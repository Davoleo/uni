//
// Created by Leo Dav on 06/05/22.
//

#import "FLExampleFriendDataSource.h"

#import "FLGeoFriend.h"

@interface FLExampleFriendDataSource()

@property (nonatomic, strong) FLFriendList* friends;

- (void) addFriends;

@end

@implementation FLExampleFriendDataSource

- (instancetype) init {
    if (self = [super init]) {
        _friends = [[FLFriendList alloc] init];
        [self addFriends];
    }

    return self;
}

- (void)addFriends {
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

- (FLFriendList*)getFriends {
    return self.friends;
}




@end