#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "cannon_csenthil.h"

int main(void)
{
	const double YS_PI = 3.1415927;
	FsOpenWindow(16, 16, 800, 600, 1);
	int ObstaclesState[5];
	int x1[5], y1[5], x2[5], y2[5];
	srand((unsigned)time(NULL));

	for (int i = 0; i<5; ++i)
	{
		x1[i] = rand() % 720;
		y1[i] = rand() % 520;
		x2[i] = x1[i] + 80 + rand() % 70;
		y2[i] = y1[i] + 80 + rand() % 70;
		ObstaclesState[i] = 1;
	}

	int terminate = 0;
	int y = 0;
	int x = 30;
	int a = 55;
	int b = 545;

	double m = 1.0;
	double dt = 0.025;
	int CannonballState = 0;

	int angle = 30;
	double vx;
	double vy;

	int Hit = 0;
	int csy = 0;
	int TargetState = 1;

	while (0 == terminate)
	{
		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key)
		{
			terminate = 1;
		}
		else if (FSKEY_SPACE == key)
		{
			if (0 == CannonballState)
			{
				CannonballState = 1;
				vx = cos(angle*YS_PI / 180) * 400;
				vy = -sin(angle*YS_PI / 180) * 400;
			}
		}
		else if (FSKEY_LEFT == key)
		{
			angle++;
			if (angle >= 90) angle = 0;
		}
		else if (FSKEY_RIGHT == key)
		{
			angle--;
			if (angle <= 0) angle = 0;
		}
		else if (FSKEY_UP == key && CannonballState == 0)
		{
			csy = csy - 1; 
			b = b - 1; 
		}
		else if (FSKEY_DOWN == key && CannonballState == 0)
		{
			csy = csy + 1; 
			b = b + 1; 
		}
		//draw screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (0 != ObstaclesState)
		{
			for (int i = 0; i<5; ++i)
			{
				if (0 != ObstaclesState[i])
				{
					obstacle_sketch(x1[i], y1[i], x2[i], y2[i]);
					if (0 != CannonballState && 0 != CheckCollision(a, b, x1[i], y1[i], x2[i], y2[i]))
					{
						printf("Hit An Obstacle!\n");
						ObstaclesState[i] = 0;
						CannonballState = 0;
						Hit = 1;
						a = 55;
						b = 545+csy;
					}
				}
				if (0 != Hit)
				{
					obstacle_sketch2(x1[i], y1[i], x2[i], y2[i]);
				}
			}
		}
		if (0 != TargetState)
		{
			if (0 != CannonballState && 0 != CheckHit(a, b, y))
			{
				printf("HitTarget!\n");
				TargetState = 0;
				CannonballState = 0;
				break;
			}
		}
		cannonline_sketch(angle, csy);
		cannon_sketch(csy);
		target_sketch(y);
		target_move(y, 600);
		if (0 != CannonballState)
		{
			//b = 545 + csy; 
			cannonball_sketch(a, b);
			ball_move(a, b, vx, vy, m, dt);

			if (a>800 || b>600 || b<0 || a<0)
			{
				CannonballState = 0;
				a = 55;
				b = 545 + csy; 
			}
		}
		FsSwapBuffers();
		FsSleep(25);
	}
	return 0;
}