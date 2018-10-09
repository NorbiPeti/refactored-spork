#include <stdio.h>
//#include "terminal-grafika.h"
#include <stdlib.h>
#include <time.h>

int main() { //gcc -lm -Wall -o randomterm terminal-grafika.c randomterm.c
	srand(time(NULL));
	printf("\033[%d;%dH", rand()%24 + 1, rand()%80 + 1);
	return 0;
}

