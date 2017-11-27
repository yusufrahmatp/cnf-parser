#ifndef CUSTOMSTRING_H_
#define CUSTOMSTRING_H_

#include <string.h>
#include "boolean.h"

#define NMaxStringLength 10
#define NMaxStringArrayLength 10000

typedef struct tStringArray {
	char arr[1000][1000];
	int size; // size of the array
} StringArray;

void InitializeStringArray(StringArray *S);

boolean IsStringArrayFull(StringArray S);

void AddString(StringArray *S, char str[1000]);

#endif
