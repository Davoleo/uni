#import "MDPoi.h"

@implementation MDPoi

//in objective-C tutti gli oggetti sono allocati dinamicamente sull'heap (motivo per cui si usano SEMPRE i pointer)
//Some Keywords:
//id = Puntatore ad un oggetto di qualsiasi tipo (simile a void* in C)
//nil = puntatore che punta a niente (NULL in C)
//BOOL = tipo definito (tramite typdef in objc.h) per boolean values
//	- YES == 1 (true)
//	- NO == 0 (false)
//self = puntatore all'oggetto corrente (uguale a 'this' in java)

- (double)latitude {
	return _latitude;
}
//La Method invocation è basata su message passing agli oggetti
//Il message passing è diverso dai metodi classici di invocazione perché il metodo eseguito non è legato ad una specifica sezione di codice
//	Il target è risolto dinamicamente a runtime
//Se il ricevitore di un messaggio non risponde -> un eccezione è lanciata
//è possibile mandare un messaggio a nil: 0 è ritornato
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
}

//visto che details è definito come una property nel .h si può chiamare con
NSString* str = poi.detail;

@end