@protocol MyProtocol

//Default: Required
- (void) method1;
- (NSString*) method2;

//Non deve essere implementato per forza
@optional
- (void)optionalMethod;

//Deve essere implementato per forza
@required
- (NSArray*)method3: (NSString*) str;

@end

@interface ClasseConforme : NSObject<MyProtocol> {

}

@end

@implementation ClasseConforme 

//Implementazione metodi interfacce
- (void) method1 {
	//...
}
- (NSString*) method2 {
	//...
}
- (NSArray*)method3: (NSString*) str {
	//...
}

@end

//Controllo se ClasseConforme implementa il metodo opzionale (e se quidni posso chiamarlo)
if ([target respondsToSelector:@selector(optionalMethod)]) {
	[target optionalMethod]
}