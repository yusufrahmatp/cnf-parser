#include <stdio.h>
#include "boolean.h"
#include "customstring.h"
#include "cnf.h"
#include "parser.h"
#include <unistd.h>

FILE* FIN;
char CC;
int cur_line;
int cur_col;
StringArray result;

TerminalArray resultX;

const int terminal_enum[] = {
	PROGRAM, VAR, TYPE_INT, TYPE_REAL, TYPE_CHAR, ARRAY, OF, BEGIN, END,
	IF, THEN, ELSE, WHILE, DO, TO, DOWNTO, STEP, REPEAT, UNTIL, FOR, AND, OR,
	INPUT, OUTPUT,
	SEMICOLON, COLON, EQUAL, NOT_EQUAL, PERIOD, DOUBLE_PERIOD, COMMA, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, ASSIGNMENT, TICK,
	OPENSQPARAN, CLOSESQPARAN, OPENPARAN, CLOSEPARAN, OPENCRPARAN, CLOSECRPARAN
};

char terminal[][30] = {
	"program", "var", "integer", "real", "char", "array", "of", "begin", "end",
	"if", "then", "else", "while", "do", "to", "downto", "step", "repeat", "until", "for", "and", "or",
	"input", "output",
	";", ":", "=", "<>", ".", "..", ",", "<", ">", "<=", ">=", ":=", "'",
	"[", "]", "(", ")", "{", "}"
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

void NextLine() {
	cur_line++;
	cur_col = 1;
}

void IgnoreBlank() {
	if (CC == '\n') {
		NextLine();
	}
	while (CC != EOF && (CC == ' ' || CC == '\n' || CC == '\t')) {
		CC = getc(FIN);
		if (CC == '\n') {
			NextLine();
		}
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
			return false;
		}
		if (c[i] == '.') {
			if (postik != -1) {
				return false;
			} else {
				postik = i;
			}
		} else if (i != 0 && !IsNumerical(c[i])) {
			return false;
		}
	}
	return true;
}

boolean IsVariable(char c[]) {
	int len = strlen(c);
	if (len < 1) {
		return false;
	}
	if (!IsAlphaNumerical(c[0])) {
		return false;
	}
	for (int i = 1; i < len; i++) {
		if (!IsAlphaNumerical(c[i])) {
			return false;
		}
	}
	return true;
}

void TranslateEnumToString(char c[], int x) {
	// Match string with easily identifiable terminal
	int arrsize = sizeof(terminal_enum)/sizeof(terminal_enum[0]);
	for (int i = 0; i < arrsize; i++) {
		if (terminal_enum[i] == x) {
			strcpy(c, terminal[i]);
			return;
		}
	}

	if (x == OPT) {
		strcpy(c, "+");
	} else if (x == CHAR) {
		strcpy(c, "'a'");
	} else if (x == NUM_INT) {
		strcpy(c, "123");
	} else if (x == NUM_REAL) {
		strcpy(c, "1.23");
	} else if (x == IDENTIFIER) {
		strcpy(c, "abc");
	} else {
		strcpy(c, ">ERROR<");
	}
}

int GetEnumValueFromTerminalString(char c[20]) {
	// lowecase string
	for (int i = 0; c[i] != '\0'; i++) {
		if (c[i] >= 'A' && c[i] <= 'Z') {
			c[i] = c[i] - 'A' + 'a';
		}
	}

	// printf(">>>%s<<<<\n", c);
	// Match string with easily identifiable terminal
	int arrsize = sizeof(terminal_enum)/sizeof(terminal_enum[0]);
	for (int i = 0; i < arrsize; i++) {
		if (IsStringSame(c, terminal[i])) {
			return terminal_enum[i];
		}
	}

	// handle special case string
	if (IsStringSame(c, "+") || IsStringSame(c, "-") || IsStringSame(c, "*") || IsStringSame(c, "div") || IsStringSame(c, "mod")) {
		return OPT;
	} else if (IsChar(c)) {
		return CHAR;
	} else if (IsNumInt(c)) {
		return NUM_INT;
	} else if (IsNumReal(c)) {
		return NUM_REAL;
	} else if (IsVariable(c)) {
		return IDENTIFIER;
	}

	// if none matched, return -1 (error identifier)
	return -1;
}

