#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Line2D_csenthil.h"
#include "Drawing2D_csenthil.h"

void Line2D::Draw(int movex, int movey) const
{
	glColor3ub(R, G, B);
	glBegin(GL_LINES);
	glVertex2d(X1 + movex, Y1 + movey);
	glVertex2d(X2 + movex, Y2 + movey);
	glEnd();
}

void Line2D::MakeFromString(char str[256])
{
	int wordtop[7];
	int wordlength[7];
	Parse(wordtop, wordlength, 7, str);

	X1 += atoi(str + wordtop[0]);
	Y1 += 600 - atoi(str + wordtop[1]);
	X2 += atoi(str + wordtop[2]);
	Y2 += 600 - atoi(str + wordtop[3]);
	R = atoi(str + wordtop[4]);
	G = atoi(str + wordtop[5]);
	B = atoi(str + wordtop[6]);
}

int Line2D::Parse(int wordTop[], int wordLength[], int maxNumWord, char str[])
{
	int state = 0;  // 0:Blank   1:Visible Letter
	int nw = 0;
	for (int i = 0; 0 != str[i]; ++i)
	{
		switch (state)
		{
		case 0:
			if (' ' != str[i] && isprint(str[i]))
			{
				if (nw<maxNumWord)
				{
					wordTop[nw] = i;
					wordLength[nw] = 1;
				}
				else
				{
					goto LOOPOUT;
				}
				++nw;
				state = 1;
			}
			else
			{
			}
			break;
		case 1:
			if (' ' != str[i] && isprint(str[i]))
			{
				wordLength[nw - 1]++;
			}
			else
			{
				state = 0;
			}
			break;
		}
	}
LOOPOUT:

	return nw;
}

Line2D::Line2D()
{
	X1 = 0;
	X2 = 0;
	Y1 = 0;
	Y2 = 0;
	R = 0;
	G = 0;
	B = 0;
}
Line2D::~Line2D()
{
	X1 = NULL;
	X2 = NULL;
	Y1 = NULL;
	Y2 = NULL;
	R = NULL;
	G = NULL;
	B = NULL;
}