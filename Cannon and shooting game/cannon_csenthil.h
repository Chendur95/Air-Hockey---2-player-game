#pragma once
void cannon_sketch(int csy); 
void cannonline_sketch(int a, int csy); 
void target_sketch(int y); 
void obstacle_sketch(int x1, int y1, int x2, int y2); 
void obstacle_sketch2(int x1, int y1, int x2, int y2);
void target_move(int &y, int scrnSizeY); 
void cannonball_sketch(int cx, int cy);
void ball_move(int &x, int &y, double &vx, double &vy, double m, double dt); 
int CheckCollision(int &cx, int &cy, int &x1, int &y1, int &x2, int &y2); 
int CheckHit(int &cx, int &cy, int &y); 