#pragma once
void draw_Table(); 
void goals_sketch(int x, int y); 
void draw_DiscBall(int x, int y); 
void draw_PlayerL(int y);
void draw_PlayerR(int y);
double Disc_Launch_Angle(); 
void Disc_Physics(int &x, int &y, int &vx, int &vy, double angle, double dt); 
void check_goal(int &x, int &y, bool &state, int &goalsR, int &goalsL); 
void check_table_collision(int &x, int &y, int &vx, int &vy);
void check_playerHit(int x, int y, int &velx, int yPosLeft, int yPosRight, int &itnum, int xvals[100000]);
void display_msgs();
void goalDisplay_Left(int num); 
void goalDisplay_Right(int num); 