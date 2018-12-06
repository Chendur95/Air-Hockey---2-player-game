#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "cannon_csenthil.h" 
void cannon_sketch(int csy)
{
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(50, 550 + csy);
	glVertex2i(60, 550 + csy);
	glVertex2i(60, 540 + csy);
	glVertex2i(50, 540 + csy);
	glEnd();
}

void cannonline_sketch(int a, int csy)
{
	const double YS_PI = 3.1415927;
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	double x, y, length;
	length = 30;
	double angle = a*YS_PI / 180;
	x = 55 + cos(angle)*length;
	y = 545 + csy - sin(angle)*length;
	glVertex2i(55, 545 + csy);
	glVertex2i(x, y);
	glEnd();
}

void target_sketch(int y)
{
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(750, y);
	glVertex2i(800, y);
	glVertex2i(800, y + 50);
	glVertex2i(750, y + 50);
	glEnd();
}

void obstacle_sketch(int x1, int y1, int x2, int y2)
{
	glColor3ub(0, 255, 0);
	glBegin(GL_QUADS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void obstacle_sketch2(int x1, int y1, int x2, int y2)
{
	glColor3ub(0, 255, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void target_move(int &y, int scrnSizeY)
{
	y += 2.5;
	if (y>scrnSizeY)
	{
		y = 0;
	}
}

void cannonball_sketch(int cx, int cy)
{
	const double YS_PI = 3.1415927;
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	int i;
	for (i = 0; i<64; i++)
	{
		double angle = (double)i*YS_PI / 32.0;
		double x = (double)cx + cos(angle) * 5;
		double y = (double)cy + sin(angle) * 5;
		glVertex2d(x, y);
	}
	glEnd();
}


void ball_move(int &x, int &y, double &vx, double &vy, double m, double dt)
{
	double fx, fy, ax, ay;
	x = x + vx*dt;
	y = y + vy*dt;
	fx = 0.0;
	fy = m * 98;
	ax = fx / m;
	ay = fy / m;
	vx = vx + dt*ax;
	vy = vy + dt*ay;

}

int CheckCollision(int &cx, int &cy, int &x1, int &y1, int &x2, int &y2)
{
	int rx1 = cx - x1;
	int rx2 = cx - x2;
	int ry1 = cy - y1;
	int ry2 = cy - y2;
	if (0 >= (rx1*rx2) && 0 >= (ry1*ry2))
	{
		return 1;
	}
	return 0;
}

int CheckHit(int &cx, int &cy, int &y)
{
	int rx = cx - 750;
	int ry = cy - y;
	if (0 <= rx && 50 >= rx && 0 <= ry && 50 >= ry)
	{
		return 1;
	}
	return 0;
}