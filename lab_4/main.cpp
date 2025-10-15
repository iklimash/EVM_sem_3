#include "dos.h"
#include "conio.h"
#include "stdio.h"

int code();

int main() {
    int x = 1, y = 1, ch = 0;
    textbackground(BLACK);
    window(15, 10, 65, 20);
    clrscr();
    
    do {
        clrscr();
        gotoxy(x, y);
        putch('*');
        
        ch = code();
        
        switch (ch) {
            case 72:  
                if (y > 1) y--;
                break;
            case 80:  
                if (y < 10) y++;
                break;
            case 75:  
                if (x > 1) x--;
                break;
            case 77:  
                if (x < 50) x++;
                break;
        }
        
    } while (ch != 27); 
    
    return 0;
}

int code() {
    union REGS r;
    r.h.ah = 0x7;
    int86(0x21, &r, &r);
    return r.h.al;
}