#include"asciipower.h"
#include"conio.h"

int main()
{
    Init_ASCII("Coding faker!");
    char text[]=">start\n>open bank target\n>crack data base /934 -%235 -interior\n|decoding data*************\ndone!\ndecrypting completed\nentering bank code****\nbreaking******\gathering***\n*\n*\n*\nDONE!\n|>system shutdown\n>opening C++\n|opening C++ interface******\nwait*****\npreparing interface***\nopen compilator******\n*\n*\n*\nDONE!\nready***\n|int automatic=false;\n    int i=0;\n    while(i<strlen(text))\n    {\n        if(!automatic)getch();\n        else Sleep(100);\n        if(text[i]=='|')\n        {\n            automatic=!automatic;\n\        }\n        else if(text[i]=='*')\n        {\n            printf(\".\");\n            Sleep(300);\n        }\n        else\n        {\n            printf(\"%c\",text[i]);\n        }\n        i++;\n    }\n               ";
    int automatic=false;
    int i=0;
    while(i<strlen(text))
    {
        if(!automatic)getch();
        else Sleep(100);
        if(text[i]=='|')
        {
            automatic=!automatic;
        }
        else if(text[i]=='*')
        {
            printf(".");
            Sleep(300);
        }
        else
        {
            printf("%c",text[i]);
        }
        i++;
    }
    return 0;
}
/*

    */
