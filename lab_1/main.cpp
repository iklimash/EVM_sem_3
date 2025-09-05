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
    for (int i = 7; i >= 4; i--) 
    {
        cout << ((converter.bytes[6] >> i) & 1);
    }
    cout << " ";
    
    //  мантисс
    for (int i = 3; i >= 0; i--) {
        cout << ((converter.bytes[6] >> i) & 1);
    }
    for (int i = 5; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            cout << ((converter.bytes[i] >> j) & 1);
        }
    }
    cout << endl;
}
void changeBit(int& intValue, int amount, int* index, int* values)
{   
    for(int i = 0; i < amount; i++)
    {
        if(values[i] == 1)
        {
            intValue |= (1 << index[i]);
        } else
        {
            intValue &= ~(1 << index[i]);
        }
    }
}

void showMenu()
{
    cout << "1 - Convert integer on binary\n";
    cout << "2 - Convert double on binary\n";
    cout << "3 - Change bits\n";
    cout << "0 - exit\n";
    cout << ">";
}

int main()
{
    int intValue, type, amount;
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
        case 3:
            cout << "0 - integer\n";
            cout << "1 - double\n>";
            cin >> type;
            if (type == 0)
            {   
                cout << "Enter integer number\n>"; 
                cin >> intValue;
                int newIntValue = intValue;
                intConvertBinary(intValue);
                
                cout << "Enter amount values\n>";
                cin >> amount;
                int* index = new int[amount];
                int* values = new int[amount];
                for (int i = 0; i < amount; i++) 
                {
                    do
                    {
                        cout << "Enter index values for " << i+1 << " bit (0-31)\n>";
                        cin >> index[i];
                        if(index[i] < 0 || index[i] > 31)
                        {
                            cout << "Invalid index\n";
                        }
                    } while (index[i] < 0 || index[i] > 31);
                    do
                    {
                        cout << "Enter new values for " << i+1 << " (0 or 1)\n>";
                        cin >> values[i];
                        if(values[i] != 0 && values[i] != 1)
                        {
                            cout << "Invalid value\n";
                        }
                    } while (values[i] != 0 && values[i] != 1);
                    
                }
                changeBit(newIntValue, amount, index, values);
                intConvertBinary(intValue);
                intConvertBinary(newIntValue);

                delete[] index;
                delete[] values;
            } else
            {

            }

            break;
        case 0:
            return 0;
        
        default:
            break;
        }
    }  
}
