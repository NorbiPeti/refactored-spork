#include <stdio.h>
#include "terminal-grafika.h"
#include <stdlib.h>
#include <time.h>

int main() { //gcc -lm -Wall -o randomterm terminal-grafika.c randomterm.c
	srand(time(NULL));
	screen_t scr = new_screen(0, 20, 0, 20);
	for(int i=0; i<20; i++)
		screen_move_xy(scr, rand()%20, rand()%20);
	return 0;
}

