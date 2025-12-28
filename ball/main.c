#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "ball.h"

#define PHYT_ERR (10)	// Error of physical calculation
#define RENT_ERR (100)	// Error of render
#define GA (9.8)		// Gravitational acceleration
#define FPS 24

#define S(us) ((us)/1000000.0)			// us to s
#define cycle(freq) ((uint32_t)( 1000000 / (freq) ))	// Time of a cycle
#define is_time2(dt, intvl, err) (((intvl)-(err) <= (dt)%(intvl) && (dt)%(intvl) <= (intvl)+(err)))

typedef uint64_t us_t;


void draw(Ball *ptr);
double vy(Ball *ba, double t);

int main(int argc, char **argv)
{
	us_t rtime = 0;
	us_t phy_last = 0, ren_last = 0;
	Ball *ba = ball_init(ball_new(), 1, 0, -GA, 0, 0, 0, 20);

	ba->set_vel(ba, (argc > 1) ? atof(argv[1]) : 2.0, 0);

	for (;;) {
		rtime = clock() * (1000000 / CLOCKS_PER_SEC);
		
		// phy cal
		if (is_time2(rtime - phy_last, cycle(6000), PHYT_ERR)) {
			double dt = S(rtime - phy_last);
			ba->update_accel(ba);
			ba->update_vel(ba, dt);
			ba->set_vel(ba, 0, vy(ba, dt));
			ba->update_pos(ba, dt);
			phy_last = rtime;
		}
		// render
		if (is_time2(rtime - ren_last, cycle(FPS), RENT_ERR)) {
			draw(ba);
			ren_last = rtime;
		}
	}

	return 0;
}

#define outpos(x, y, wid) ((int)(x) + (int)(y) * (wid))

void draw(Ball *ptr)
{
	
	static Vector_2d o_pos = {0.0, 0.0};
	static char *out = NULL;

	if (out == NULL) {
		out = (char *)malloc(sizeof(char) * (83 * 21 + 1));

		for (int i = 0; i < 83*21-1; ++i)
				out[i] = ' ';

		for (int i = 0; i <= 21; ++i)
			out[outpos(82, i, 83)] = '\n';
			
	}

	out[outpos(o_pos.x*2, o_pos.y, 83)] = ' ';
	out[outpos(o_pos.x*2+1, o_pos.y, 83)] = ' ';
	
	o_pos.x = ptr->pos.x;
	o_pos.y = 21 - ptr->pos.y;
	
	
	
	out[outpos(o_pos.x*2, o_pos.y, 83)] = '@';
	out[outpos(o_pos.x*2+1, o_pos.y, 83)] = '@';
	printf("\033c");
	printf("x: %f\ty: %f\n\n", ptr->pos.x, ptr->pos.y);
	fwrite(out, 83 * 21, 1, stdout);
	printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
	if ((int)ptr->pos.y <= 0)
		ptr->coll = 1;

	if (ptr->pos.x > 40) {
		free(out);
		free(ptr);
		exit(0);
	}

	return;
}

double vy(Ball *ba, double dt)
{
	if (ba->coll) {
		ba->coll = 0;
		return ba->vel.y * -2;
	}

	return 0.0;
}