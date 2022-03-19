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

//NSRange è una struct che specifica uno starting point e un offset su un array
// è passata per valore (è come un'array window)