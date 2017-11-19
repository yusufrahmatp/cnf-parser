#include <string.h>
#include "boolean.h"
#include "customstring.h"

void InitializeStringArray(StringArray *S) {
	S->size = 0;
}

boolean IsStringArrayFull(StringArray S) {
	return S.size == NMaxStringArrayLength;
}

void AddString(StringArray *S, char str[NMaxStringLength]) {
	if (!IsStringArrayFull(*S)) {
		strcpy(S->arr[S->size], str);
		S->size = S->size + 1;
	}
}
