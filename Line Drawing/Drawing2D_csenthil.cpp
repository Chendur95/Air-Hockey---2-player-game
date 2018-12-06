#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Line2D_csenthil.h"
#include "Drawing2D_csenthil.h"

Drawing2D& Drawing2D::operator= (const Drawing2D &Source)
{
	numoflines = Source.numoflines;
	line2D_ptr = Source.line2D_ptr;
	return *this;
}

void Drawing2D::Draw(int movex, int movey)
{
	ReadFile(filename);
	for (int i = 0; i<numoflines; i++)
	{
		line2D_ptr[i].Draw(movex, movey);
	}
}

Drawing2D::Drawing2D()
{
	numoflines = NULL;
}

Drawing2D::~Drawing2D()
{
	cleanup();
}

void Drawing2D::cleanup()
{
	if (line2D_ptr != nullptr)
	{
		delete[] line2D_ptr;
	}
}

void Drawing2D::ReadFile(char filename[256])
{
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp != nullptr)
	{
		char str[256];
		numoflines = atoi(fgets(str, 255, fp));
		line2D_ptr = new Line2D[numoflines];

		for (int i = 0; fgets(str, 255, fp) != nullptr; i++)
		{
			line2D_ptr[i].MakeFromString(str);
		}
	}
	fclose(fp);
}