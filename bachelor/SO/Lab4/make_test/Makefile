# Makefiles components
# - Targets: I file che devono essere creati o l'azione da compiere
# - Prerequisites: file utilizzati come input per creare il target | di solito sono più di uno
# - Recipe: l'azione come sequenza di uno o più comandi su una riga o più righe da essere eseguiti 
#	(ogni linea della recipe di un target è preceduta da un TAB)
#	una recipe di solito si trova in una rule che serve a creare un target ogni talvolta che i prerequisites cambiano
# - Una regola spiega come e quando rifare alcuni file che sono il target di una particolare regola
#	(la ricetta viene eseguita sui prerequisite formando i target)
# Le rule possono differenziarsi un pochino da questo template in quanto possono contenere altre cose ma essenzialmente hanno solo bisogno di questo

# Example
edit: main.o kbd.o command.o display.o insert.o search.o files.o utils.o
	cc -o edit main.o kdb.o command.o display.o insert.o search.o files.o utils.o

main.o : main.c defs.h
	cc -c main.c
kbd.o: kbd.c defs.h command.h
	cc -c kbd.c
command.o: command.c defs.h command.h
	cc -c command.c
display.o: display.c defs.h buffer.h
	cc -c display.c
insert.o: insert.c defs.h buffer.h
	cc -c insert.c
search.o: search.c defs.h buffer.h
	cc -c search.c
files.o: files.c defs.h buffer.h command.h
	cc -c files.c
utils.o: utils.c defs.h
	cc -c utils.c

clean:
	rm edit main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o

# Note i Makefile non sanno niente delle recipe, le eseguono in modo asettico quando ce n'è bisogno ma è up to il programmatore di 
# modificare i file correttamente