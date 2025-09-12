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
void scrollWindow(int X1, int Y1, int X2, int Y2) {
    HWND hWnd = GetConsoleWindow();
    RECT rect = { X1, Y1, X2, Y2 };
    ScrollWindowEx(hWnd, 0, 1, &rect, NULL, NULL, NULL, SW_INVALIDATE);
}

void printColors(int X1, int Y1, int X2, int Y2, unsigned delay, int step)
{
    const int maxLines = (Y2 - Y1) / step + 1;
    const string colorNames[] = {
            "black","blue","green","cyan","red","magenta","brown","lightgray","darkgray","lightblue","lightgreen",
                               "lightcyan","lightred","lightmagenta","yellow","white"
    };
    const string colorNums[] = {
            "black","blue","green","cyan","red","magenta","brown","lightgray","darkgray","lightblue","lightgreen",
                               "lightcyan","lightred","lightmagenta","yellow","white"
    };
    setColor(15, 0);
    createWindow(X1, Y1, X2, Y2);
    for (int colorIndex = 0; ; colorIndex = (++colorIndex) % 16) 
    {
        for (int textIndex = 0; textIndex < 16; ++textIndex)
        {
            int tempBg = colorIndex, tempText = textIndex;
            for (int line = 0; line < maxLines; ++line) {
                if (Y2 - line * (step + 1) >= Y1 && Y2 - line * (step + 1) <= Y2) {
                    
                    setColor(15, 0); 
                    gotoxy(X1, Y1 - line * (step + 1));
                    for (int i = 0; i < X2 - Y1 + 1; ++i) {
                        cout << ' ';
                    }
                    setColor(tempText, tempBg);
                    gotoxy(X1, Y1 - line * (step + 1));
                    cout << colorNums[tempBg] << ' ' << colorNames[tempText];
                }

                
                if (tempText == 0 && tempBg!= 0) {
                    tempBg--;
                    tempText = 15;
                } else if (tempText == 0 && tempBg == 0) {
                    break;
                } else {
                    tempText--;
                }
            }
            scrollWindow(X1, Y1, X2, Y2);
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
