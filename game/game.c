#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "getch.h"

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define SIZE_X 80
#define SIZE_Y 24

typedef struct { int x, y; char prevc; } player_t;

bool player_move(player_t *p, char dir);
bool sp(player_t *p, char but);

int main() {
	printf("\033[0;0H");
	srand(time(NULL));
	for(int i=0; i<SIZE_Y; i++) {
		for(int j=0; j<SIZE_X; j++) {
			printf(".");
		}
		if(i+1!=SIZE_Y)
			printf("\n");
	}
	char input;
	player_t player = { 10, 10 };
	do {
		input = getch(); //Don't wait for Enter key
		if(player_move(&player, input)) continue;
		if(sp(&player, input)) continue;
	} while(input!=10); //Enter
	printf("\033["STRINGIFY(SIZE_Y)";0H\n"); //Reset prompt location
	return 0;
}

void print_char(player_t *p, char c) {
	printf("\033[%d;%dH%c\033[%d;%dH", p->y, p->x, c, p->y, p->x);
}

bool player_move(player_t *p, char dir) {
	print_char(p, '.');
	switch(dir) {
		case 'W':
		case 'w':
			if(p->y<=1) break;
			p->y--;
			break;
		case 'A':
		case 'a':
			if(p->x<=1) break;
			p->x--;
			break;
		case 'S':
		case 's':
			if(p->y>=SIZE_Y) break;
			p->y++;
			break;
		case 'D':
		case 'd':
			if(p->x>=SIZE_X) break;
			p->x++;
			break;
		default:
			return false;
	}
	print_char(p, 'X');
	return true;
}

bool sp(player_t *p, char but) {
	if(but!=' ') return false;
	print_char(p, 'O');
	return true;
}
