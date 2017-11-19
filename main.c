#include <stdio.h>
#include <string.h>

#include "customstring.h"
#include "token.h"
#include "cnf.h"
#include "cyk.h"

CNFArray C;
StringArray S;

void InitCNF() {
	CNFArray C;

	C.size = 8;

	strcpy(C.cnf[0].source, "S");
	C.cnf[0].destination.type = VARIABLE_TOKEN_TYPE;
	strcpy(C.cnf[0].destination.str, "A");
	strcpy(C.cnf[0].destination.str2, "B");

	strcpy(C.cnf[1].source, "S");
	C.cnf[1].destination.type = VARIABLE_TOKEN_TYPE;
	strcpy(C.cnf[1].destination.str, "B");
	strcpy(C.cnf[1].destination.str2, "C");

	strcpy(C.cnf[2].source, "A");
	C.cnf[2].destination.type = VARIABLE_TOKEN_TYPE;
	strcpy(C.cnf[2].destination.str, "B");
	strcpy(C.cnf[2].destination.str2, "A");

	strcpy(C.cnf[3].source, "A");
	C.cnf[3].destination.type = TERMINAL_TOKEN_TYPE;
	strcpy(C.cnf[3].destination.str, "a");

	strcpy(C.cnf[4].source, "B");
	C.cnf[4].destination.type = VARIABLE_TOKEN_TYPE;
	strcpy(C.cnf[4].destination.str, "C");
	strcpy(C.cnf[4].destination.str2, "C");

	strcpy(C.cnf[5].source, "B");
	C.cnf[5].destination.type = TERMINAL_TOKEN_TYPE;
	strcpy(C.cnf[5].destination.str, "b");

	strcpy(C.cnf[6].source, "C");
	C.cnf[6].destination.type = VARIABLE_TOKEN_TYPE;
	strcpy(C.cnf[6].destination.str, "A");
	strcpy(C.cnf[6].destination.str2, "B");

	strcpy(C.cnf[7].source, "C");
	C.cnf[7].destination.type = TERMINAL_TOKEN_TYPE;
	strcpy(C.cnf[7].destination.str, "a");
}

void InitStringArray() {
	// b a a b a
	S.size = 5;
	strcpy(S.arr[0], "b");
	strcpy(S.arr[1], "a");
	strcpy(S.arr[2], "a");
	strcpy(S.arr[3], "b");
	strcpy(S.arr[4], "a");
}

int main() {
	InitCNF();
	InitStringArray();
	SolveCYK(C, S);
}