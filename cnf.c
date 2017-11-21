#include "cnf.h"

int startVar;
arrayOfVar var;
arrayOfProductionVar prodVar;
arrayOfProductionTerminal prodTerminal;

void initFile() {
	f = fopen("cnf.txt", "r");
}

void ignoreLine() {
	fgets(str, 100, f);
}

void getString() {
	fscanf(f,"%s", str);
}

void getInt() {
	fscanf(f, "%d", &num);
}

int findVarIdx(char temp[]) {
	for (int i = 0; i < var.varCount; ++i) {
		if (strcmp(temp, var.T[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void closeFile() {
	fclose(f);
}

void readCNF() {
	// Algorithm
	initFile();


	ignoreLine();								// Ignore # List of Variables line
	getInt();									// Get the number of variables
	var.varCount = num;

	for (int i = 0; i < var.varCount; i++) {
		getString();							// Get all the variables and store it
		strcpy(var.T[i], str);					// in var
	}

	for (int i = 0; i < var.varCount; ++i) {
		// printf("%s\n", var.T[i]);
	}

	ignoreLine();								// Ignore the rest of the line
	ignoreLine();								// Ignore # List of Variables line
	getString();								// Get the start variable
	startVar = findVarIdx(str);

	ignoreLine();								// Ignore the rest of the line
	ignoreLine();								// Ignore the # List of Production with two variables
	getInt();									// Get the number of production
	prodVar.prodCount = num;

	for (int i = 0; i < prodVar.prodCount; i++) {
		getString();								// Get the source string
		prodVar.T[i].sourceIdx = findVarIdx(str);

		getString();								// Get the var1 string
		prodVar.T[i].var1Idx = findVarIdx(str);

		getString();								// Get the var2 string
		prodVar.T[i].var2Idx = findVarIdx(str);
	}

	for (int i = 0; i < prodVar.prodCount; i++) {
		// printf("%d %d %d\n", prodVar.T[i].sourceIdx, prodVar.T[i].var1Idx, prodVar.T[i].var2Idx);
	}


	ignoreLine();								// Ignore the rest of the line
	ignoreLine();								// Ignore the list of terminal production
	getInt();									// Get the number of production
	prodTerminal.prodCount = num;

	for (int i = 0; i < prodTerminal.prodCount; i++) {
		getString();							// Get the source string
		prodTerminal.T[i].sourceIdx = findVarIdx(str);

		getString();							// Get the Terminal number
		prodTerminal.T[i].terminal = getToken(str);
	}

	// for (int i = 0; i < prodTerminal.prodCount; i++) {
		// printf("%d %d\n", prodTerminal.T[i].sourceIdx, prodTerminal.T[i].terminal);
	// }
}

Terminal getToken(char str[]) {
	if (!strcmp(str, "PROGRAM")) {
		return PROGRAM;
	} else if (!strcmp(str, "VAR")) {
		return VAR;
	} else if (!strcmp(str, "IDENTIFIER")) {
		return IDENTIFIER;
	} else if (!strcmp(str, "TYPE_INT")) {
		return TYPE_INT;
	} else if (!strcmp(str, "TYPE_REAL")) {
		return TYPE_REAL;
	} else if (!strcmp(str, "TYPE_CHAR")) {
		return ARRAY;
	} else if (!strcmp(str, "OF")) {
		return OF;
	} else if (!strcmp(str, "BEGIN")) {
		return BEGIN;
	} else if (!strcmp(str, "END")) {
		return END;
	} else if (!strcmp(str, "NUM_INT")) {
		return NUM_INT;
	} else if (!strcmp(str, "NUM_REAL")) {
		return NUM_REAL;
	} else if (!strcmp(str, "CHAR")) {
		return CHAR;
	} else if (!strcmp(str, "OPT")) {
		return OPT;
	} else if (!strcmp(str, "IF")) {
		return IF;
	} else if (!strcmp(str, "THEN")) {
		return THEN;
	} else if (!strcmp(str, "ELSE")) {
		return ELSE;
	} else if (!strcmp(str, "WHILE")) {
		return WHILE;
	} else if (!strcmp(str, "DO")) {
		return DO;
	} else if (!strcmp(str, "TO")) {
		return TO;
	} else if (!strcmp(str, "DOWNTO")) {
		return DOWNTO;
	} else if (!strcmp(str, "STEP")) {
		return STEP;
	} else if (!strcmp(str, "REPEAT")) {
		return REPEAT;
	} else if (!strcmp(str, "UNTIL")) {
		return UNTIL;
	} else if (!strcmp(str, "INPUT")) {
		return INPUT;
	} else if (!strcmp(str, "OUTPUT")) {
		return OUTPUT;
	} else if (!strcmp(str, "SEMICOLON")) {
		return SEMICOLON;
	} else if (!strcmp(str, "COLON")) {
		return COLON;
	} else if (!strcmp(str, "EQUAL")) {
		return EQUAL;
	} else if (!strcmp(str, "NOT_EQUAL")) {
		return NOT_EQUAL;
	} else if (!strcmp(str, "PERIOD")) {
		return PERIOD;
	} else if (!strcmp(str, "DOUBLE_PERIOD")) {
		return DOUBLE_PERIOD;
	} else if (!strcmp(str, "COMMA")) {
		return COMMA;
	} else if (!strcmp(str, "LESS")) {
		return LESS;
	} else if (!strcmp(str, "GREATER")) {
		return GREATER;
	} else if (!strcmp(str, "LESS_EQUAL")) {
		return LESS_EQUAL;
	} else if (!strcmp(str, "GREATER_EQUAL")) {
		return GREATER_EQUAL;
	} else if (!strcmp(str, "ASSIGNMENT")) {
		return ASSIGNMENT;
	} else if (!strcmp(str, "TICK")) {
		return TICK;
	} else if (!strcmp(str, "OPENSQPARAN")) {
		return OPENSQPARAN;
	} else if (!strcmp(str, "CLOSESQPARAN")) {
		return CLOSESQPARAN;
	} else if (!strcmp(str, "OPENPARAN")) {
		return OPENPARAN;
	} else if (!strcmp(str, "CLOSEPARAN")) {
		return CLOSEPARAN;
	} else if (!strcmp(str, "FOR")) {
		return FOR;
	} else if (!strcmp(str, "OPENCRPARAN")) {
		return OPENCRPARAN;
	} else if (!strcmp(str, "CLOSECRPARAN")) {
		return CLOSECRPARAN;
	} else if (!strcmp(str, "ARRAY")) {
		return ARRAY;
	} else if (!strcmp(str, "AND")) {
		return AND;
	} else if (!strcmp(str, "OR")) {
		return OR;
	} else {
		return -1;
	}
}
