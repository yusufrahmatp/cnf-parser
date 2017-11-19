#include "token.h"

#define NMaxCYK 20

struct CYK {
	TokenArray mat[NMaxCYK][NMaxCYK];
	int row_size;
	int col_size;
};

void InitializeCYK(int row_size, int col_size);