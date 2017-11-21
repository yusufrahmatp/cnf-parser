#ifndef CNF_H_
#define CNF_H_

#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_LENGTH 100
#define MAX_VAR_COUNT 200
#define MAX_PROD_COUNT 300


typedef enum {
	PROGRAM, VAR, IDENTIFIER, TYPE_INT, TYPE_REAL, TYPE_CHAR, ARRAY, OF, BEGIN, END,
	NUM_INT, NUM_REAL, CHAR,
	OPT,
	IF, THEN, ELSE, WHILE, DO, TO, DOWNTO, STEP, REPEAT, UNTIL, FOR,
	INPUT, OUTPUT,
	SEMICOLON, COLON, EQUAL, NOT_EQUAL, PERIOD, DOUBLE_PERIOD, COMMA, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, ASSIGNMENT, TICK,
	OPENSQPARAN, CLOSESQPARAN, OPENPARAN, CLOSEPARAN
} Terminal;

typedef struct {
	char T[MAX_VAR_COUNT][MAX_VAR_LENGTH];
	int varCount;
} arrayOfVar;

typedef struct {
	int sourceIdx;
	int var1Idx;
	int var2Idx;
} ProductionVar;

typedef struct {
	ProductionVar T[MAX_PROD_COUNT];
	int prodCount;
} arrayOfProductionVar;

typedef struct {
	int sourceIdx;
	Terminal terminal;
} ProductionTerminal;

typedef struct {
	ProductionTerminal T[MAX_PROD_COUNT];
	int prodCount;
} arrayOfProductionTerminal;


FILE *f;
char str[MAX_VAR_LENGTH];
int num;

extern int startVar;
extern arrayOfVar var;
extern arrayOfProductionVar prodVar;
extern arrayOfProductionTerminal prodTerminal;

void initFile();

void readCNF();

int findVarIdx();

void ignoreLine();

void getString();

void getInt();

Terminal getToken(char str[]);

#endif
