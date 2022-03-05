//#import diversamente da #include Protegge automaticamente da inclusione multipla di header file
#import <Foundation/Foundation.h>

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

//Dichiarazione Inizializzatore esempio
- (instancetype) initWithName:(NSString*)name latitude:(double)latitude longitude:(double)longitude;

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