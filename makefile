all: compile

compile:
	gcc -I ./include -o ./lib/dllist.o -c ./src/dllist.c
	gcc -I ./include -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include -o ./lib/jrb.o -c ./src/jrb.c
	gcc -I ./include -o ./lib/jval.o -c ./src/jval.c
	gcc -I ./include -o ./bin/program.out ./lib/dllist.o ./lib/fields.o ./lib/jrb.o ./lib/jval.o ./src/src.c

