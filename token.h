#include <stdio.h>

#define NMaxTokenLength 10
#define NMaxTokenArrSize 20

#define TERMINAL_TOKEN_TYPE 'T'
#define VARIABLE_TOKEN_TYPE 'V'

struct Token {
	char str[NMaxTokenLength];
	char str2[NMaxTokenLength];
	char type;
};

struct TokenArray {
	Token arr[NMaxTokenArrSize];
	int size;
};

void InitializeTokenArray(TokenArray *T);
