#include <stdlib.h>
#include "snake.h"

static Node *tail_nod = NULL; // head

int push(Point pt)
{
	static Node *prev_nod = NULL; // tail
	Node *nod = (Node *)malloc(sizeof(Node));

	if (nod == NULL)
		return 0;
	nod->next = NULL;
	nod->pt = pt;

	if (prev_nod == NULL)
		tail_nod = nod;
	else
		prev_nod->next = nod;
	prev_nod = nod;

	return 1;
}

Point pop(void)
{
	Point pt;
	Node *next = NULL;

	if (tail_nod == NULL) /* Error */
		exit(1); 
	pt = tail_nod->pt;

	next = tail_nod->next;
	free(tail_nod);
	tail_nod = next;

	return pt;
}
