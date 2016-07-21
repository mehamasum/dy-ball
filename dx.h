#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <stdlib.h>
#include <time.h>
using namespace std;

#define WINX	1000
#define WINY	700

void welcome();
int game();
void drawcircle(int color,int x,int y,int rx,int ry);
void drawbar(int barcolor,int mx,int rad,int barw);
void drawbrick(int brickcolor,int bx, int by);

void score_getter(long long int score);
void read_from_user(char *str);
int evaluate(char *str);
int evaluate(string str);
void leader_board();
void print_board();