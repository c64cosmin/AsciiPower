/*       ASCII POWER         //
//by Cosmin Munteanu (c) 2013*/
#ifndef _ASCII_POWER_
#define _ASCII_POWER_
#include<cstdio>
#include<cstdlib>
#include<windows.h>

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0X41
#define VK_B 0X42
#define VK_C 0X43
#define VK_D 0X44
#define VK_E 0X45
#define VK_F 0X46
#define VK_G 0X47
#define VK_H 0X48
#define VK_I 0X49
#define VK_J 0X4a
#define VK_K 0X4b
#define VK_L 0X4c
#define VK_M 0X4d
#define VK_N 0X4e
#define VK_O 0X4f
#define VK_P 0X50
#define VK_Q 0X51
#define VK_R 0X52
#define VK_S 0X53
#define VK_T 0X54
#define VK_U 0X55
#define VK_V 0X56
#define VK_W 0X57
#define VK_X 0X58
#define VK_Y 0X59
#define VK_Z 0X5a

#define R 4
#define G 2
#define B 1
#define I 8
#define BG(c) (c)*16

HANDLE hConsole;

void Init_ASCII(const char* app_name)
{
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X=80;
    pos.Y=40;
    SetConsoleScreenBufferSize(hConsole,pos);
    SetConsoleTitle(app_name);
}

void Set_Color(int color)
{
    SetConsoleTextAttribute(hConsole,color);
}

void Set_Cursor(int x,int y)
{
    COORD pos;
    if(x==80&&y==24)x--;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hConsole,pos);
}

int Get_Cursor_X()
{
    CONSOLE_SCREEN_BUFFER_INFO pos;
    GetConsoleScreenBufferInfo(hConsole,&pos);
    return pos.dwCursorPosition.X;
}

int Get_Cursor_Y()
{
    CONSOLE_SCREEN_BUFFER_INFO pos;
    GetConsoleScreenBufferInfo(hConsole,&pos);
    return pos.dwCursorPosition.Y;
}

void Get_Cursor(int &x,int &y)
{
    x=Get_Cursor_X();
    y=Get_Cursor_Y();
}

void Put_Char(int x,int y,char c)
{
    if(x>=0&&x<=80&&y>=0&&y<=25)
    {
        int ox,oy;
        Get_Cursor(ox,oy);
        Set_Cursor(x,y);
        printf("%c",c);
        Set_Cursor(ox,oy);
    }
}

char Get_Char(int x,int y)
{
    COORD pos;
    char* c=(char*)malloc(sizeof(char));
    pos.X=x;
    pos.Y=y;
    DWORD dummy;
    ReadConsoleOutputCharacter(hConsole,
                               c,
                               sizeof(TCHAR),
                               pos,
                               &dummy);
    return c[0];
}

void Clear_Screen()
{
    Sleep(15);
    Set_Color(I);
    system("cls");
}

bool Key_Press(int key)
{
    return GetAsyncKeyState(key);
}

#endif
