#include "token.h"

#define NMaxCNFSourceLength 10
#define NMaxCNGArrLength 10

struct CNF {
	char source[NMaxCNFSourceLength];
	Token destination;
};

struct CNFArray {
	CNF cnf[NMaxCNGArrLength];
	int size;
};

