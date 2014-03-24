#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"


using namespace std;


int main()
{
    CardOfBuyer *Array;
    int quantityOfBuyers = 20;
    Array = new CardOfBuyer[ quantityOfBuyers ];
    int key = 0;
    do
    {
        cout << endl;
        cout << " Press key: " << endl;
        cout << " ~1~ - For enter new base " << endl;
        cout << " ~2~ - For adding Buyer " << endl;
        cout << " ~3~ - For deleting Buyer " << endl;
        cout << " ~4~ - For changing information about Buyer " << endl;
        cout << " ~5~ - For open the base " << endl;
        cout << " ~6~ - For show the base " << endl;
        cout << " ~7~ - For sorting " << endl;
        cout << " ~0~ - For exit " << endl;
        cin >> key;
        if( key )
        {
            getMenu( key, Array, quantityOfBuyers );
        }
    }
    while( key );

    delete[] Array;

    return 0;
}
