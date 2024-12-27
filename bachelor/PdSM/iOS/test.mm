// This file can contain C++ code as well as Objective-C
@interface Test : NSObject {
}

//Ogni volta che viene invocato un metodo: nello stack vieen creato un activation record
//Nell'activation record in questo caso ci sarà: n, j
- (void) countdown:(int)n {
	int j;
	if ([self isEven:n] == YES)
		j = n/2;
	else
		j = n+1;
	for (j; j>0; j--) {
		//Stampa su console una stringa Obj-C anche formattata con placeholder
		NSLog(@"%d", j);
	}
}

//Nell'activation record ci sarà: m, even
//l'activation record verrà distrutto non appena si ritorna fuori dal metodo
- (BOOL) isEven:(int)num {
	BOOL even = (num % 2 == 0);
	if (even == YES)
		return YES;
	else
		return NO;
}