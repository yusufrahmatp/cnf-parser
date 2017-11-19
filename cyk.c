#include "cyk.h"
#include "token.h"

void InitializeCYK(CYK *C, int row_size, int col_size) {
	(*C).row_size = row_size;
	(*C).col_size = col_size;
}

void SolveCYK(CNFArray C, StringArray S) {
	CYK cyk;
	InitializeCYK(&cyk, S.size, S.size);
	for (int i = 0; i < S.size; i++) {
		for (int j = 0; j < (S.size - i); j++) {
			printf("%s ", S.arr[i]);
			if (j == 0) {
				// TODO: handle first row
			} else {
				// TODO: handle next row
			}
		}
		printf("\n");
	}
}

