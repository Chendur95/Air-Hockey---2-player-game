#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Line2D_csenthil.h"
#include "Drawing2D_csenthil.h"

using namespace std; 

struct graphicParams {
	double scale;
	double transX;
	double transY;
};

void adjustZoom(double locX, double locY, double newScaleFactor, graphicParams &g)
{
	// reset panX and panY such that the graphics just under the mouse pointer don't move
	// essentially, back-calculate the true coords then adjust transX and transY so that
	// point under mouse does not change screen coords.

	double newScale = g.scale * newScaleFactor; 
	g.transX = (int)round((locX * (g.scale - newScale)
		+ g.transX * newScale) / g.scale);
	g.transY = (int)round((locY * (g.scale - newScale)
		+ g.transY * newScale) / g.scale);
	g.scale = newScale;
}

int main()
{
	bool term = false;
	printf("Enter File Name>");
	char name[256];
	fgets(name, 255, stdin);
	if (name[strlen(name) - 1] == '\n')
	{
		name[strlen(name) - 1] = '\0';
	}

	graphicParams gWindow;  // will hold the scale and panning
	gWindow.scale = 1.;
	gWindow.transX = 0.;
	gWindow.transY = 0.;
	Drawing2D Drawing;

	int startx = 0;
	int starty = 0;
	int movex = 0;
	int movey = 0;
	int xlast = 0;
	int ylast = 0;
	FsOpenWindow(0, 0, 800, 600, 1);
	while (true != term)
	{
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto key = FsInkey();
		if (key == FSKEY_ESC)
		{
			term = true;
		}
		for (int i = 0; i <= strlen(name); i++)
		{
			Drawing.filename[i] = name[i];
		}
		int lb, mb, rb, mx, my;
		int evt = FsGetMouseEvent(lb, mb, rb, mx, my);

		if (FSMOUSEEVENT_LBUTTONDOWN == evt)
		{
			startx = mx;
			starty = my;
			xlast = gWindow.transX;
			ylast = gWindow.transY;
		}
		if (lb == 1)
		{
			gWindow.transX = xlast + mx - startx;
			gWindow.transY = ylast + my - starty;
		}
		if (key == FSKEY_SPACE)
		{
			startx = 0;
			starty = 0;
			gWindow.transX = 0;
			gWindow.transY = 0;
		}
		Drawing.Draw(gWindow.transX, gWindow.transY);
		if (key == FSKEY_WHEELUP) //cout << "Detected wheel UP event" << endl;
		{
			adjustZoom(mx, my, 1.1, gWindow);
		}
		if (key == FSKEY_WHEELDOWN) //cout << "Detected wheel DOWN event" << endl;
		{
			adjustZoom(mx, my, 1. / 1.1, gWindow);
		}
		FsSwapBuffers();
		FsSleep(25);
	}
}