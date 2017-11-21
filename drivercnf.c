#include "cnf.h"

int main() {
	// Algorithm
	initFile();

	ignoreLine();
	printf("%s\n", str);
	getInt();
	printf("%d\n", num);
	var.varCount = num;

	for (int i = 0; i < var.varCount; i++) {
		getString();
		strcpy(var.T[i], str);
	}

	for (int i = 0; i < var.varCount; ++i) {
		printf("%s\n", var.T[i]);
	}

	ignoreLine();
	printf("%s\n", str);
	ignoreLine();
	printf("%s\n", str);
	getString();
	printf("%s\n", str);
	startVar = findVarIdx(str);
	printf("%d\n", startVar);

	ignoreLine();
	printf("%s\n", str);
	ignoreLine();
	printf("%s\n", str);
	getInt();
	prodVar.prodCount = num;

	for (int i = 0; i < prodVar.prodCount; i++) {
		getString();
		prodVar.T[i].sourceIdx = findVarIdx(str);

		getString();
		prodVar.T[i].var1Idx = findVarIdx(str);

		getString();
		prodVar.T[i].var2Idx = findVarIdx(str);
	}

	for (int i = 0; i < prodVar.prodCount; i++) {
		printf("%d %d %d\n", prodVar.T[i].sourceIdx, prodVar.T[i].var1Idx, prodVar.T[i].var2Idx);
	}


	ignoreLine();
	printf("%s\n", str);
	ignoreLine();
	printf("%s\n", str);
	getInt();
	printf("%d\n", num);
	prodTerminal.prodCount = num;

	for (int i = 0; i < prodTerminal.prodCount; i++) {
		getString();
		prodTerminal.T[i].sourceIdx = findVarIdx(str);

		getString();
		prodTerminal.T[i].terminal = getToken(str);	
	}

	for (int i = 0; i < prodTerminal.prodCount; i++) {
		printf("%d %d\n", prodTerminal.T[i].sourceIdx, prodTerminal.T[i].terminal);
	}


}