#ifndef CUSTOMSTRING_H_
#define CUSTOMSTRING_H_

#include <string.h>
#include "boolean.h"

#define NMaxStringLength 10
#define NMaxStringArrayLength 10

typedef struct tStringArray {
	char arr[NMaxStringArrayLength][NMaxStringLength];
	int size; // size of the array
} StringArray;

void InitializeStringArray(StringArray *S);

boolean IsStringArrayFull(StringArray S);

void AddString(StringArray *S, char str[NMaxStringLength]);

#endif