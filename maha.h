
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "lable.c"
#include "data.c"
#include "pass_g.c"
#include "edit_delete.c"
#include "find.c"
void logo()
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc, 12); // this function working on changing of color
    puts("Creat DBMS in C By Amantaycon, url = https://www.github.com/amantaycon");

    SetConsoleTextAttribute(hc, 7);
}
/* black 0, blue 1, green 2, aqua 3, red 4, purple 5, yellow 6, white 7, gray 8, light blue 9,light green 10, light aqua 11, light red 12, light purple 13, light yellow 14, white bright 15
 */