// >= .. <= <>
// TODO:
// - testing
void parse() {
	char file_name[50];

	do {
		printf("Enter load file name:\n");
		scanf("%s", file_name);
		FIN = fopen(file_name, "r");
		int input;
        if (access(file_name, F_OK) == -1) {
			printf("File \"%s\" doesn't exist. Choose command: \n\n", file_name);
			printf("1. Enter another file name\n");
			printf("2. Exit\n");
	        scanf("%d", &input);

	        switch (input) {
	            case 1  : break;
	            default : exit(0);
	        }
        }
	} while(access( file_name, F_OK ) == -1 );

	resultX.size = 0;
	result.size = 0;

	boolean first = true;
	CC = getc(FIN);

	cur_line = 1;
	cur_col = 1;

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

		result.arr[result.size][0] = '\0';

		resultX.arr[resultX.size].line = cur_line;
		resultX.arr[resultX.size].col = cur_col;

		// printf(">>> %d >>> %d ", cur_line, cur_col);
		if (CC == '-') {
			result.arr[result.size][0] = CC;
			CC = getc(FIN);
			if (IsAlphaNumerical(CC)) {
				if (IsAlphabet(CC)) {
					for (int i = 1; IsAlphaNumerical(CC) && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
						result.arr[result.size][i] = CC;
						CC = getc(FIN);
						if (!IsAlphaNumerical(CC) || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
							result.arr[result.size][i+1] = '\0';
							noread = true;
						}
					}
				} else {
					for (int i = 1; (IsAlphaNumerical(CC) || CC == '.') && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
						result.arr[result.size][i] = CC;
						char prev_char = CC;
						CC = getc(FIN);
						if ((!IsAlphaNumerical(CC) && CC != '.') || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
							result.arr[result.size][i+1] = '\0';
							noread = true;
						}
						if (prev_char == '.' && CC == '.') {
							result.arr[result.size][i] ='\0';
							resultX.arr[resultX.size].val = GetEnumValueFromTerminalString(result.arr[result.size]);
							// printf(">>> %s >> enum = %d\n", result.arr[result.size], resultX.arr[resultX.size].val);
							result.size++;
							resultX.size++;
							first = false;
							cur_col++;
							IgnoreBlank();
							result.arr[result.size][0] = '.';
							result.arr[result.size][1] = '.';
							result.arr[result.size][2] = '\0';
							break;
						}

					}
				}
			} else {
				result.arr[result.size][1] = '\0';
				noread = true;
			}
		} else if (IsAlphaNumerical(CC)) {
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
				for (int i = 0; (IsAlphaNumerical(CC) || CC == '.') && CC != EOF && CC != ' ' && CC != '\n' && CC != '\t'; i++) {
					result.arr[result.size][i] = CC;
					char prev_char = CC;
					CC = getc(FIN);
					if ((!IsAlphaNumerical(CC) && CC != '.') || CC == EOF || CC == ' ' || CC == '\n' || CC == '\t') {
						result.arr[result.size][i+1] = '\0';
						noread = true;
					}
					if (prev_char == '.' && CC == '.') {
						result.arr[result.size][i] ='\0';
						resultX.arr[resultX.size].val = GetEnumValueFromTerminalString(result.arr[result.size]);
						// printf(">>> %s >> enum = %d\n", result.arr[result.size], resultX.arr[resultX.size].val);
						result.size++;
						resultX.size++;
						first = false;
						cur_col++;
						IgnoreBlank();
						result.arr[result.size][0] = '.';
						result.arr[result.size][1] = '.';
						result.arr[result.size][2] = '\0';
						break;
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
				// printf("YEUU %c == %c, ", CC, result.arr[result.size][0]);
				CC = getc(FIN);
				if (CC == '=') {
					result.arr[result.size][1] = CC;
					// printf("%c == %c ", CC, result.arr[result.size][1]);
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

		resultX.arr[resultX.size].val = GetEnumValueFromTerminalString(result.arr[result.size]);

		// printf(">>> %s >> enum = %d\n", result.arr[result.size], resultX.arr[resultX.size].val);

		result.size++;
		resultX.size++;

		first = false;

		cur_col++;

		IgnoreBlank();
	}
	// printf("YEUUUUUUUUUUUU\n");
	// for (int i = 0; i < resultX.size; i++) {
	// 	char c[40];
	// 	TranslateEnumToString(c, resultX.arr[i].val);
	// 	printf("%s\n", c);
	// }
}

// int main() {
// 	// printf("%s\n", terminal[8]);
// 	parse();
//
// }
