#include <iostream>
#include <cstdint>
using namespace std;


void intConvertBinary(int value)
{
    unsigned int u_value = value;
    int amountBit = sizeof(int) * 8;
    // знаковый бит
    cout << ((u_value >> (amountBit - 1)) & 1) << ' ';
    // остальные
    for (int i = amountBit - 2; i >= 0; i--)
    {
        cout << ((u_value >> i) & 1);
        if(i == amountBit - 1)
        {
            cout << ' ';
        }
    }
    cout << endl;
}
void doubleConvertBinary(double value) 
{
    union 
    {
        double d;
        unsigned char bytes[sizeof(double)];
    } converter;
    
    converter.d = value;
    
    cout << ((converter.bytes[7] >> 7) & 1) << " ";
    
    // порядок
    for (int i = 6; i >= 0; i--) 
    {
        cout << ((converter.bytes[7] >> i) & 1);
    }
    for (int i = 7; i >= 6; i--) 
    {
        cout << ((converter.bytes[6] >> i) & 1);
    }
    cout << " ";
    
    //  мантисс
    for (int i = 6; i >= 0; i--) 
    {
        for (int j = (i == 6 ? 5 : 7); j >= 0; j--) 
        {
            cout << ((converter.bytes[i] >> j) & 1);
        }
    }
    cout << endl;
}


void showMenu()
{
    cout << "1 - Convert integer on binary\n";
    cout << "2 - Convert double on binary\n";
    cout << "0 - exit\n";
    cout << ">";
}

int main()
{

    int intValue;
    double doubleValue;
    while (true)
    {
        showMenu();
        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:
            cout << "Enter a int number\n>"; cin >> intValue;
            intConvertBinary(intValue);
            break;
        case 2:
            cout << "Enter a double number\n>"; cin >> doubleValue;
            doubleConvertBinary(doubleValue);
            break;
        case 0:
            return 0;
        
        default:
            break;
        }
    }  
}
