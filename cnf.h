#ifndef CNF_H_
#define CNF_H_

#include "token.h"

#define NMaxCNFSourceLength 10
#define NMaxCNGArrLength 10

typedef struct tCNF {
	char source[NMaxCNFSourceLength];
	Token destination;
} CNF;

typedef struct tCNFArray {
	CNF arr[NMaxCNGArrLength];
	int size;
} CNFArray;

#endif
