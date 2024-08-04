/*       SPACE INVADERS      //
//by Cosmin Munteanu (c) 2013*/
#include"asciipower.h"

int ship_x=40;
int ship_y=23;
int ship_cadence=1;
int ship_cadence_max=10;
int laser_x[100];
int laser_y[100];
int laser_n=0;
int alien_x[100];
int alien_y[100];
int alien_t[100];
int alien_n=0;
int alien_laser_x[100];
int alien_laser_y[100];
int alien_laser_n=0;
int alien_counter=1;
int alien_counter_max=15;
int dir=0;
bool dead;
int score;
int old_score=0;
int lifes;
void remove_i(int v[],int i,int n)
{
    int aux;
    aux=v[i];
    v[i]=v[n-1];
    v[n-1]=aux;
}
void game_init()
{
    dead=false;
    alien_counter_max+=3;
    score=0;
    lifes=5;
    dir=0;
    ship_x=40;
    ship_y=23;
    laser_n=alien_n=0;
    alien_n=80;
    for(int i=0;i<20;i++)
    for(int j=0;j<4;j++)
    {
        alien_x[i+20*j]=i*3+1;
        alien_y[i+20*j]=j*3+1;
        alien_t[i+20*j]=rand()%3;
    }
}
void move_alien()
{
    bool ok=false;
    alien_counter=(alien_counter+1)%alien_counter_max;
    if(alien_counter==0)
    {
        for(int i=0;i<alien_n;i++)
        {
            if(dir==0)alien_x[i]++;
            if(dir==1)alien_x[i]--;
            if(dir>1)alien_y[i]++;
            if(alien_x[i]==0||alien_x[i]==79)ok=true;
            if(alien_y[i]>22)dead=true;
        }
        if(dir>1)
        {
            dir=1-(dir-10);
            alien_counter_max-=2;
            if(alien_counter_max<1)alien_counter_max=1;
            ok=false;
        }
        if(ok)dir+=10;
    }
}
int main()
{
    Init_ASCII("Space Invaders");
    game_init();
    while(!Key_Press(VK_ESCAPE))
    {
        Clear_Screen();
        ship_cadence_max=10-((score-old_score)/1000);
        if(ship_cadence_max<1)ship_cadence_max=1;
        if(Key_Press(VK_LEFT))ship_x--;
        if(Key_Press(VK_RIGHT))ship_x++;
        if(Key_Press(VK_SPACE))ship_cadence=(ship_cadence+1)%ship_cadence_max;
        if(Key_Press(VK_SPACE)&&ship_cadence==0)
        {
            laser_x[laser_n]=ship_x;
            laser_y[laser_n]=ship_y;
            laser_n++;
        }
        if(ship_x<1)ship_x=1;
        if(ship_x>79)ship_x=79;
        move_alien();
        for(int i=0;i<alien_n;i++)
        {
            int color,chr;
            if(alien_t[i]==0){color=R+B+I;chr=0xea;}
            if(alien_t[i]==1){color=G+I;chr=0x9d;}
            if(alien_t[i]==2){color=B+I;chr=0xe8;}
            Set_Color(color);
            Put_Char(alien_x[i],alien_y[i],chr);
            if(rand()%300==0||(alien_x[i]==ship_x&&rand()%20==0))
            {
                alien_laser_x[alien_laser_n]=alien_x[i];
                alien_laser_y[alien_laser_n]=alien_y[i];
                alien_laser_n++;
            }
        }
        for(int i=0;i<laser_n;i++)
        {
            laser_y[i]--;
            Set_Color(R+G+I);
            Put_Char(laser_x[i],laser_y[i],0xad);
            if(laser_y[i]<0)
            {
                remove_i(laser_x,i,laser_n);
                remove_i(laser_y,i,laser_n);
                laser_n--;
                i--;
            }
        }
        for(int i=0;i<alien_laser_n;i++)
        {
            alien_laser_y[i]++;
            Set_Color(R+I);
            Put_Char(alien_laser_x[i],alien_laser_y[i],0xf8);
            if(alien_laser_y[i]>25)
            {
                remove_i(alien_laser_x,i,alien_laser_n);
                remove_i(alien_laser_y,i,alien_laser_n);
                alien_laser_n--;
                i--;
            }
            if(alien_laser_x[i]==ship_x&&alien_laser_y[i]==ship_y)
            {
                lifes--;
                remove_i(alien_laser_x,i,alien_laser_n);
                remove_i(alien_laser_y,i,alien_laser_n);
                alien_laser_n--;
                i--;
            }
        }
        for(int i=0;i<alien_n;i++)
        for(int j=0;j<laser_n;j++)
            if(laser_x[j]==alien_x[i]&&laser_y[j]==alien_y[i])
            {
                score+=100;
                remove_i(alien_x,i,alien_n);
                remove_i(alien_y,i,alien_n);
                remove_i(alien_t,i,alien_n);
                alien_n--;
                i--;
                remove_i(laser_x,j,laser_n);
                remove_i(laser_y,j,laser_n);
                laser_n--;
                j--;
            }
        Set_Color(I);
        Put_Char(ship_x,ship_y,0x7f);
        Set_Cursor(0,0);
        Set_Color(R+G+B+I);
        printf("Score:%i",score);
        Set_Color(R+I);
        for(int i=0;i<lifes;i++)
            printf(" %c",3);
        if(lifes<0)dead=true;
        if(dead)
        {
            Set_Cursor(32,12);
            Set_Color(R+BG(R+I));
            printf(">>>GAME OVER<<<");
        }
        if(alien_n==0)
        {
            Set_Cursor(32,12);
            Set_Color(G+BG(G+I));
            printf(">>> YOU WIN <<<");
        }
        if(dead||alien_n==0)
        {
            for(int i=5;i>0;i--)
            {
                Set_Cursor(31,14);
                Set_Color(R+G+B+I);
                printf("Get ready in ... %i",i);
                Sleep(1000);
            }
            if(alien_n==0)old_score=score;
            game_init();
            if(alien_n==0)score=old_score-1000;
            if(score<0)score=0;
        }
    }
    return 0;
}
