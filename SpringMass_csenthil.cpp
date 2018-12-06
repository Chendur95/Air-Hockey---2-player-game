#include <stdio.h>
#include <iostream>
#include <math.h>
#include "fssimplewindow.h"
#include "SpringMass_csenthil.h"

intCoords Spring::getScreenCoords(double modelX, double modelY)
{ // rotation is given in degrees, cartesian coords

	intCoords screenCoords;
	double scale = 100.0;
	int xOrigin = 100;
	int yOrigin = 300;
	screenCoords.x = modelX * scale + xOrigin;
	screenCoords.y = modelY * -scale + yOrigin;
	return screenCoords;
}

void Spring::screenVertex(double modelX, double modelY) 
{
	intCoords screenCoords = getScreenCoords(modelX, modelY);
	glVertex2i(screenCoords.x, screenCoords.y);
}

void Spring::drawWall(double locationX, double height)
{
	double diagLineSpacing = .2;
	double hatchWidth = .05;
	double scale = 10;
	double lineWidth = 4. * scale / 100.;

	glColor3f(1.0, 0.0, 0.0); // red

								  // draw the vertical line
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	screenVertex(0., -height / 2);
	screenVertex(0., height / 2);
	glEnd();

	// draw the hatch lines
	glLineWidth(lineWidth / 2.);
	glBegin(GL_LINES);
	for (int i = 1; i <= height / diagLineSpacing; i++) {
		screenVertex(0., -height / 2 + i * diagLineSpacing);
		screenVertex(-diagLineSpacing, -height / 2 + (i - 1)*diagLineSpacing);
	}
	glEnd();
}

void Spring::drawMass(double height)   //Location X is current length 
{
	double chamferRatio = 0.1;
	double height1 = height / 2;
	double height2 = height * (0.5 - chamferRatio);
	double x1 = currLength;
	double x2 = currLength + height * chamferRatio;
	double x3 = currLength + height * (1. - chamferRatio);
	double x4 = currLength + height;

	glColor3f(0.4, 0.4, 0.4); // gray
	glBegin(GL_POLYGON);   // mass will be filled in

	screenVertex(x2, height1);
	screenVertex(x3, height1);
	screenVertex(x4, height2);
	screenVertex(x4, -height2);
	screenVertex(x3, -height1);
	screenVertex(x2, -height1);
	screenVertex(x1, -height2);
	screenVertex(x1, height2);
	glEnd();
}

void Spring::drawSpring(double height)       //Length is currLength
{
	int numbOfCoils = 3;
	double coilSpacing = currLength / (numbOfCoils * 6);
	double currX;  // used to increment the x-coordinate

	glColor3f(0.0, 0.0, 1.0); // blue
	glBegin(GL_LINE_STRIP);
	screenVertex(0, 0);
	screenVertex(currLength / 3., 0);
	currX = currLength / 3. - coilSpacing / 2.;
	for (int i = 0; i < numbOfCoils; i++) {
		currX += coilSpacing;
		screenVertex(currX, -height / 2.);
		currX += coilSpacing;
		screenVertex(currX, height / 2.);
	}
	currX += coilSpacing / 2.;
	screenVertex(currX, 0.);
	screenVertex(currLength, 0.);
	glEnd();
}

void Spring::setparams(double leng, double heigh)
{
	initLength = leng;
	height = heigh;
	k = 1;   //spring constant
	m = 1;   //Mass 
	natLength = 3;
	currLength = leng;
	vel = 0;
	t2 = 0;
	t1 = 0;
}

void Spring::simulate(bool inAnimationMode)
{
	t1 = FsPassedTime();     // Time before the loop to find dt
	if (inAnimationMode) {  // adjust currLength only if in animation mode
		dt = (t1 - t2) / 1000;
		acc = -k*(currLength - natLength) / m;
		vel = acc*dt + vel;
		currLength = vel*dt + currLength;
	}
	t2 = FsPassedTime();      //Time after the loop to find dt 
}