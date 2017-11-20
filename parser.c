#include <stdio.h>
#include "boolean.h"
#include "customstring.h"
// #include "parser.h"

FILE* FIN;
char CC;
int cur_line;

typedef struct tTerminalElmt {
	char str[20];
	int line;
} TerminalElmt;

typedef struct tTerminalArray {
	TerminalElmt arr[100];
	int size;
} TerminalArray;

// char terminals[][30] =
// {
// 	"program", "var", "integer", "real", "char", "array", "of", "begin",
// 	"+", "-", "*", "/",
// 	"div", "mod", "if", "then", "else", "while", "do", "to", "downto", "step", "repeat", "until",
// 	"input", "output",
// 	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
// 	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
// 	";", ":", "=", ".", ",", "<", ">", "<=", ">=", "=", "<>", "'"
// }; // size

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

void parse() {
	char file_name[] = "he.txt";
	// printf("Enter file name: "); scanf("%s", file_name);
	FIN = fopen(file_name, "r");

	TerminalArray result;
	result.size = 0;

	boolean first = true;
	CC = getc(FIN);

	cur_line = 1;

	boolean noread = false;

	while (CC != EOF) {
		IgnoreBlank();

		if (!first && !noread) {
			printf("bukan first\n");
			CC = getc(FIN);
			noread = false;
		}

		if (IsAlphaNumerical(CC)) {
			for (int i = 0; IsAlphaNumerical(CC) && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
				result.arr[result.size][i] = CC;
				CC = getc(FIN);
				if (!IsAlphaNumerical(CC) || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
					result.arr[result.size][i+1] = '\0';
				}
				if (!IsAlphaNumerical(CC)) {
					noread = true;
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
				}
			} else {
				result.arr[result.size][0] = CC;
				result.arr[result.size][1] = '\0';
				CC = getc(FIN);
			}
		}

		printf(">>> %s\n", result.arr[result.size]);

		result.size++;

		first = false;

		IgnoreBlank();
	}
}

int main() {
	parse();
}