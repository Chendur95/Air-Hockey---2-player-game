#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "ps05_csenthil.h"

struct playerPosition
{
	int pLeft;
	int pRight; 
	int pointsR;
	int pointsL; 
}playerPos;

struct discPos
{
	int X;
	int Y; 
	bool state; 
	double angle; 
	int vel_x; 
	int vel_y; 
}disc;

int main()
{
	int terminate = 0;
	FsOpenWindow(16, 16, 800, 600, 1);
	srand((unsigned)time(NULL));
	int dt = 1; 
	playerPos.pLeft = 265;
	playerPos.pRight = 265;

	int goalPos_Y = 200; 
	int goalPos_X_right = 783;
	int goalPos_X_left = 10; 

	int goal;  
	playerPos.pointsR = 0; 
	playerPos.pointsL = 0;

	disc.X = 400; 
	disc.Y = 300; 
	disc.state = 0;
	disc.angle = 0;
	disc.vel_x = 0;
	disc.vel_y = 0;

	int itnum = 0;
	int xposval[100000] = {0};
	while (terminate==0)
	{
		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key)
		{
			terminate = 1;
		}
		if (FSKEY_W == key)
		{
			playerPos.pLeft = playerPos.pLeft - 5; 
			if (playerPos.pLeft <= 10) playerPos.pLeft = 10;
		}
		if (FSKEY_S == key)
		{
			playerPos.pLeft = playerPos.pLeft + 5;
			if (playerPos.pLeft >= 520) playerPos.pLeft = 520;
		}
		if (FSKEY_UP == key)
		{
			playerPos.pRight = playerPos.pRight - 5;
			if (playerPos.pRight <= 10) playerPos.pRight = 10;
		}
		if (FSKEY_DOWN == key)
		{
			playerPos.pRight = playerPos.pRight + 5;
			if (playerPos.pRight >= 520) playerPos.pRight = 520; 
		}
		if (FSKEY_SPACE == key && disc.state == 0)    //When disc hits goal disc.state becomes 0
		{
			disc.X = 400;
			disc.Y = 300;
			disc.state = 1; 
			disc.angle = Disc_Launch_Angle(); 
			disc.vel_x = 5; 
			disc.vel_y = 5; 
		}
		
		if (disc.state == 1)
		{
			Disc_Physics(disc.X, disc.Y, disc.vel_x, disc.vel_y, disc.angle, dt);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		xposval[itnum] = disc.X; 
		check_goal(disc.X, disc.Y, disc.state, playerPos.pointsR, playerPos.pointsL); 
		display_msgs(); 

		goalDisplay_Left(playerPos.pointsL);
		goalDisplay_Right(playerPos.pointsR);
		draw_PlayerR(playerPos.pRight);
		draw_PlayerL(playerPos.pLeft);
		draw_DiscBall(disc.X, disc.Y); 
		draw_Table(); 
		goals_sketch(goalPos_X_left, goalPos_Y);
		goals_sketch(goalPos_X_right, goalPos_Y);
		check_table_collision(disc.X, disc.Y, disc.vel_x, disc.vel_y);

		if(itnum>0) check_playerHit(disc.X, disc.Y, disc.vel_x, playerPos.pLeft, playerPos.pRight, itnum, xposval); 
		itnum++; 
		FsSwapBuffers();
		FsSleep(25);
	}	
	return 0; 
}