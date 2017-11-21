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

	initFile();

	// Ignore the # list of variables
	ignoreLine();
	getInt();
	var.varCount = num;

	// Get all the variables
	for (int i = 0; i < var.varCount; i++) {
		getString();
		strcpy(var.T[i], str);
	}

	// Ignore the # list of production with two variables
	ignoreLine();
	getInt();


}