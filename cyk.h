#include "token.h"
#include "cnf.h"
#include "customstring.h"

#define NMaxCYK 20

typedef struct yCYKElmtArray {
	StringArray arr[10];
	int size;
} CYKElmtArray;

typedef struct tCYK {
	StringArray mat[NMaxCYK][NMaxCYK];
	int row_size;
	int col_size;
} CYK;

void InitializeCYK(CYK *C, int row_size, int col_size);

void SolveCYK(CNFArray C, StringArray S);
