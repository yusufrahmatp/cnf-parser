#include <stdio.h>
#include "boolean.h"
#include "customstring.h"
#include "cnf.h"
// #include "parser.h"

FILE* FIN;
char CC;
int cur_line;

typedef struct tTerminalElmt {
	char str[20];
	int line;
	int col;
} TerminalElmt;

typedef struct tTerminalArray {
	TerminalElmt arr[100];
	int size;
} TerminalArray;

const int terminal_enum[] = {
	PROGRAM, TYPE_INT, TYPE_REAL, TYPE_CHAR, ARRAY, OF, BEGIN,
	IF, THEN, ELSE, WHILE, DO, TO, DOWNTO, STEP, REPEAT, UNTIL,
	INPUT, OUTPUT,
	SEMICOLON, COLON, EQUAL, NOT_EQUAL, PERIOD, DOUBLE_PERIOD, COMMA, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, ASSIGNMENT, TICK
};

char terminal[][30] = {
	"program", "integer", "real", "char", "array", "of", "begin",
	"if", "then", "else", "while", "do", "to", "downto", "step", "repeat", "until",
	"input", "output",
	";", ":", "=", "<>", ".", "..", ",", "<", ">", "<=", ">=", ":=", "'"
};

boolean IsAlphabet(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

boolean IsNumerical(char c) {
	return (c >= '0' && c <= '9');
}

boolean IsAlphaNumerical(char c) {
	return (IsAlphabet(c) || IsNumerical(c));
}

void IgnoreBlank() {
	while (CC != EOF && (CC == ' ' || CC == '\n' || CC == '\t')) {
		CC = getc(FIN);
	}
}

boolean IsStringSame(char a[], char b[]) {
	return (strcmp(a,b) == 0);
}

boolean IsChar(char c[]) {
	int len = strlen(c);
	if (len != 3) {
		return false;
	}
	return c[0] == '\'' && c[2] == '\'';
}

boolean IsNumInt(char c[]) {
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		if (!IsNumerical(c[i]) && (i == 0 && !IsNumerical(c[i]) && c[i] != '-')) {
			return false;
		}
	}
	return true;
}

boolean IsNumReal(char c[]) {
	int postik = -1;
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		if (i == 0 && c[i] != '.' && c[i] != '-' && !IsNumerical(c[i])) {
			printf("lele goreng\n");
			return false;
		}
		if (c[i] == '.') {
			if (postik != -1) {
				printf("lele rebus\n");
				return false;
			} else {
				postik = i;
			}
		} else if (i != 0 && !IsNumerical(c[i])) {
			printf("lele kukus %c\n", c[i]);
			return false;
		}
	}
	return true;
}

int GetEnumValueFromTerminalString(char c[20]) {
	// Match string with easily identifiable terminal
	int arrsize = sizeof(terminal_enum)/sizeof(terminal_enum[0]);
	for (int i = 0; i < arrsize; i++) {
		if (IsStringSame(c, terminal[i])) {
			return terminal_enum[i];
		}
	}

	// handle special case string
	if (IsStringSame(c, "+") || IsStringSame(c, "-") || IsStringSame(c, "*") || IsStringSame(c, "/") || IsStringSame(c, "%")) {
		return OPT;
	} else if (IsChar(c)) {
		return CHAR;
	} else if (IsNumInt(c)) {
		return NUM_INT;
	} else if (IsNumReal(c)) {
		return NUM_REAL;
	}

	// if none matched, return -1 (error identifier)
	return -1;
}

// >= .. <= <>
// TODO:
// - build pipeline : read file => lower case => convert to
// - add line and col prop to each string/terminal
// - testing
void parse() {
	char file_name[] = "he.txt";
	FIN = fopen(file_name, "r");

	StringArray result;
	result.size = 0;

	boolean first = true;
	CC = getc(FIN);

	cur_line = 1;

	boolean noread = false;

	while (CC != EOF) {
		IgnoreBlank();

		if (!first && !noread) {
			CC = getc(FIN);
			IgnoreBlank();
		} else if (noread) {
			noread = false;
		}

		if (CC == EOF) {
			break;
		}

		if (IsAlphaNumerical(CC)) {
			if (IsAlphabet(CC)) {
				for (int i = 0; IsAlphaNumerical(CC) && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
					result.arr[result.size][i] = CC;
					CC = getc(FIN);
					if (!IsAlphaNumerical(CC) || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
						result.arr[result.size][i+1] = '\0';
						noread = true;
					}
				}
			} else {
				for (int i = 0; IsNumerical(CC) && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
					result.arr[result.size][i] = CC;
					CC = getc(FIN);
					if (!IsNumerical(CC) || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
						result.arr[result.size][i+1] = '\0';
						noread = true;
					}
				}
			}
		} else {
			if (CC == '<' || CC == '>') {
				result.arr[result.size][0] = CC;
				CC = getc(FIN);
				if (CC == '=' || (result.arr[result.size][0] == '<' && CC == '>')) {
					result.arr[result.size][1] = CC;
					result.arr[result.size][2] = '\0';
				} else {
					result.arr[result.size][1] = '\0';
					noread = true;
				}
			} else if (CC == '.') {
				result.arr[result.size][0] = CC;
				CC = getc(FIN);
				if (CC == '.') {
					result.arr[result.size][1] = CC;
					result.arr[result.size][2] = '\0';
				} else {
					result.arr[result.size][1] = '\0';
					noread = true;
				}
			} else if (CC == ':') {
				result.arr[result.size][0] = CC;
				CC = getc(FIN);
				if (CC == '=') {
					result.arr[result.size][1] = CC;
					result.arr[result.size][2] = '\0';
				} else {
					result.arr[result.size][1] = '\0';
					noread = true;
				}
			} else if (CC == '\'') {
				result.arr[result.size][0] = CC;
				for (int i = 1; CC != EOF; i++) {
					CC = getc(FIN);
					if (CC == EOF) {
						result.arr[result.size][i] = '\0';
					} else if (CC == '\'') {
						result.arr[result.size][i] = '\'';
						result.arr[result.size][i+1] = '\0';
						break;
					} else {
						result.arr[result.size][i] = CC;
					}
				}
			} else {
				result.arr[result.size][0] = CC;
				result.arr[result.size][1] = '\0';
			}
		}

		printf(">>> %s\n", result.arr[result.size]);

		result.size++;

		first = false;

		IgnoreBlank();
	}
}

int main() {
	char a[] = "'1'";
	char b[] = "-23";
	char c[] = "-.3";
	printf("%s itu %s\n", a, (IsChar(a) ? "char" : "bukan char"));
	printf("%s itu %s\n", b, (IsNumInt(b) ? "int" : "bukan int"));
	printf("%s itu %s\n", c, (IsNumReal(c) ? "real" : "bukan real"));
	// parse();
	// char c[] = "+";
	// printf("hasil %d\n", GetEnumValueFromTerminalString(c));
}