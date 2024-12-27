@interface NSString(MyCategory) {
- (int) countOccurrences:(char)c;
}
@end

@implementation NSString (MyCategory)

- (int) countOccurrences:(char)c {
	//...
}

@end

//Nel file di utilizzo si può chiamare
//#import "NSString+MyCategory.h"
//e in tutte le NSString successive potrò chiamare il metodo della category

//Possono anche esserci categorie anonime tramite cui definire metodi e property private all'interno del file .m 