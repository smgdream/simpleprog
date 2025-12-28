// Coding by smgdream
// Version: 0.1.5
// Mar 19 2024
// License: MIT LICENSE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#ifdef __unix__
	#include <unistd.h>
#else
	#include <windows.h>
	#include <conio.h>
#endif

#include "snake.h"

#define SIZE 30
#define pos(x, y) ((x) + (y) * SIZE)

#ifdef __unix__
	#define fps(n) usleep(1000000/n)
	#define clear() printf("\033c");
#else
	#define fps(n) Sleep(1000/n)
	#define clear() system("cls");
#endif


static int64_t get_time()
{
	time_t tp;
	return time(&tp);
}

int main()
{
	char scene[SIZE * SIZE];
	int act = 0;
	bool flag = 1;
	Snake *snk = malloc(sizeof(Snake));

	init(scene, snk);

	/* update */
	while (1) {
		/* get key */
		if (kbhit()) {
			act = getch();
			srand(act);
		}

		/* key process */
		if (act == 'e')
			break;
		if ((act == 'w' || act == 's' || act == 'a' || act == 'd')
			&& ((snk->ori == 'w' || snk->ori == 's') ? (act != 'w' && act != 's') : (act != 'a' && act != 'd'))
		) {
			snk->ori = act;
		}

		/* object update */
		flag = snake_mov(snk, scene);
		mapper(scene);
		if (flag == 0) {
			printf("GAME OVER!!!!!\n");
			break;
		}
		/* frame time ctl */
		fps(12);
	}
	return 0;
}

void new_food(char *scene)
{
	/* n_food: food counter */
	static int n_food = 0;
	int x, y;

	if (n_food != 0)
		--n_food;

	if (n_food < 5) {
		/* cnt: new food counter */
		int cnt = ((n_food > 2) ? (rand() % 7 == 6) : 1) + (rand() % 8 == 6);
		n_food += cnt;

		while (cnt) {
			x = rand()%SIZE;
			y = rand()%SIZE;
			if (scene[pos(x, y)] == 'n') { // It's noting on (x,y)
				scene[pos(x, y)] = 'f'; /* put food on the ground */
				--cnt;
			}
		}
	}
}

int snake_mov(Snake *snk, char *scene)
{	
	/* move to the next position */
	switch (snk->ori) {
	case 'w':
		snk->head.y += -1;
		break;
	case 's':
		snk->head.y += 1;
		break;
	case 'a':
		snk->head.x += -1;
		break;
	case 'd':
		snk->head.x += 1;
		break;
	}

	/* where is the snake go */
	switch (scene[pos(snk->head.x, snk->head.y)]) {
	case 'n':
		scene[pos(snk->head.x, snk->head.y)] = 's';
		push(snk->head);
		break;
	case 'f':
		scene[pos(snk->head.x, snk->head.y)] = 's';
		push(snk->head);
		new_food(scene);
		return 1;
		break;
	case 's':
		/* fall through */
	case 'w':
		return 0; /* game over */
		break;
	}
	scene[pos(snk->tail.x, snk->tail.y)] = 'n';
	snk->tail = pop();/* get the next tail */
	
	return 1;
}

int init(char *scene, Snake *snk)
{
	int ox, oy, ori;

	/* init seed */
	srand((uint32_t)get_time());

	/* init map */
	for (int y = 0; y < SIZE; ++y)
		for (int x = 0; x < SIZE; ++x)
			if (x == 0 || x == SIZE-1 || y == 0 || y == SIZE-1)
				scene[pos(x, y)] = 'w';
			else
				scene[pos(x, y)] = 'n';

	/* init something useful */
	ox = 6 + rand() % 10;
	oy = 6 + rand() % 10;
	snk->tail.x = ox;
	snk->tail.y = oy;
	ori = "asdw"[rand() % 4];
	snk->ori = ori;

	/* init snake's body */
	for (int cnt = 3; cnt; --cnt) {
		scene[pos(ox, oy)] = 's';
		snk->head.x = ox;
		snk->head.y = oy;
		push(snk->head);
		switch (ori) {
		case 'w':
			--oy;
			break;
		case 's':
			++oy;
			break;
		case 'a':
			--ox;
			break;
		case 'd':
			++ox;
			break;
		}
	}

	new_food(scene);
	pop(); /* pop the useless tail */
	return ori;
}

int mapper(char *scene)
{
	static char *buf = NULL;
	char *buf_ptr = NULL;
	if (buf == NULL)
		buf = (char *)malloc((SIZE*2+1)*SIZE);
	buf_ptr = buf;

	clear();
	for (int y = 0; y < SIZE; ++y) {
		for (int x = 0; x < SIZE; ++x) {
			switch (scene[pos(x, y)]) {
			case 's':
				sprintf(buf_ptr, "[]");
				break;
			case 'f':
				sprintf(buf_ptr, "FF");
				break;
			case 'w':
				sprintf(buf_ptr, "HH");
				break;
			case 'n':
				sprintf(buf_ptr,"  ");
				break;
			}
			buf_ptr += 2;
		}
		sprintf(buf_ptr, "\n");
		buf_ptr += 1;
	}
	fwrite(buf, (SIZE*2+1)*SIZE, 1, stdout);
	return 1;
}
