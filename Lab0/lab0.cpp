/*
    lab0.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Aug 31, 2022
*/


#include <iostream>
#include "Suit.h"
#include "Card_T.h"
#include "PinochleDeck.h"

using namespace std;


int main() {
    // test Stuit
    Suit s = Suit::clubs;
    cout << s << endl;
    ++s;
    cout << s << endl;

    // test Card
    Card<Rank, Suit> c(Rank::ace, Suit::spades);

    // test PinochleDeck
    PinochleDeck pd;
    pd.print(cout);

    return 0;
}


