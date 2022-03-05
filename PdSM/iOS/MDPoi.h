//#import diversamente da #include Protegge automaticamente da inclusione multipla di header file
#import <Foundation/Foundation.h>
//Foundation Framework : definisce tutte le classi base che si possono utilizzare per sviluppare altro
//- Comune a iOS e Mac OSX 
//Esempi Classi di Foundation Framework
//- NSObject: base di tutti gli oggetti [simile a Object in Java]
//	- qualsiasi oggetto è un NSObject
//	- Classi e instance methods per memory management
//	- Fornisce metodi di introspezione (vedo MDPoi.m)
//- NSString classe per gestire sequenze di caratteri Unicode (invece che le CString)
	NSString* immString = @"This is an Objective-C string";
//	- NSString sono IMMUTABILI (nuova NSString per ogni NSString method)
//- NSMutableString è una NSString mutabile
//  - è una versione mutabile di NSString (ha tutti i metodi della superclasse)
//	- permette di utilizzare la stringa e modificarla senza crearne nuove copie (utile in certi casi)
//- NSNumber: wrappa gli oggetti primitivi in un oggetto
//	- Negli array Objective-C non si possono mettere gli oggetti primitivi quindi bisogna usare NSNumber
//	- Permette di estrarre degli NSNumber dalle variabili primitive
NSNumber* number = [NSNumber numberWithInt: 2];
// Convert back to int
int i = [number intValue]
// Metodo alternativo più veloce
number = @(10)
//NSData e NSMutableData utilizzati per storare un flusso di byte
//Esempio: ritornati da connessioni internet
//NSDate: Per fare operazioni su date: [calcoli, formattazione]
//NSTimeInterval(double) è anche utile per gestire operazioni su date [è sotto sotto un dato]
//Esempi:
NSDate* now = [NSDate date];
NSDate* nextHour = [NSDate dateWithTimeIntervalSinceNow:3600];
NSTimeInterval delta = [now timeIntervalSinceDate:nextHour];
//NSArray e NSMutableArray: è una lista ordinata di oggetti
//- NSArray possono storare oggetti di tipo qualunque
//nil serve per terminare la lista di argomenti variabile (come gli oggetti nella lista)
//Analoghi dell'ArrayList in java
NSArray* array = [NSArray arrayWithObjects:@"string", [NSNumber numberWithInt:10], nil];
int size = [array count];
id first = [array objectAtIndex:0];
id last = [array lastObject];
NSMutableArray* array2 = [NSMutableArray arrayWithObjects:@"str1", @"str2", nil];
[array2 addObject:@"str3"];
[array2 insertObject: @"first", atIndex:0];
[array2 removeObjectAtIndex:1];
//^ l'array si shrinka automaticamente
//NSNull -> rappresentazione (wrapper) di un oggetto nil che si può inserire dentro array
//Costruzione veloce di NSArray
NSArray* fastarr = @[@"a", @"b", @"1", @(10)];
//Crea un array mutabile tramite un altro array
NSMutableArray* mfastarray = [NSMutableArray arrayWithArray:array];

//NSDictionary e NSMutableDictionary
//- Una mappa di Key/Value pairs
//- sia la chiave che le value sono oggetti
//- le chiavi usate devono appartenere ad una classe che implementa: hash e isEqual (per buildare la struttura dati)
//- le chiavi spesso sono NSString
NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys: @"value1", @"key1", @"value2", @"key2", nil];
int size = [dict count];
id val = [dict objectForKey: @"key1"];
NSMutableDictionary* dict2 = [NSMutableDictionary dictionary];
[dict2 setObject:@"value" forKey@"key"];
[dict2 removeObjectForKey: @"key"];
//Alternative
NSDictionary* fastdict = @{
	@"key1":@"value1",
	@"key2":@"value2"
};

//NSSet e NSMutableSet: lista non ordinata di oggetti
//Si possono buttare oggetti di tipo diverso dentro (bisogna usare introspezione)
NSSet* set = [NSSet setWithObjects: @"obj1", @"obj2", @"obj3", nil];
int size = [set count];
id random = [set anyObject];
NSMutableSet* mset = [NSMutableSet set];
[mset addObject:@"string1"];
[mset addObject:@"string2"];
[mset removeObject:@"string1"];

//Iterare sulle collection
//Metodo 1:
for (int i = 0; i < [alpha count]; i++) {
	id object = [alpha objectAtIndex:i];
	//do something with object
	if ([object isKindOfClass:[NSString class]]) {
		//do something with string
	}
}
//Metodo 2: Enumeration (for-in)
for (id object in alpha) {
	if ([object isKindOfClass:[NSString class]]) {
		NSString* string = (NSString*) object;
		//do something with string
	}
}
//Con cast implicito (da fare solo se si è sicuri dell'omogeneità degli oggetti collezione)
for (NSString* string in alpha) {
	//do something with string
}

//Dichiarazione della classe: MDPoi che estende la class NSObject (tutte le classi devono estendere questa classe)
//Non esistono package e namespace (quindi i nomi delle classi devono essere unique over all the project) => 

//Prefissi ---
//Ci vuole un prefisso davanti al nome in modo da assicurarsi che non ci siano conflitti (MD = Mobile Development ad esempio)
//Le classi di default dell'objective-c hanno come prefisso NS (NextSTEP la compagnia che ha sviluppato Objective-C prima della Apple)
@interface MDPoi : NSObject {
	//Classe che definisce le stringhe | I tipi composti devono essere passati come puntatori (e non possono essere passati per valore)
@private
	NSString* _name;
	double _latitude;
	double _longitude;
	//Convention: ^ gli identificatori dei Campi privati della classe devono iniziare con un underscore
	//Di default i campi sono protected

	@property (readonly) NSString* detail;
}

//returns _latitude (getter method): la convenzione è di rimuovere l'underscore dal nome della variabile privata
- (double)latitude;
- (void)setLatitude:(double)lat;
//Setter ^

- (double)longitude;
- (void)setLongitude:(double)lon;

//il dash - significa che il metodo è di istanza (lavora sull'oggetto)
//il più + significa che il metodo è di classe (e.g. static)
//NSArray* = return type tra parentesi prima del nome del metodo
//nome del metodo spezzato in più parti (prima dei 2 punti)
- (NSArray*)pointsWithinRange:(double)distance fromPoi:(MDPoi*)poi;
//This method's name is: pointsWithinRange:fromPoi
//example invocation
NSArray* list = [self pointsWithinRange:10.0F fromPoi:poi]

//alcuni metodi hanno nomi molto lunghi
- (BOOL)tableView:(UITableView*)tableView
	canPerformAction:(SEL)action
	forRowAtIndexPath:(NSIndexPath*)indexPath
	withSender:(id)sender;

//example call
//BOOL x = [tableView:myTable canPerformAction:myAction forRowAtIndexPath:myIP withSender:sender]

@end