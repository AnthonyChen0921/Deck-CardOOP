/*
    lab0.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Aug 31, 2022
*/


#include <iostream>
#include "Suit.h"
#include "Card_T.h"
#include <ostream>

using namespace std;

int main() {
    // test Stuit
    Suit s = Suit::spades;
    cout << s << endl;
    ++s;
    cout << s << endl;

    // test Card
    Card<Rank, Suit> c(Rank::ace, Suit::spades);
    cout << c << endl;

    return 0;
}