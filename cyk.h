#include "token.h"
#include "cnf.h"
#include "customstring.h"

#define NMaxCYK 20

// typedef struct yCYKElmtArray {
// 	StringArray arr[10];
// 	int size;
// } CYKElmtArray;

// typedef struct tCYK {
// 	StringArray mat[NMaxCYK][NMaxCYK];
// 	int row_size;
// 	int col_size;
// } CYK;

typedef struct tCYKElmt {
	int arr[10];
	int size;
} CYKElmt;

typedef struct tCYKMatrix {
	CYKElmt mat[100][100];
	int row_size;
	int col_size;
} CYKMatrix;

void InitializeCYK(CYKMatrix *C, int row_size, int col_size);

void SolveCYK(arrayOfProductionVar P1, arrayOfProductionTerminal P2, TerminalArray T);
