#ifndef PARSER_H_
#define PARSER_H_

typedef struct tTerminalElmt {
	int val;
	int line;
	int col;
} TerminalElmt;

typedef struct tTerminalArray {
	TerminalElmt arr[500];
	int size;
} TerminalArray;

extern TerminalArray resultX;

void parse();

#endif
