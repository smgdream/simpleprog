#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include <stdint.h>


typedef struct vector_2d_tag {
	double x;
	double y;
} Vector_2d;

typedef struct ball_tag Ball;
typedef struct ball_tag {
	/* data */
	int coll;
	double mass;
	Vector_2d pos;
	Vector_2d vel;
	Vector_2d accel;
	Vector_2d force;
	/* function */
	int (*set_force)(Ball *this, double x, double y);
	int (*set_vel)(Ball*this, double x, double y);
	int (*update_accel)(Ball *this);
	int (*update_vel)(Ball *this, double dt);
	int (*update_pos)(Ball *this, double dt);
} Ball;

int ball_set_force(Ball *this, double x, double y);
int ball_set_vel(Ball *this, double x, double y);
int ball_update_accel(Ball *this);
int ball_update_vel(Ball *this, double dt);
int ball_update_pos(Ball *this, double dt);


/* new a Ball. return the pointer to Ball */
static inline Ball *ball_new(void)
{
	return (Ball *) malloc(sizeof(Ball));
}

/* ball_init - onstructor of Ball. set the arguments we need.
 * return the value of ptr
 */
static inline Ball *ball_init(Ball *ptr, double mass,
							 double force_x, double force_y,
							 double vel_x, double vel_y,
	 						 double pos_x, double pos_y)
{
	// NULL?
	ptr->coll = 0;
	ptr->mass = mass;
	ptr->force.x = force_x;
	ptr->force.y = force_y;
	ptr->accel.x = 0.0;
	ptr->accel.y = 0.0;
	ptr->vel.x = vel_x;
	ptr->vel.y = vel_y;
	ptr->pos.x = pos_x;
	ptr->pos.y = pos_y;
	ptr->set_force = ball_set_force;
	ptr->set_vel = ball_set_vel;
	ptr->update_accel = ball_update_accel;
	ptr->update_vel = ball_update_vel;
	ptr->update_pos = ball_update_pos;

	return ptr;
}



#endif