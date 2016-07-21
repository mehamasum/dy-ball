#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "dx.h"
using namespace std;
 
#define D(x)    cout<< #x " = " << (x) <<endl 
#define sqr(x)  (x)*(x)
#define pi		acos(-1.00)

typedef double db; 
 
char s[20],l[20]; 
int level=1,score_level_converter=0;
int i,j,rad;
long long int score=1,best=0;
int blenx=60, bleny=30;

int dir[10000]; 

int barw=120;
int prebarw;
int bonuson[10]={0};
int bonusx[10], bonusy[10];
int bonusprecx=bonusx[0];
int bonusprecy=bonusy[0];
 
int color=0;
int mx=0;
int premx=0;
bool bonusdrop[10]={0};
int barinc=0, bardic=0;
char bonusname[10][100]={"LARGER BAT","SMALLER BAT","BONUS LIFE","BOMBER BALL"};
 
int brickcount=15;
int boom[100]={0};
int bxarray[10000]={0},byarray[10000]={0},bcolor[10000]={0};
 
int heart=3;
int bomber=0;

inline int mabs(int x) {return x<0? -x:x;}

int calc(int i, int w, int y)
{
    db ang = 5 + i*125/(db) w, yp2 = y*y, ret;
    ang = 90-ang;
    ang *= pi/180.00;
    ret = yp2 / (sin(ang) * sin(ang));
    ret -= yp2;
    return min((int) sqrt(ret), 10);
}
 
bool dist(int x1,int y1, int x2, int y2)
{
    return sqr(x1-x2) + sqr(y1-y2) <= sqr(rad);  
}
 
void draw_bonus(int color, int i)
{
    drawcircle(BLACK,bonusprecx,bonusprecy,10,10); // Path Tracing
 
    int m;
    for(m=1;m<=brickcount;m++)
    {
            if(boom[m]==0)
            {
                if(bonusx[i]>=bxarray[m] && bonusx[i]<=bxarray[m]+blenx)
                {
                    drawbrick(bcolor[m],bxarray[m],byarray[m]);
                    printf("loop: %d: %d %d %d\n",i,bxarray[i],byarray[i],bcolor[i]);
                }
            }
    }
 
    drawcircle(color,bonusx[i],bonusy[i],10,10);
 
    bonusprecx=bonusx[i];
    bonusprecy=bonusy[i];
 
    bonusy[i]+=3;
 
     
 
    setcolor(color);
    outtextxy(400,10,bonusname[i]);
}
 
