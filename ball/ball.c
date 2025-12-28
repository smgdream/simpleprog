#include "ball.h"

int ball_set_force(Ball *this, double x, double y)
{
	// NULL?
	this->force.x = x;
	this->force.y = y;

	return 1;
}

int ball_set_vel(Ball *this, double x, double y)
{	
	// NULL?
	this->vel.x += x;
	this->vel.y += y;
	
	return 1;
}

int ball_update(Ball *this, double dt)
{
	// NULL ?
	this->update_accel(this);
	this->update_vel(this, dt);
	this->update_pos(this, dt);

	return 1;
}

int ball_update_accel(Ball *this)
{
	// NULL?
	this->accel.x = this->force.x / this->mass;
	this->accel.y = this->force.y / this->mass;

	return 1;
}

int ball_update_vel(Ball *this, double dt)
{
	// NULL?
	this->vel.x += this->accel.x * dt;
	this->vel.y += this->accel.y * dt;

	return 1;
}

int ball_update_pos(Ball *this, double dt)
{
	// NULL?
	this->pos.x += this->vel.x * dt;
	this->pos.y += this->vel.y * dt;

	return 1;
}


