#include "functions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <iomanip>


using namespace std;

void inputBase( CardOfBuyer *Array, int firstIndex, int lastIndex )
{
    cin.ignore(1,'\n');
    for( int i = firstIndex; i < lastIndex; ++i )
    {
        cout << "Enter surname:\t";
        cin.getline( Array[ i ].surname, 30, '\n' );

        cout << "Enter first name:\t";
        cin.getline( Array[ i ].firstname, 20, '\n' );

        cout << "Enter Amount Of Purchases:\t";
        cin.getline( Array[ i ].amountOfPurchases, 15, '\n' );

        cout << "Enter Number Of Purchases:\t";
        cin.getline( Array[ i ].numberOfPurchases, 15, '\n' );
    }
}



void getMenu ( int key, CardOfBuyer *Array, int quantity  )
{
    switch( key )
    {
    case 1:
        inputNewBase( Array, quantity );
        break;
    case 2:
    {
        int index;
        system( " cls " );
        cout << " Enter the Index Of the Added Buyer ";
        cin >> index;
        inputBase( Array, index , index + 1 );
        ++quantity;
        fstream dataOut( "data.txt", ios::out|ios::binary|ios::trunc );
        dataOut.write(( char *)Array, quantity * sizeof( CardOfBuyer ));
        dataOut.close();
    }
    break;
    case 3:
    {
        int indexOfDeleted;
        cout << " Enter the Index Of the Deleted Buyer : ";
        cin >> indexOfDeleted;
        Array[ indexOfDeleted ] = Array[ quantity - 1 ];
        --quantity;
        fstream dataOut( "data.txt", ios::out|ios::binary|ios::trunc );
        dataOut.write(( char *)Array, quantity * sizeof( CardOfBuyer ));
        dataOut.close();
    }
    break;
    case 4:
        changeBuyer( Array, quantity );
        break;
    case 5:
    {
        fstream dataOut( "data.txt", ios::in|ios::binary );
        dataOut.read(( char *)Array, quantity * sizeof( CardOfBuyer ));
        dataOut.close();
    }
    break;
    case 6:
        showBase( Array, quantity );
        break;
    case 7:
        sortingFields( Array, quantity );
        break;
    }
}

void inputNewBase( CardOfBuyer *Array, int quantity )
{
    system( " cls " );
    fstream dataOut( "data.txt", ios::out|ios::binary|ios::trunc );
    dataOut.write(( char *)Array, quantity * sizeof( CardOfBuyer ));
    dataOut.close();
    inputBase( Array, 0, quantity );
    system( " pause " );
}


void changeBuyer( CardOfBuyer *Array, int quantity )
{
    cin.ignore( 1, '\n' );
    int indexOfChanged;
    cout << " Enter the Index Of the Changed Buyer: ";
    cin >> indexOfChanged;

    cout << " Change The Surname:  ";
    cin.getline( Array[ indexOfChanged ].surname, 30, '\n' );

    cout << " Change The Firstname: ";
    cin.getline( Array[ indexOfChanged ].firstname, 20, '\n' );

    cout << " Change Amount Of Purchases: ";
    cin.getline( Array[ indexOfChanged ].amountOfPurchases, 15, '\n' );

    cout << " Change Number Of Purchases: ";
    cin.getline( Array[ indexOfChanged ].numberOfPurchases, 20, '\n' );

    fstream dataOut( " data.txt ", ios::out|ios::binary|ios::trunc );
    dataOut.write(( char *)Array, quantity * sizeof( CardOfBuyer ));
    dataOut.close();
}

void showBase( CardOfBuyer *Array, int quantity )
{
    system( " cls " );
    cout << " Surname       Firstname     Amount     Quantity " << endl;
    for( int i = 0; i < quantity; ++i )
    {
        cout << endl;
        cout.setf( ios::fixed );
        cout << setw( 17 ) << Array[ i ].surname;
        cout << setw( 13 ) << Array[ i ].firstname;
        cout << setw( 10 ) << Array[ i ].amountOfPurchases;
        cout << setw( 10 ) << Array[ i ].numberOfPurchases;
        cout << endl;
    }
}

int sortingBySurname( CardOfBuyer ArrayOne, CardOfBuyer ArrayTwo )
{
    return strcmp( ArrayOne.surname, ArrayTwo.surname );
}

int sortingByFirstname( CardOfBuyer ArrayOne, CardOfBuyer ArrayTwo )
{
    return strcmp( ArrayOne.firstname, ArrayTwo.firstname );
}

int sortingByAmount( CardOfBuyer ArrayOne, CardOfBuyer ArrayTwo )
{
    return strcmp( ArrayOne.amountOfPurchases, ArrayTwo.amountOfPurchases );
}

