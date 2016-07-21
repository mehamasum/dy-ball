#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
using namespace std;

#define MAX     1000
#define inf     (1<<30) 

int leaders=0;
char scr[20];

void score_getter(long long int score)
{
	sprintf(scr,"%lld",score);
}

void read_from_user(char *str)
{
    char ch,  pseudo_string[2] = ""; 
 
    strcpy(str, ""); //Initializing the string
    while(1)
    {
        ch = getch();
        if(!ch) ch = getch(); // For ignoring when the arrow keys like " -> " or " <- " is pressed
        if(ch == 13) break; // 13 is the ASCI Value of the key "Enter" 
        pseudo_string[0] = ch; 
        strcat(str, pseudo_string);
        outtextxy(460,420,str);
    }
 
    return; 
}
 
int evaluate(char *str)
{
    int ret = 0, mul = 1, len = strlen(str); 
    while(len)
        ret += (str[--len]-'0')*mul, mul*=10; 
    return ret; 
}
 
int evaluate(string str)
{
    int ret = 0, mul = 1, len = str.size(); 
    while(len)
        ret += (str[--len]-'0')*mul, mul*=10; 
    return ret; 
}
 
void leader_board()
{
    settextstyle(3, HORIZ_DIR,3);
    //Declaration of the Variables Starts  
    char ch, str[MAX+10],name_of_the_player[MAX+10], string_score[15]; 
    int score, low_score = inf, cnt_score = 2, pre_score = inf, cur = 2, i, j; 
    string copy_of_name, copy_of_score;
    vector<string> Ranking[30];
    //Declaration of the Variables Ends 
 
 
 
    strcpy(string_score, scr); 
    score = evaluate(string_score); 
 
 
    //Get Lowest Score From the Input File
    freopen("Scoreboard.txt", "r", stdin); 
    while(scanf("%s", str) == 1)
    {
        Ranking[cnt_score].push_back(str); 
        if('0' <= str[0] && str[0] <= '9') low_score = min(low_score, evaluate(str)), cnt_score+=2; //2,4,6....20   
        if(cnt_score == 22) break; 
    }
    fclose(stdin); 
    Ranking[cnt_score].push_back("0");
    leaders=cnt_score/2-1;
    if(cnt_score >= 22 && score <= low_score) goto Ending; 
    leaders++;
 
 
    //Getting the name of the current player
    outtextxy(415,400,"TYPE YOUR NAME:"); 
    read_from_user(name_of_the_player); 
 
 
 
    //Finding its position
    while(score <= evaluate(Ranking[cur].back()) ) cur+= 2;
    cur--; 
    copy_of_name = name_of_the_player;
    copy_of_score = string_score; 
    Ranking[cur].push_back(copy_of_name); 
    Ranking[cur].push_back(copy_of_score); 
 
 
 
    //Writing in the Scoreboard 
    freopen("Scoreboard.txt", "w", stdout);
    for(i = 1; i < cnt_score; i++)
        if(Ranking[i].size())
        {
            //D(Ranking[i].size()); 
            for(j = 0; j < (int) Ranking[i].size(); j++)
                printf("%s ", Ranking[i][j].c_str()); 
            puts(""); 
        }
 
        fclose(stdin); 
        fclose(stdout);
Ending:; 
        //For Debugging Purpose
        //outtextxy(100,100,"Returning 0"); 
        //while(!kbhit()) delay(200); 
        return; 
} 
 
void print_board()
{
    freopen("Scoreboard.txt", "r", stdin);
    int i=0,y=150;
    char temp[30];
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR,3);
    //outtextxy(350,100,"LEADER BOARD");
    for(i=0;i<leaders;i++)
    {
        gets(temp);
        printf("%s\n",temp);
        outtextxy(400,y,temp);
        y+=30;
    }
    fclose(stdin);
}