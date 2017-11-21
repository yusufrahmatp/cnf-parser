#include "cnf.h"

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

int findVarIdx(char str[]) {
	for (int i = 0; i < var.varCount; ++i) {
		if (strcmp(str, var.T[i]) == 0) {
			return i;
		}
	}
}

void readCNF() {
	// Variables
	char str[100];

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