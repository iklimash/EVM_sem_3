#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

enum Colors {
    BLACK       = 0,
    BLUE        = 1,
    GREEN       = 2,
    CYAN        = 3,
    RED         = 4,
    MAGENTA     = 5,
    BROWN       = 6,
    LIGHTGRAY   = 7,
    DARKGRAY    = 8,
    LIGHTBLUE   = 9,
    LIGHTGREEN  = 10,
    LIGHTCYAN   = 11,
    LIGHTRED    = 12,
    LIGHTMAGENTA= 13,
    YELLOW      = 14,
    WHITE       = 15
};

void setColor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
}

// Функция для установки позиции курсора
void gotoxy (int x, int y)
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// x1, y1 - координаты верхнего левого угла окна
// x2, y2 - координаты верхнего правого угла окна
void createWindow (int X1, int Y1, int X2, int Y2) 
{
    gotoxy(X1 - 1, Y1 - 1);
    for(int x = X1 - 1; x < X2 + 2; x++)
        cout << '#';
    gotoxy(X1 - 1, Y2 + 1);
    for (int x = X1 - 1; x < X2 + 2; x++)
        cout << '#';
    for (int y = Y1; y <= Y2 + 1; y++)
    {    
        gotoxy(X1 - 1, y);
        cout << '#';
    }
    for (int y = Y1; y <= Y2 + 1; y++)
    {    
        gotoxy(X2 + 1, y);
        cout << '#';
    }

        
}

int main()
{
    // system("cls");
    cout << "Hello"; 

    createWindow(10, 5, 70, 15);
    setColor(WHITE, WHITE);
    return 0;
}