void drop_bonus(int i)
{
     
    if( bonusy[i]>=WINY-rad-rad && bonusy[i]<=WINY && bonusx[i]>=mx && bonusx[i]<=mx+barw|| bonusy[i]>=WINY-rad-rad && bonusx[i]>=mx-rad && bonusx[i]<=mx||bonusy[i]>=WINY-rad-rad && bonusx[i]>=mx+barw && bonusx[i]<=mx+barw+rad)
    { 
        if(i==0) 
        {
            if(barw<500) barw+=40; 
            barinc=1;
        } 
        else if (i==1) 
        {
            if(barw>50) barw-=20;
            bardic=1;
        } 
        else if (i==2) 
        {
            if(heart<5) heart++;
        }
        else if(i==3)
        {
            cleardevice();
 
            settextstyle(3,0,10);
            outtextxy(300,100,"BOOM!");
            delay(1000);
             
            level++;
            sprintf(l,"LEVEL UP!",level);
            setcolor(YELLOW);
            outtextxy(250, 275,l);
            delay(1000);
            score+=50;
            sprintf(l,"SCORE +%d !",50);
            setcolor(YELLOW);
            outtextxy(230, 375,l);
 
            delay(2000);
            cleardevice();
             
            bomber=1;
             
        }
        bonusdrop[i]=true;
    }
    else if(bonusy[i]>WINY) { bonuson[i]=0; bonusdrop[i]=true;}
    if(bonusdrop[i]==true) 
    {
        bonuson[i]=false;
        color=BLACK;
        drawcircle(color,bonusprecx,bonusprecy,10,10);
        setcolor(BLACK);
        outtextxy(400,10,bonusname[i]);
    }
    //printf("last\n");
}
 
 int game()
 {
	prebarw=barw;
newgame:
    //NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME NEW GAME 
    cleardevice();
    heart=3;
    brickcount=10;
    int cx,cy;
    rad=10;
    cx=cy=rad;
    int precx=0,precy=0;
 
 
 
    int bx,by;
 
    int accx=4,accy=6; // ------------------ 
 
    double de=16;
 
 
    int barcolor=0;
    int brickcolor=0;
 
     
    score=1;
    score_level_converter=0;
    level=1;
 
 
    //bricks generator
     
    int flag=0;
    int dx; 
    //NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL NEW LEVEL 
newlevel:
    cleardevice();
    cx=rad; cy=rad;
	precx=precy=rad;
    accx=5; accy=7;
    score_level_converter=0;
    if(brickcount<26) brickcount++;
    barinc=0; bardic=0;
    memset(bonuson,0,sizeof(bonuson));
    memset(bonusx,0,sizeof(bonusx));
    memset(bonusy,0,sizeof(bonusy));
    memset(bonusdrop,0,sizeof(bonusdrop));
    memset(bxarray,0,sizeof(bxarray));
    memset(byarray,0,sizeof(byarray));
    memset(bcolor,0,sizeof(bcolor));
    memset(boom,0,sizeof(boom));
    for(i=1,brickcolor=0;i<=brickcount; )
    {
        bx=rand()%900;
        by=rand()%310+40;
 
        for(j=i-1,flag=0;j>=0;j--)
        {
            if(bx>=bxarray[j]-60 && bx<=bxarray[j]+blenx+60 && by>=byarray[j]-60 && by<=byarray[j]+bleny+60){ flag=1;break;}
        }
        if(flag==1) continue;
        bxarray[i]=bx;
        byarray[i]=by;
         
        brickcolor++;
        if(brickcolor==4) brickcolor++;
        else if(brickcolor>=14) brickcolor=1;
        bcolor[i]=brickcolor;
        printf("%d: %d %d %d\n",i,bxarray[i],byarray[i],bcolor[i]);
        i++;
        drawbrick(brickcolor,bx,by);    
 
    }
    delay(75);
 
     
 
    settextstyle(3, HORIZ_DIR,3);
 
    //THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP THE LOOP 
    for(i=0; ;i++)
    {
        //level up
        if(score_level_converter==brickcount) 
        {
            score_level_converter=0;
            if(de>2) de-=1; 
            //accx++; accy++;
            level++;
            sprintf(l,"LEVEL %d!",level);
 
            setcolor(YELLOW);
            outtextxy(450, 275,l);
            delay(2000);
            setcolor(BLACK);
            outtextxy(450, 275, l);
            goto newlevel;
        }
        delay(de);
newlife:
        //circle
        color=0;
        drawcircle(color,precx,precy,rad,rad); // Path Tracing
        color=WHITE;//COLOR(255,100,0);
        drawcircle(color,cx,cy,rad,rad);
 
        precx=cx;
        precy=cy;
 
 
        //bar
        barcolor=0;
        if(bardic)  { bardic=0; setfillstyle(SOLID_FILL,BLACK); bar(0,WINY-rad,WINX,WINY);}
        else drawbar(barcolor,premx,rad,barw);
 
        mx=mousex();
        if(mx>WINX-barw) mx=WINX-barw;
        barcolor=14;
        drawbar(barcolor,mx,rad,barw);
 
        premx=mx;
 
 
        //acceleration
        cx+=accx;
        cy+=accy;
 
        //bonus ball droping
        if(bonuson[0])
        {
            //long bat
            draw_bonus(RGB(0,128,255),0);
            drop_bonus(0);
        }
 
        if(bonuson[1])
        {
            //small bat
            draw_bonus(RGB(0,255,0),1);
            drop_bonus(1);
        }
        if(bonuson[2])
        {
            //life
            draw_bonus(RGB(237,28,36),2);
            drop_bonus(2);
        }
        if(bonuson[3])
        {
            //bomb
            draw_bonus(RGB(190,0,200),3);
            drop_bonus(3);
            if(bomber) { bomber=0; goto newlevel;}
        }
        //brickcheck
        for(j=1;j<=brickcount;j++)
        {
            if(cx>=bxarray[j]-rad && cx<=bxarray[j]+blenx+rad && cy>=byarray[j]-rad && cy<=byarray[j]+bleny+rad && boom[j]==0)
            {
                delay(50);
                brickcolor=0;
                drawbrick(brickcolor,bxarray[j],byarray[j]);
                boom[j]=1;
                int bully=rand()%4;
                if(j==6 && bully==0) {bonuson[0]=true; bonusx[0]=bxarray[j], bonusy[0]=byarray[j];} //large ball
                if(j==6 && bully==1) {bonuson[1]=true; bonusx[1]=bxarray[j], bonusy[1]=byarray[j];} //small ball
                if(j==6 && bully==2) {bonuson[2]=true; bonusx[2]=bxarray[j], bonusy[2]=byarray[j];} //life
                if(j==6 && bully==3) {bonuson[3]=true; bonusx[3]=bxarray[j], bonusy[3]=byarray[j];} //bomb
                score++;
                //printf("%lld\n",score);
                score_level_converter++;
                accy=-accy;
                //accx=-accx;
                if((dist(bxarray[j],byarray[j],cx-accx,cy-accy) || dist(bxarray[j]+blenx,byarray[j],cx-accx,cy-accy) || dist(bxarray[j],byarray[j]+bleny,cx-accx,cy-accy) || dist(bxarray[j]+blenx, byarray[j]+bleny, cx-accx,cy-accy)) && !boom[j])
                {
                    accy = -accy; 
                    accx = -accx; 
                    printf("HI"); 
                }
 
            }
 
            //putpixel(cx-accx,cy-accy,WHITE);
 
        }
        //wallcheck
        bool touch = false;
        bool con1,con2,con3;
        if(cx>=WINX-rad || cx<=rad) accx*=-1;
        if(cy<=rad) accy*=-1;
        else if ( cy>=WINY-rad-rad && cx>=mx && cx<=mx+barw ) accy*=-1, touch = true, dx = mx+50-cx, con1=true;
        else if( cy>=WINY-rad-rad && cx>=mx-rad && cx<=mx)
        { 
            if(accx > 0) accx *=-1, accy*=-1;
            else accy = -accy; 
            touch = true; 
            dx = mx+50-cx;
            con2=true;
        }
        else if( cy>=WINY-rad-rad && cx>=mx+barw && cx<=mx+barw+rad)
        { 
            if(accx < 0) accx*=-1, accy*=-1;
            else accy = -accy;
            touch = true; 
            dx = mx+50-cx;
            con3=true;
        }
        else if( cy>=WINY-rad)
        {
            //Game over case
            heart--;
            if(heart) 
            {
                outtextxy(450,450,"OOPS!");
                delay(1000);
                setcolor(BLACK);
                outtextxy(450,450,"OOPS!");
 
                cx=rad;
                cy=rad;
                accx=5;
                accy=7;
                goto newlife;
            }
            if(heart==0)
            {
                setcolor(BLACK);
                outtextxy(10, 10, s);
                color=0;
                drawcircle(color,precx,precy,rad,rad);
                color=COLOR(255,100,0);
                drawcircle(color,cx,cy,rad,rad);
                setfillstyle(SOLID_FILL,BLACK);
                bar(792,0,1000,40);
 
                setcolor(WHITE);
                settextstyle(3, HORIZ_DIR,5);
                outtextxy(350, 175, "GAME OVER!");
 
                sprintf(s,"SCORE:%2lld",score);
                score_getter(score);
                //settextstyle(3, HORIZ_DIR,5);
                outtextxy(380,240, s);
 
                delay(2000);
 
                leader_board();
                cleardevice();
                readimagefile("board.jpg",0,0,1000,700);
                print_board();
				
				clearmouseclick(WM_LBUTTONDOWN);
				while(!ismouseclick(WM_LBUTTONDOWN))
				{
					delay(100);
					setcolor(WHITE);
					outtextxy(320,550,"Click anywhere to retry!");
					delay(500);
					setcolor(BLACK);
					outtextxy(320,550,"Click anywhere to retry!");
				}
				clearmouseclick(WM_LBUTTONDOWN);
                goto newgame;
                system("pause");
                return 0;
            }
        }
 
 
 
		if(touch)
        {
			//D(cx); D(cy);
			//D(mousex() + barw/2 -cx);
			int cur =mousex() + barw/2-cx;

			if(cur>=0) // has hitted on the left half
			{
				//D(cur);
				accx = calc(cur, barw, accy);
				D(accx);
				accx = -accx;
				//D(accx);
			}

			else
			{
				cur = -cur;
				accx = calc(cur, barw, accy);
				D(accx); 
			}
        }
 
        //SCORING       
        sprintf(s,"SCORE: %lld",score);
        setcolor(WHITE);
        outtextxy(10, 10, s);
 
        //LIFE
        if(heart==3) readimagefile("heart3.jpg",792,0,1000,40);
        else if(heart==2) readimagefile("heart2.jpg",792,0,1000,40);
        else if(heart==1) readimagefile("heart1.jpg",792,0,1000,40);
        else if(heart==4) readimagefile("heart4.jpg",792,0,1000,40);
        else if(heart==5) readimagefile("heart5.jpg",792,0,1000,40);
    }
    return 0; 
}