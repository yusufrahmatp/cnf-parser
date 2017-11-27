#include "cnf.h"
#include "customstring.h"
#include "parser.h"

#define NMaxCYK 20

typedef struct tCYKElmt {
	int arr[10];
	int size;
} CYKElmt;

typedef struct tCYKMatrix {
	CYKElmt **mat;
	int row_size;
	int col_size;
} CYKMatrix;

void InitializeCYK(CYKMatrix *C, int row_size, int col_size);

void SolveCYK(arrayOfProductionVar P1, arrayOfProductionTerminal P2, TerminalArray T);