int sortingByNumbers( CardOfBuyer ArrayOne, CardOfBuyer ArrayTwo )
{
    return strcmp( ArrayOne.numberOfPurchases, ArrayTwo.numberOfPurchases );
}

void mergeParts( int *Array, int firstIndexOfArrayOne, int lastIndexOfArrayOne, int firstIndexOfArrayTwo, int lastIndexOfArrayTwo, int ( *fptr )( CardOfBuyer, CardOfBuyer ))
{
    int firstIndexOfResultArray = firstIndexOfArrayOne, lastIndexOfResultArray = lastIndexOfArrayTwo;
    int indexOfSortingArray = 0;
    CardOfBuyer *sortingArray;
    sortingArray = new CardOfBuyer [ lastIndexOfArrayTwo - firstIndexOfArrayOne + 1 ] ;
    while( ( firstIndexOfArrayOne <= lastIndexOfArrayOne) && ( firstIndexOfArrayTwo <= lastIndexOfArrayTwo ) )
    {
            if((( *fptr )( Array[ firstIndexOfArrayOne ], Array[ firstIndexOfArrayTwo ] )) < 0)
            {
                sortingArray[ indexOfSortingArray ] = Array[ firstIndexOfArrayOne ];
                ++ firstIndexOfArrayOne;
            }
            else
            {
                sortingArray[ indexOfSortingArray ] = Array[ firstIndexOfArrayTwo ];
                ++ firstIndexOfArrayTwo;
            }
        }
        ++ indexOfSortingArray;
    }
    if( firstIndexOfArrayOne <= lastIndexOfArrayOne )
    {
        for( int i = firstIndexOfArrayOne; i <= lastIndexOfArrayOne; ++i )
        {
            sortingArray[ indexOfSortingArray ] = Array[ i ];
            ++ indexOfSortingArray;
        }
    }
    else
    {
        for( int j = firstIndexOfArrayTwo; j <= lastIndexOfArrayTwo; ++j )
        {
            sortingArray[ indexOfSortingArray ] = Array[ j ];
            ++ indexOfSortingArray;
        }
    }
    indexOfSortingArray = 0;
    for( int k = firstIndexOfResultArray; k <= lastIndexOfResultArray; ++k )
    {
        Array [ k ] = sortingArray[ indexOfSortingArray ];
        ++indexOfSortingArray;
    }
    delete [] sortingArray;
    sortingArray = 0;

}


void mergeSorting( CardOfBuyer Array, int firstIndex, int lastIndex, int ( *fptr )( CardOfBuyer, CardOfBuyer ), int var )
{
    middle = ( firstIndex + lastIndex ) / 2;
    if( firstIndex < lastIndex )
    {
        mergeSorting( Array, firstIndex, middle, ( *fptr ), var );
        mergeSorting( Array, middle + 1, lastIndex, ( *fptr ), var );
        mergeParts( Array, firstIndex, lastIndex, ( *fptr ) );
    }
}

void sortingFields( CardOfBuyer *Array, int quantity )
{
    typedef int ( *pointers )( CardOfBuyer, CardOfBuyer );
    pointers *ArrayOfPointers;
    ArrayOfPointers = new pointers[ 4 ];
    ArrayOfPointers[ 0 ] = sortingBySurname;
    ArrayOfPointers[ 1 ] = sortingByFirstname;
    ArrayOfPointers[ 2 ] = sortingByAmount;
    ArrayOfPointers[ 3 ] = sortingByNumbers;
    cout << " Press key: " << endl;
    cout << " ~1~ - For sorting A->Z by surname ";
    endl;
    cout << " ~2~ - For sorting Z->A by surname ";
    endl;
    cout << " ~3~ - For sorting A->Z by firstname ";
    endl;
    cout << " ~4~ - For sorting Z->A by firstname ";
    endl;
    cout << " ~5~ - For sorting A->Z by Amount ";
    endl;
    cout << " ~6~ - For sorting Z->A by Amount ";
    endl;
    cout << " ~7~ - For sorting A->Z by Numbers ";
    endl;
    cout << " ~8~ - For sorting Z->A by Numbers ";
    endl;
    int key;
    cin >> key;
    switch( key
{
case 1:
    mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 0 ], -1 );
        break;
    case 2:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 0 ], 1 );
        break;
    case 3:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 1 ], -1 );
        break;
    case 4:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 1 ], 1 );
        break;
    case 5:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 2 ], -1 );
        break;
    case 6:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 2 ], 1 );
        break;
    case 7:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 3 ], -1 );
        break;
    case 8:
        mergeSorting( Array, 0, quantity - 1, ArrayOfPointers[ 3 ], 1 );
        break;
    }
    delete []ArrayOfPointers;
}
