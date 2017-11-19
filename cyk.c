#include "cyk.h"

void InitializeCYK(CYK *C, int row_size, int col_size) {
	(*C).row_size = row_size;
	(*C).col_size = col_size;
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			InitializeTokenArray(&((*C).mat[i][j]));
		}
	}
}
