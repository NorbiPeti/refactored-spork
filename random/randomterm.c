#include <stdio.h>
//#include "terminal-grafika.h"
//#include <stdlib.h>
//#include <time.h>
#include "1x.h"

int main() {
	//srand(time(NULL));
	//printf("\033[%d;%dH", rand()%24 + 1, rand()%80 + 1);
	printf("\033[%d;%dH", crshrand()%24 + 1, crshrand()%80 + 1);
	return 0;
}

