#include <string.h>
#include "cnf.h"
#include "cyk.h"
#include "customstring.h"
#include "parser.h"
#include <stdlib.h>

void InitializeCYK(CYKMatrix *C, int row_size, int col_size) {
	C->mat = (CYKElmt **) malloc(sizeof(CYKElmt *) * row_size);
	for (int i = 0; i < row_size; i++) {
		C->mat[i] = (CYKElmt *) malloc(sizeof(CYKElmt) * col_size);
	}
	(*C).row_size = row_size;
	(*C).col_size = col_size;
}

void Dealloc(CYKMatrix *C) {
	for (int i = 0; i < C->row_size; i++) {
		free(C->mat[i]);
	}
	free(C->mat);
}

void SolveCYK(arrayOfProductionVar P1, arrayOfProductionTerminal P2, TerminalArray S) {
	CYKMatrix cyk;
	InitializeCYK(&cyk, S.size, S.size);
	for (int i = 0; i < S.size; i++) {
		for (int j = 0; j < (S.size - i); j++) {
			cyk.mat[i][j].size = 0;
			if (i == 0) {
				for (int k = 0; k < P2.prodCount; k++) {
					if (P2.T[k].terminal == S.arr[j].val) {
						cyk.mat[i][j].arr[cyk.mat[i][j].size] = P2.T[k].sourceIdx;
						cyk.mat[i][j].size++;
					}
				}

				// DEBUG - END
			} else {
				// generate cross
				int cross[50000][2];
				int cross_size = 0;
				for (int k = 0; k < i; k++) {
					CYKElmt S1 = cyk.mat[k][j];
					CYKElmt S2 = cyk.mat[i-k-1][j+k+1];
					if (S1.size != 0 && S2.size != 0) {
						for (int x = 0; x < S1.size; x++) {
							for (int y = 0; y < S2.size; y++) {
								// printf("CROSS %d %d\n", S1.arr[x],);
								cross[cross_size][0] = S1.arr[x];
								cross[cross_size][1] = S2.arr[y];
								cross_size++;
							}
						}
					}
				}

				// megik
				for (int k = 0; k < cross_size; k++) {
					for (int x = 0; x < P1.prodCount; x++) {
						if (P1.T[x].var1Idx == cross[k][0] && P1.T[x].var2Idx == cross[k][1]) {
							boolean already_in_arr = false;
							for (int y = 0; y < cyk.mat[i][j].size; y++) {
								if (cyk.mat[i][j].arr[y] ==  P1.T[x].sourceIdx) {
									already_in_arr = true;
									break;
								}
							}
							if (!already_in_arr) {
								cyk.mat[i][j].arr[cyk.mat[i][j].size] = P1.T[x].sourceIdx;
								cyk.mat[i][j].size++;
								// AddString(&(cyk.mat[i][j]), C.arr[x].source);
							}
						}
					}
				}
			}
		}
	}

	boolean AC = false;
	int ac_enum = 1; // START
	for (int i = 0 ; i < cyk.mat[S.size-1][0].size; i++) {
		if (cyk.mat[S.size-1][0].arr[i] == ac_enum) {
			AC = true;
			break;
		}
	}
	printf("Input program is: \n");
	if (AC) {
		printf("ACCEPTED\n");
	} else {
		printf("REJECTED\n");
	}
	Dealloc(&cyk);
}

void SolveCYKPrint(arrayOfProductionVar P1, arrayOfProductionTerminal P2, TerminalArray S) {
	CYKMatrix cyk;
	InitializeCYK(&cyk, S.size, S.size);
	for (int i = 0; i < S.size; i++) {
		for (int j = 0; j < (S.size - i); j++) {
			cyk.mat[i][j].size = 0;
			if (i == 0) {
				for (int k = 0; k < P2.prodCount; k++) {
					if (P2.T[k].terminal == S.arr[j].val) {
						cyk.mat[i][j].arr[cyk.mat[i][j].size] = P2.T[k].sourceIdx;
						cyk.mat[i][j].size++;
					}
				}
				// DEBUG - START
				for(int k = 0; k < cyk.mat[i][j].size; k++) {
					printf("%d/", cyk.mat[i][j].arr[k]);
				}
				printf(" ");
				// DEBUG - END
			} else {
				// generate cross
				int cross[50000][2];
				int cross_size = 0;
				for (int k = 0; k < i; k++) {
					CYKElmt S1 = cyk.mat[k][j];
					CYKElmt S2 = cyk.mat[i-k-1][j+k+1];
					if (S1.size != 0 && S2.size != 0) {
						for (int x = 0; x < S1.size; x++) {
							for (int y = 0; y < S2.size; y++) {
								// printf("CROSS %d %d\n", S1.arr[x],);
								cross[cross_size][0] = S1.arr[x];
								cross[cross_size][1] = S2.arr[y];
								cross_size++;
							}
						}
					}
				}

				// megik
				for (int k = 0; k < cross_size; k++) {
					for (int x = 0; x < P1.prodCount; x++) {
						if (P1.T[x].var1Idx == cross[k][0] && P1.T[x].var2Idx == cross[k][1]) {
							boolean already_in_arr = false;
							for (int y = 0; y < cyk.mat[i][j].size; y++) {
								if (cyk.mat[i][j].arr[y] ==  P1.T[x].sourceIdx) {
									already_in_arr = true;
									break;
								}
							}
							if (!already_in_arr) {
								cyk.mat[i][j].arr[cyk.mat[i][j].size] = P1.T[x].sourceIdx;
								cyk.mat[i][j].size++;
								// AddString(&(cyk.mat[i][j]), C.arr[x].source);
							}
						}
					}
				}

				for(int k = 0; k < cyk.mat[i][j].size; k++) {
					printf("%d/", cyk.mat[i][j].arr[k]);
				}
				if (cyk.mat[i][j].size == 0) {
					printf("XX");
				}
				printf(" ");
			}
		}
		printf("\n");
	}
	Dealloc(&cyk);
}
