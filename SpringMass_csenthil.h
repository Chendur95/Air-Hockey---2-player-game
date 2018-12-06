#pragma once

#define PI_NG 3.141592653589793

struct intCoords {
	int x;
	int y;
};

class Spring
{
private:
	double initLength;
	double height;
	double k;   //spring constant
	double m;   //Mass 
	double natLength;
	double currLength;
	double acc;
	double vel;
	double t2;
	double t1;
	double dt;
public:

	intCoords getScreenCoords(double modelX, double modelY);
	void screenVertex(double modelX, double modelY);
	void drawWall(double locationX, double height);
	void drawMass(double height);   //Location X is current length 
	void drawSpring(double height);       //Length is currLength
	void setparams(double leng, double heigh);
	void simulate(bool inAnimationMode);
};