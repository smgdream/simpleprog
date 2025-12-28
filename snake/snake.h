#ifndef SNAKE_H
#define SNAKE_H

typedef struct point_tag {
	int x, y;
} Point;

typedef struct snake_tag {
	Point head;
	Point tail;
	int ori; // orientation
} Snake;

typedef struct node_tag {
	Point pt;
	struct node_tag *next;
} Node;

void new_food(char *scene);
int mapper(char *scene);
int snake_mov(Snake *snk, char *scene);
int init(char *scene, Snake *snk);

int push(Point pt);
Point pop(void);

int kbhit(void);
int getch(void);

#endif
