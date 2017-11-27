#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

#include "customstring.h"
#include "cnf.h"
#include "cyk.h"

void clearscr() {

    #ifdef _WIN32
        system("cls");
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        system("clear");
    #else
        #error "OS not supported."
    #endif

}

int main() {
	clearscr();
	readCNF();
	parse();
	int input;
	printf("Input program is: \n");
	SolveCYK(prodVar, prodTerminal, resultX);
	printf("Print table?: \n");
	printf("1. Print \n");
	printf("2. Exit \n");
	printf(">>> ");
	scanf("%d", &input);

	if(input == 1) {
		SolveCYKPrint(prodVar, prodTerminal, resultX);
	}
	else {
		exit(0);
	}

	return 0;

}
