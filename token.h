#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdio.h>

#define NMaxTokenLength 10
#define NMaxTokenArrSize 20

#define TERMINAL_TOKEN_TYPE 'T'
#define VARIABLE_TOKEN_TYPE 'V'

typedef struct tToken {
	char str[NMaxTokenLength];
	char str2[NMaxTokenLength];
	char type;
} Token;

typedef struct tTokenArray {
	Token arr[NMaxTokenArrSize];
	int size;
} TokenArray;

void InitializeTokenArray(TokenArray *T);

#endif
