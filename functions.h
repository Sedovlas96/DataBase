#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct CardOfBuyer
{
    char surname[ 30 ];
    char firstname[ 20 ];
    char amountOfPurchases[ 15 ];
    char numberOfPurchases[ 10 ];
};

void inputNewBase( CardOfBuyer *Array, int quantity );
void showBase( CardOfBuyer *Array, int quantity );
void getMenu ( int key, CardOfBuyer *Array, int quantity  );
void changeBuyer( CardOfBuyer *Array, int quantity );
void sortingFields( CardOfBuyer *Array, int quantity );


#endif // FUNCTIONS_H
