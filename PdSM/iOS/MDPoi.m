#import "MDPoi.h"

//Anonymous category containing hidden private properties and methods
@interface MDPoi() {
  @property (strong) NSString* privateProp;
  - (void) privateMethod;
}

@implementation MDPoi

//Fino ad iOS6 inizializzatori dovevano sempre ritornare id
//da iOS7 in poi nuova special keyword instancetype (vincola la costruzione all'oggetto di questa classe)
//Struttura molto simile in tutti
- (instancetype) initWithName:(NSString*) name latitude:(double)latitude longitude:(double)longitude {
	//inizializzo me stesso chiamando l'inizializzatore della super classe
	//Dentro l'if controllo che il padre non ritorni nil
	if (self = [super init]) {
		//Inizializzo le mie variabili d'istanza
		//l'inizializzatore NON deve usare le proprietà e i getter
		//Perché l'oggetto non è ancora ben formato -> quindi i metodi di interfaccia potrebbero non funzionare correttamente
		_name = [name copy];
		_latitude = latitude;
		_longitude = longitude;
	}
	return self;
}

//Deallocazione della memoria
//Viene chiamato il metodo release di tutte le variabili d'istanza oggetto (simile al distruttore in C++)
//Deve essere sovrascritto se ci sono delle variabili d'istanza non-primitive nella classe
//dealloc NON va mai chiamato direttamente [il lavoro lo fa il reference counter]
//Alla fine va chiamato anche il dealloc della classe padre (di default il metodo fa solo quello)
- (void) dealloc {
	[_name release];
	[super dealloc];
}

- (double)latitude {
	return _latitude;
}

- (void)setLatitude:(double)lat{
	self._latitude = lat;
}
//Genera le implementazione di getter e setter per la variabile membro _latitude con nome latitude e setLatitude automaticamente
//se latitude segue le convenzioni è possibile evitare di specificare il nome del membro privato
@synthesize latitude = _latitude;

- (double)longitude {
	return _longitude
}
- (void)setLongitude:(double)lon {
	_longitude = lon;
}

- (NSString*) detail {
	return [NSString stringWithFormat:@"%@ - (%f, %f)", _name, _latitude, _longitude];

	//Introspection test with isKindOfClass
	NSObject obj = "test";
	if ([obj isKindOfClass:[NSString class]]) {
		NSString* str = (NSString*) obj;
	}
	//SEL (@selector) Modo astratto di definire un metodo con nome 
	SEL selector = @selector(lowercaseString);
	if ([obj respondsToSelector:selector]) {
		NSString* str = [obj performSelector:selector];
	}
}

- (NSArray*) getAllPois {
	NSMutableArray* array = [[NSMutableArray alloc] init];
	//Alternative: Per la classe NSArray è disponibile un metodo che fa autorelase in automatico (costruttore oggetto autorilasciante)
	//NSMutableArray* array = [NSMutableArray array];
	//...
	//[array release]; //Wrong -> deallocazione dell'array una volta che viene restituito
	[array autorelease]; 
	//^ Piccolo cuscinetto temporale che consente all'oggetto chiamante del metodo di diventare proprietario dell'oggetto prima 
	//che venga distrutto da questo metodo con release
	return array;
}

//Implementazione del privateMethod dentro la category
- (void) privateMethod {

}

//Example method calls on object poi of type MDPoi:
double lat = [poi latitude];
[poi setLatitude:12.0F];
//Properties:
//Un modo conveniente di lavorare con getter e setter
//il compilatore riesce a capire questa notazione solo se sono usati le convenzioni standard per i nomi dei setter/getter
double lat = poi.latitude;
poi.latitude = 12.0F;

@interface test : NSObject {
	//è possibile evitare di definire getter e setter usando la parola chiave @property (il compilatore li definisce in automatico)
	@property double latitude;
	//definisce solo il getter
	@property (readonly) double latitude

	//Tipicamente i getter ritornano un oggetto che deve essere autorilasciante
	//3 modi di dire come i setter devono essere implementati
	@property (retain) NSString* name; //Dovra rimanere in vita fintanto che è in vita l'oggetto
	//@synthesize name Diventa
	- (void) setName:(NSString*) name {
		[_name release]; //Release della vecchia variabile istanza
		_name = [name retain]; //Si diventa proprietari del nuovo oggetto name e assegnato a _name
	}
	@property (copy) NSString* name; //si diventa proprietari di una copia di una
	- (void) setName:(NSString*) name {
		[_name release]; //Release della vecchia variabile istanza
		_name = [name copy]; //il valore impostato a _name è una copia di name
	}
	@property (assign) NSString* name; //si accetta che l'oggetto non è nostro di proprietà e che potrebbe sparire da un momento all'altro
	- (void) setName:(NSString*) name {
		_name = name //non si è proprietari della variabile assegnata a _name (potrebbe sparire da un momento all'altro)
	}
}

//visto che details è definito come una property nel .h si può chiamare con
NSString* str = poi.detail;

MDPoi* poi = [[MDPoi alloc] initWithName:@"MyPoi" latitude:45.2 longitude: 10.12];
[poi retain]; //retainCount = 2
[poi retain]; //retainCount = 3
[poi release]; //retainCount = 2
[poi release]; //retainCount = 1
[poi release]; //retainCount = 0 -> oggetto deallocato


@end