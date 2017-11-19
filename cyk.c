#include <string.h>
#include "cnf.h"
#include "cyk.h"
#include "token.h"
#include "customstring.h"

void InitializeCYK(CYK *C, int row_size, int col_size) {
	(*C).row_size = row_size;
	(*C).col_size = col_size;
}

void SolveCYK(CNFArray C, StringArray S) {
	CYK cyk;
	InitializeCYK(&cyk, S.size, S.size);
	for (int i = 0; i < S.size; i++) {
		for (int j = 0; j < (S.size - i); j++) {
			InitializeStringArray(&(cyk.mat[i][j]));
			if (i == 0) {
				for (int k = 0; k < C.size; k++) {
					if (C.arr[k].destination.type == TERMINAL_TOKEN_TYPE && strcmp(C.arr[k].destination.str, S.arr[j]) == 0) {
						AddString(&(cyk.mat[i][j]), C.arr[k].source);
					}
				}
				// DEBUG - START
				for(int k = 0; k < cyk.mat[i][j].size; k++) {
					printf("%s/", cyk.mat[i][j].arr[k]);
				}
				printf(" ");
				// DEBUG - END
			} else {
				// generate cross
				char cross[100][2][10];
				int cross_size = 0;
				for (int k = 0; k < i; k++) {
					StringArray S1 = cyk.mat[k][j];
					StringArray S2 = cyk.mat[i-k-1][j+k+1];
					if (S1.size != 0 && S2.size != 0) {
						for (int x = 0; x < S1.size; x++) {
							for (int y = 0; y < S2.size; y++) {
								// printf("gengg %s %s\n", S1.arr[x], S2.arr[y]);
								strcpy(cross[cross_size][0], S1.arr[x]);
								strcpy(cross[cross_size][1], S2.arr[y]);
								cross_size++;
							}
						}
					}
				}

				// megik
				for (int k = 0; k < cross_size; k++) {
					for (int x = 0; x < C.size; x++) {
						if (C.arr[x].destination.type == VARIABLE_TOKEN_TYPE && strcmp(C.arr[x].destination.str, cross[k][0]) == 0 && strcmp(C.arr[x].destination.str2, cross[k][1]) == 0) {
							boolean already_in_arr = false;
							for (int y = 0; y < cyk.mat[i][j].size; y++) {
								if (strcmp(cyk.mat[i][j].arr[y], C.arr[x].source) == 0) {
									already_in_arr = true;
									break;
								}
							}
							if (!already_in_arr) {
								AddString(&(cyk.mat[i][j]), C.arr[x].source);
							}
						}
					}
				}

				for(int k = 0; k < cyk.mat[i][j].size; k++) {
					printf("%s/", cyk.mat[i][j].arr[k]);
				}
				if (cyk.mat[i][j].size == 0) {
					printf("XX");
				}
				printf(" ");
			}
		}
		printf("\n");
	}
}

