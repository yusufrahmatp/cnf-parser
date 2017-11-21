#include "cnf.h"

int startVar;
arrayOfVar var;
arrayOfProductionVar prodVar;
arrayOfProductionTerminal prodTerminal;

void initFile() {
	f = fopen("cnftest.txt", "r");
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
		printf("%s\n", var.T[i]);
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
		printf("%d %d %d\n", prodVar.T[i].sourceIdx, prodVar.T[i].var1Idx, prodVar.T[i].var2Idx);
	}


	ignoreLine();								// Ignore the rest of the line
	ignoreLine();								// Ignore the list of terminal production
	getInt();									// Get the number of production
	prodTerminal.prodCount = num;

	for (int i = 0; i < prodTerminal.prodCount; i++) {
		getString();							// Get the source string
		prodTerminal.T[i].sourceIdx = findVarIdx(str);

		getInt();								// Get the Terminal number
		prodTerminal.T[i].terminal = num;	
	}

	for (int i = 0; i < prodTerminal.prodCount; i++) {
		printf("%d %d\n", prodTerminal.T[i].sourceIdx, prodTerminal.T[i].terminal);
	}
}

Terminal getToken(char str[]) {
	if (strcmp(str, "PROGRAM")) {

	}
}