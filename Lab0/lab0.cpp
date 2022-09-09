/*
    lab0.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/


#include <iostream>
#include "Suit.h"
#include "Card_T.h"
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

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

    // test HoldEmDeck
    HoldEmDeck hd;
    hd.print(cout);

    return 0;
}


