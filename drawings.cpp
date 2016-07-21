#include "graphics.h"
#include "dx.h"

void drawcircle(int color,int x,int y,int rx,int ry)
{
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    fillellipse(x,y,rx,ry);
    return;
}
 
void drawbar(int barcolor,int mx,int rad, int barw)
{
    setcolor(barcolor);
    setfillstyle(SOLID_FILL,barcolor);
    bar(mx,WINY-rad,mx+barw,WINY);
    return;
}
void drawbrick(int brickcolor,int bx, int by)
{
    setcolor(brickcolor);
    setfillstyle(SOLID_FILL,brickcolor);
    bar(bx,by,bx+60,by+30);
    return;
}