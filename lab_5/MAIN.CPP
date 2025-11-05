#include <dos.h>
#include <conio.h>
#include <stdio.h>

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

void interrupt (far *oldfunc)(__CPPARGS);
int flag = 0;
unsigned char firstArr[100];
int currentIndex = 0;


unsigned char scanToAscii[128] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' '
};

void interrupt far nineHandle(__CPPARGS) {
    unsigned char scanCode;
    unsigned char asciiChar;
    int i, check;
    

    scanCode = inportb(0x60);
    

    if (!(scanCode & 0x80)) {
        asciiChar = scanToAscii[scanCode];
        
        if (flag == 0) {
            if (asciiChar != 0 && asciiChar != 'z') {
                firstArr[currentIndex] = asciiChar;
                cprintf("%c", asciiChar);
                currentIndex++;
            }
            if (asciiChar == 'z') {
                firstArr[currentIndex] = '$';
                flag = 1;
                cprintf("\n\r");
            }
        }
        else if (flag == 1) {
            check = 1;
            if (asciiChar != 0 && asciiChar != 'z') {
                for (i = 0; i < currentIndex; i++) {
                    if (firstArr[i] == asciiChar) {
                        check = 0;
                        break;
                    }
                }
                if (check == 1) {
                    cprintf("%c", asciiChar);
                }
            }
            if (asciiChar == 'z') {
                flag = 2;
            }
        }
    }
    
    outportb(0x20, 0x20);
}

int main() {
    int counter = 1;
    

    oldfunc = getvect(0x09);

    setvect(0x09, nineHandle);
    
    cprintf("Enter symbols to delete from sentence (to exit press z) ");
    
    while (flag != 2) {
        if (flag == 1 && counter == 1) {
            cprintf("Enter your sentence (to exit press z) ");
            counter++;
        }
    }
    
    setvect(0x09, oldfunc);
    
    cprintf("\n\rProgram completed.\n\r");
    
    return 0;
}