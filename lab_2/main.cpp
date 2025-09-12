#include <iostream>
#include <windows.h>
#include <string>

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

void scrollArea(int X1, int Y1, int X2, int Y2, int lines) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                
    SMALL_RECT scrollRect;
    scrollRect.Left = X1;
    scrollRect.Top = Y1;
    scrollRect.Right = X2;
    scrollRect.Bottom = Y2;
    
    COORD scrollTarget;
    scrollTarget.X = X1;
    scrollTarget.Y = Y1 - 1; 
    
    CHAR_INFO fill;
    fill.Char.UnicodeChar = ' ';
    fill.Attributes = 15; 
                
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
}

void printColors(int X1, int Y1, int X2, int Y2, unsigned delay, int step)
{
    const int maxLines = (Y2 - Y1) / step + 1;
    const string colorNames[] = {
            "black","blue","green","cyan","red","magenta","brown","lightgray","darkgray","lightblue","lightgreen",
                               "lightcyan","lightred","lightmagenta","yellow","white"
    };
    const string colorNums[] = {
        "0","1","2","3","4","5","6","7","8","9","10",
                               "11","12","13","14","15"    
    };
    setColor(15, 0);
    createWindow(X1, Y1, X2, Y2);
    int currLine = Y1;
    for (int colorIndex = 0; ; colorIndex = (++colorIndex) % 16) 
    {
        for (int textIndex = 0; textIndex < 16; ++textIndex)
        {
            
            if (currLine > Y2) {
               
                scrollArea(X1, Y1 + 1, X2, Y2, 1);

                currLine = Y2;
            }
            
            setColor(15, 0);
            gotoxy(X1, currLine);
            for (int i = 0; i < X2 - X1 + 1; ++i) {
                cout << ' ';
            }
            
            setColor(textIndex, colorIndex);
            gotoxy(X1, currLine);
            cout << colorNums[colorIndex] << ' ' << colorNames[textIndex];
        
            currLine++;
            
            Sleep(delay);

    
        }
    }
}   

int main()
{
    system("cls");
    Sleep(1400);
    const unsigned T = 1400; // delay mc
    const int S = 1; // Шаг строк

    const int X1 = 15;
    const int Y1 = 10;
    const int X2 = 65;
    const int Y2 = 20;

    printColors(X1, Y1, X2, Y2, T, S);

    return 0;
}
