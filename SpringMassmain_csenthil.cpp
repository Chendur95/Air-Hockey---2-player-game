#include <stdio.h>
#include <iostream>
#include <math.h>
#include "fssimplewindow.h"
#include "SpringMass_csenthil.h"
using namespace std;

int main(void)
{
	Spring obj; 
	double initLength, height;		  // user-inputted parameters

	double compressedLength;		  // will be set to 25% of fullLength
	double lengthFactor, currLength;  // used for animation
	int cycleCounter;				  // used for animation
	double currRot = 0., currScale = 100.;		  // used to control visualization

	bool inAnimationMode = false;
	bool continueProgram = true;
	bool thereWasInput = true;
	int key;

	// get user input and provide instructions
	cout << "24 - 780 Engineering Computation Problem Set 3 - 2 – Mass - Spring System" << endl;
	cout << endl << "This program will draw a spring mass system. " << endl;
	cout << "    L is the spring position to start from and h is the height of the mass." << endl;
	cout << "    Use space bar to start/stop animation." << endl;
	cout << "    Use ESC key to exit program." << endl << endl;
	cout << "Enter L and h: ";
	cin >> initLength >> height;

	// initialize 
	obj.setparams(initLength, height);
	double dt; 
	FsOpenWindow(16, 16, 800, 600, 1);

	while (continueProgram) {
		obj.simulate(inAnimationMode); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj.drawWall(1., 3 * height);
		obj.drawMass(height);
		obj.drawSpring(height);
		FsSwapBuffers();

		FsPollDevice();
		switch (FsInkey()) {
		case FSKEY_SPACE: inAnimationMode = !inAnimationMode;
			break;
		case FSKEY_ESC: continueProgram = false;
			break;
		}
		FsSleep(10);
	}

	FsPollDevice();
	while (FSKEY_NULL == FsInkey())
	{
		FsPollDevice();
		FsSleep(25);
	}
}