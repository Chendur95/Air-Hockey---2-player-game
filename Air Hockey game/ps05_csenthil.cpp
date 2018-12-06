#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "ps05_csenthil.h"

void draw_Table()
{
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex2d(10, 10);
	glVertex2d(790, 10);
	glVertex2d(790, 10);
	glVertex2d(790, 590);
	glVertex2d(790, 590);
	glVertex2d(10, 590);
	glVertex2d(10, 590);
	glVertex2d(10, 10);
	glVertex2d(400, 10);
	glVertex2d(400, 590);
	glEnd();
}

void goals_sketch(int x, int y)    //y = 200 and x = 783 for right, 10 for left
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);
	glVertex2i(x + 7, y);
	glColor3ub(0, 125, 0);
	glVertex2i(x, y);
	glColor3ub(0, 125, 0);
	glVertex2i(x, y + 200);
	glColor3ub(0, 0, 255);
	glVertex2i(x + 7, y + 200);
	glEnd();
}
void draw_DiscBall(int cx, int cy)
{
	const double PI = 3.1415927;
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	int i;
	for (i = 0; i<128; i++)
	{
		double angle = (double)i*PI / 64.0;
		double x = (double)cx + cos(angle) * 8;
		double y = (double)cy + sin(angle) * 8;
		glColor3ub(i, 255 - i, 0);
		glVertex2d(x, y);
	}
	glEnd();
}
void draw_PlayerL(int y)
{
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(55, y);
	glVertex2i(48, y);
	glVertex2i(48, y + 70);
	glVertex2i(55, y + 70);
	glEnd();
}
void draw_PlayerR(int y)
{
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(752, y);
	glVertex2i(745, y);
	glVertex2i(745, y + 70);
	glVertex2i(752, y + 70);
	glEnd();
}

double Disc_Launch_Angle()
{
	const double PI = 3.1415927;
	double t = rand() % 360; 
	while ((t > 80 && t < 100) || (t>170 && t<190)) t = rand() % 360; 
	double angle = (double)(t)*PI / 180;
	return angle;
}

void Disc_Physics(int &x, int &y, int &vx, int &vy, double angle, double dt)
{
	x = (int)x + (int)((int)vx*(double)cos(angle)*(int)dt);
	y = (int)y + (int)((int)vy*(double)sin(angle)*(int)dt);
}

void check_goal(int &x, int &y, bool &state, int &goalsR, int &goalsL)
{
	int goal;
	if (y >= 200 && y <= 400 && x >= 780 && x <= 790)
	{
		goal = 2;
		state = 0;
		x = 400;
		y = 300;
		goalsL++;
	}
	if (y >= 200 && y <= 400 && x >= 10 && x <= 20)
	{
		goal = 1;
		state = 0;
		x = 400;
		y = 300;
		goalsR++;
	}
}

void check_table_collision(int &x, int &y, int &vx, int &vy)
{
	if (x > 780)
	{
		x = 780;
		vx = -vx;
	}
	if (x < 20)
	{
		x = 20;
		vx = -vx;
	}
	if (y > 580)
	{
		y = 580;
		vy = -vy;
	}
	if (y < 20)
	{
		y = 20;
		vy = -vy;
	}
}

void check_playerHit(int x, int y, int &velx, int yPosLeft, int yPosRight, int &itnum, int xvals[100000])
{
	if (y > yPosRight && y < (yPosRight + 70) && (x >= 745) && (x <= 752) && (xvals[itnum - 1] <= 745))
	{
		x = 744;
		velx = -velx;
	}
	if (y > yPosRight && y < (yPosRight + 70) && (x >= 745) && (x <= 752) && (xvals[itnum - 1] >= 752))
	{
		x = 753;
		velx = -velx;
	}
	if ((y > yPosLeft) && y < (yPosLeft + 70) && (x >= 48) && (x <= 55) && (xvals[itnum - 1] >= 55))
	{
		x = 56;
		velx = -velx;
	}
	if ((y > yPosLeft) && y < (yPosLeft + 70) && (x >= 48) && (x <= 55) && (xvals[itnum - 1] <= 48))
	{
		x = 47;
		velx = -velx;
	}
}

void display_msgs()
{
	glColor3ub(255, 0, 0);
	glRasterPos2i(300, 50);  // sets position
	YsGlDrawFontBitmap16x24("AIR HOCKEY GAME");
	glColor3ub(0, 0, 255);
	glRasterPos2i(170, 560);  // sets position
	YsGlDrawFontBitmap12x16("Hit SPACE to launch the disc from center");
	glColor3ub(255, 80, 155);
	glRasterPos2i(150, 80);  // sets position
	YsGlDrawFontBitmap16x20("TEAM A");
	glColor3ub(255, 80, 155);
	glRasterPos2i(550, 80);  // sets position
	YsGlDrawFontBitmap16x20("TEAM B");
	glColor3ub(0, 0, 255);
	glRasterPos2i(391, 315);  // sets position
	YsGlDrawFontBitmap20x32("O");
}

void goalDisplay_Left(int num)
{
	glColor3ub(255, 0, 0);
	glRasterPos2i(150, 530);  // sets position
	if (num == 0)
	{
		YsGlDrawFontBitmap16x20("GOALS - 0");
	}
	if (num == 1)
	{
		YsGlDrawFontBitmap16x20("GOALS - 1");
	}
	if (num == 2)
	{
		YsGlDrawFontBitmap16x20("GOALS - 2");
	}
	if (num == 3)
	{
		YsGlDrawFontBitmap16x24("Team A won!!!");
	}
}

void goalDisplay_Right(int num)
{
	glColor3ub(255, 0, 0);
	glRasterPos2i(550, 530);  // sets position
	if (num == 0)
	{
		YsGlDrawFontBitmap16x20("GOALS - 0");
	}
	if (num == 1)
	{
		YsGlDrawFontBitmap16x20("GOALS - 1");
	}
	if (num == 2)
	{
		YsGlDrawFontBitmap16x20("GOALS - 2");
	}
	if (num == 3)
	{
		YsGlDrawFontBitmap16x24("Team B Won!!!");
	}
}