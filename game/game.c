#include <stdio.h>
#include <stdbool.h>
#include "getch.h"

typedef struct { int x, y; } player_t;

bool player_move(player_t *p, char dir);

int main() {
	//printf("Key: %d", getchar());
	for(int i=0; i<20; i++) {
		for(int j=0; j<20; j++) {
			printf(".");
		}
		printf("\n");
	}
	char input;
	player_t player = { 10, 10 };
	do {
		input = getch(); //Don't wait for Enter key
		player_move(&player, input);
	} while(input!=10);
	return 0;
}

bool player_move(player_t *p, char dir) {
	printf("\033[%d;%dH.", p->y, p->x);
	switch(dir) {
		case 'W':
		case 'w':
			p->y--;
			break;
		case 'A':
		case 'a':
			p->x--;
			break;
		case 'S':
		case 's':
			p->y++;
			break;
		case 'D':
		case 'd':
			p->x++;
			break;
		default:
			return false;
	}
	printf("\033[%d;%dHX", p->y, p->x);
	//printf("%d, %d", p->y, p->x);
	return true;
}

