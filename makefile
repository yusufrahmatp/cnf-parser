main: main.c cyk.c token.c
	gcc -o main -Wall -std=c99 cyk.c token.c -lm