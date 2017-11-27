#include <stdio.h>
#include <string.h>

#include "customstring.h"
#include "cnf.h"
#include "cyk.h"

// CNFArray C;
// StringArray S;

// void InitCNF() {

// 	C.size = 8;

	// strcpy(C.arr[0].source, "S");
	// C.arr[0].destination.type = VARIABLE_TOKEN_TYPE;
	// strcpy(C.arr[0].destination.str, "A");
	// strcpy(C.arr[0].destination.str2, "B");

	// strcpy(C.arr[1].source, "S");
	// C.arr[1].destination.type = VARIABLE_TOKEN_TYPE;
	// strcpy(C.arr[1].destination.str, "B");
	// strcpy(C.arr[1].destination.str2, "C");

	// strcpy(C.arr[2].source, "A");
	// C.arr[2].destination.type = VARIABLE_TOKEN_TYPE;
	// strcpy(C.arr[2].destination.str, "B");
	// strcpy(C.arr[2].destination.str2, "A");

	// strcpy(C.arr[3].source, "A");
	// C.arr[3].destination.type = TERMINAL_TOKEN_TYPE;
	// strcpy(C.arr[3].destination.str, "a");

	// strcpy(C.arr[4].source, "B");
	// C.arr[4].destination.type = VARIABLE_TOKEN_TYPE;
	// strcpy(C.arr[4].destination.str, "C");
	// strcpy(C.arr[4].destination.str2, "C");

	// strcpy(C.arr[5].source, "B");
	// C.arr[5].destination.type = TERMINAL_TOKEN_TYPE;
	// strcpy(C.arr[5].destination.str, "b");

	// strcpy(C.arr[6].source, "C");
	// C.arr[6].destination.type = VARIABLE_TOKEN_TYPE;
	// strcpy(C.arr[6].destination.str, "A");
	// strcpy(C.arr[6].destination.str2, "B");

	// strcpy(C.arr[7].source, "C");
	// C.arr[7].destination.type = TERMINAL_TOKEN_TYPE;
	// strcpy(C.arr[7].destination.str, "a");
// }

// void InitStringArray() {
// 	// b a a b a
// 	S.size = 5;
// 	strcpy(S.arr[0], "b");
// 	strcpy(S.arr[1], "a");
// 	strcpy(S.arr[2], "a");
// 	strcpy(S.arr[3], "b");
// 	strcpy(S.arr[4], "a");
// }

int main() {
	// InitCNF();
	// InitStringArray();
	readCNF();
	parse();
	SolveCYK(prodVar, prodTerminal, resultX);
}
