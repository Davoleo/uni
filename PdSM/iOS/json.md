## Working with JSON
Utile per fare storage di file o anche per fare comunicazione di rete serializzando gli oggetti runtime dell'app per spostarli in giro

- Class: `NSJSONSerialiazation`
- Provides method to serializa and deserialize data
- Serialized data must have the following properties: 
  - Top Level Object of type: `NSArray` or `NSDictionary`
  - Tutti i membri sono di tipo: `NSString`, `NSNumber`, `NSArray`, `NSDictionary`, `NSNull`
  - Le chiavi dei dizionari sono per forza di tipo `NSString`
- `isValidJSONObject:` restituisce se l'oggetto può essere serializzato
- `dataWithJSONObject` serializzazione -> ritorna uno stream di byte `NSData`
- `JSONObjectWithData` deserializzazione -> ritorna un id di un qualsiasi oggetto creato a partire dal JSON

```objectivec
NSData* data = [NSData dataWithContentsOfURL:url];
NSError* error;
NSDictionary* dictionary = [NSJONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
if (!error) {
	NSArray* teachers = [dictionary objectForKey:@"teachers"];
	[teachers enumerateObjectsUsingBlock:^(id obj, NSUInteger index, BOOL* stop) {
		if ([obj isKindOfClass:[NSDictionary class]]) {
			NSDictionary* pDict = (NSDictionary*)obj;
			Person* person = [[Person alloc] init];
			//Subscripting: modo più semplice che usare "objectAtIndex:" o "objectForKey:" usando l'operatore []
			person.name = pDict[@"name"];
			person.status = pDict[@"status"];
			person.imageURL = [NSURL URLWithString:pDict[@"photo"]];
			person.latitude = [pDict[@"latitude"] doubleValue];
			person.longitude = [pDict[@"longitude"] doubleValue];
		}
	}];
}
```