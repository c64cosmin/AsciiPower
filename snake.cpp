/*           SNAKE           //
//by Cosmin Munteanu (c) 2013*/
#include"asciipower.h"
#define FRUIT 20
int sx[3000];
int sy[3000];
int sn;
int fx[FRUIT];
int fy[FRUIT];
int mx,my;
int score;
bool dead;

void game_init()
{
    for(int i=1;i<3000;i++)sx[i]=sy[i]=-1;
    sx[0]=40;
    sy[0]=12;

    for(int i=0;i<FRUIT;i++)
    {
        fx[i]=rand()%80;
        fy[i]=rand()%24;
    }
    mx=1;my=0;
    score=0;
    dead=false;
    sn=5;
    Clear_Screen();
}
int main()
{
    Init_ASCII("Snake");
    game_init();

    while(!Key_Press(VK_ESCAPE))
    {
        Sleep(75);

        bool pressed=false;
        if(Key_Press(VK_RIGHT)&&mx!=-1&&!pressed){mx=1;my=0;pressed=true;}
        if(Key_Press(VK_LEFT)&&mx!=1&&!pressed){mx=-1;my=0;pressed=true;}
        if(Key_Press(VK_DOWN)&&my!=-1&&!pressed){mx=0;my=1;pressed=true;}
        if(Key_Press(VK_UP)&&my!=1&&!pressed){mx=0;my=-1;pressed=true;}

        for(int i=sn;i>0;i--)
        {
            if(sx[i]==sx[0]&&sy[i]==sy[0])dead=true;
            sx[i]=sx[i-1];
            sy[i]=sy[i-1];
            if(i!=sn)

            Set_Color(G+BG(G+I));
            Put_Char(sx[i],sy[i],0xb0+((sx[i]+sy[i]%2)%2));
        }

        sx[0]=(sx[0]+80+mx)%80;
        sy[0]=(sy[0]+24+my)%24;

        Set_Color(BG(G));
        Put_Char(sx[0],sy[0],' ');
        Set_Color(0);
        Put_Char(sx[sn],sy[sn],' ');

        for(int i=0;i<FRUIT;i++)
        {
            if(sx[0]==fx[i]&&sy[0]==fy[i])
            {
                score+=1+1*(i%2);
                fx[i]=rand()%80;
                fy[i]=rand()%24;
                sn++;
            }
            Set_Color(R+I*(i%2));
            Put_Char(fx[i],fy[i],0x2a);
        }

        Set_Color(B+I+BG(I));
        Set_Cursor(0,24);
        printf("                                                                               ");
        Set_Cursor(0,24);
        printf("Score:%8i   Lenght:%3i",score,sn);

        if(dead)
        {
            Set_Cursor(32,12);
            Set_Color(R+BG(R+I));
            printf("YOU ARE DEAD!!!");
            Set_Color(R+G+B+I);
            for(int i=5;i>0;i--)
            {
                Set_Cursor(32,14);
                printf("YOU START IN %i!",i);
                Sleep(1000);
            }
            game_init();
        }
    }
    return 0;
}
