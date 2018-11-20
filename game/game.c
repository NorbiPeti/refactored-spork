#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "getch.h"

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define SIZE_X 80
#define SIZE_Y 24
#define ENEMY_COUNT 100

typedef struct { int x, y; char pchar; } player_t;

bool player_move(player_t *p, char dir);
void spawn_enemies();
player_t *player_at(int x, int y);
void end();
void move_enemies();

player_t *own;
player_t enemies[ENEMY_COUNT];
bool running=true;

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
	player_t p = { SIZE_X/2, SIZE_Y/2+1, 'X' };
	own=&p;
	spawn_enemies();
	player_move(own, 'W'); //Render player
	do {
		input = getch(); //Don't wait for Enter key
		move_enemies(); //Move on each keypress
		if(player_move(own, input)) continue;
		//if(sp(&own, input)) continue;
	} while(input!=10 && running); //Enter
	printf("\033["STRINGIFY(SIZE_Y)";0H\n"); //Reset prompt location
	return 0;
}

void print_char(player_t *p, char c) {
	printf("\033[%d;%dH%c\033[%d;%dH", p->y, p->x, c, p->y, p->x);
}

bool player_move(player_t *p, char dir) {
	int x=p->x,y=p->y;
	switch(dir) {
		case 'W':
		case 'w':
			if(p->y<=1) return true;
			y--;
			break;
		case 'A':
		case 'a':
			if(p->x<=1) return true;
			x--;
			break;
		case 'S':
		case 's':
			if(p->y>=SIZE_Y) return true;
			y++;
			break;
		case 'D':
		case 'd':
			if(p->x>=SIZE_X) return true;
			x++;
			break;
		default:
			return false;
	}
	/*if(p->o) p->o=false;
	else print_char(p, '.');*/
	player_t *e=player_at(x, y);
	if(e && own==p) end();
	print_char(p, '.');
	p->x=x,p->y=y;
	print_char(p, p->pchar);
	return true;
}

/*bool sp(player_t *p, char but) {
	if(but!=' ') return false;
	print_char(p, 'O');
	p->o=true;
	return true;
}*/

player_t *player_at(int x, int y) {
	if(own->x==x&&own->y==y) return own;
	for(int i=0; i<ENEMY_COUNT; i++) {
		if(enemies[i].x==x&&enemies[i].y==y) return &enemies[i];
	}
	return NULL;
}

player_t get_enemy() {
	player_t p;
	while(player_at(p.x=rand()%SIZE_X, p.y=rand()%SIZE_Y)); //Find empty spot
	p.pchar='E';
	return p;
}

void spawn_enemies() {
	for(int i=0; i<ENEMY_COUNT; i++) {
		enemies[i]=get_enemy();
		print_char(&enemies[i], enemies[i].pchar);
	}
}

void end() {
	running=false;
}

void move_enemies() {
	char dir[] = { 'W', 'A', 'S', 'D' };
	for(int i=0; i<ENEMY_COUNT; i++) {
		player_move(&enemies[i], dir[rand()%4]);
	}
}

