#include <stdio.h>
#include <time.h>
#include "graphics.h"
#include "dx.h"

int main()
{   
	srand (time(NULL)); // For Randomized Rand()
	
    initwindow(WINX,WINY,"dyball_random bricks");
	//setbkcolor(WHITE);
	//welcomenote
	//readimagefile("welcome.jpg",0,0,1000,700);
    readimagefile("welcome2.jpg",0,0,1000,700);

    /*while(!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
        setcolor(WHITE);
        outtextxy(548,200,"Click anywhere to start the game");
        delay(500);
        setcolor(BLACK);
        outtextxy(548,200,"Click anywhere to start the game");
    }*/
	welcome();
    clearmouseclick(WM_LBUTTONDOWN);
	game();
}