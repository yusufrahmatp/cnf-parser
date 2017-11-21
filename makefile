main: main.c cnf.c cyk.c parser.c customstring.c
	gcc -o main -Wall -std=c99 main.c cnf.c cyk.c parser.c customstring.c -lm