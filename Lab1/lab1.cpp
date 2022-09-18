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
    // test Suit's shift operator<<
    cout << "============================" << endl;
    cout << "Test Suit's shift operator<<" << endl;
    cout << "============================" << endl;
    cout << "Suit::clubs: " << Suit::clubs << endl; 
    cout << "Suit::diamonds: " << Suit::diamonds << endl;
    cout << "Suit::hearts: " << Suit::hearts << endl;
    cout << "Suit::spades: " << Suit::spades << endl;
    cout << "Suit::undefined: " << Suit::undefined << endl;

    // test Suit's prefix increment operator++
    cout << "=======================================" << endl;
    cout << "Test Suit's prefix increment operator++" << endl;
    cout << "=======================================" << endl;
    Suit s = Suit::clubs;
    cout << "Suit is initialized to: " << s << endl;
    cout << "Prefix increment ++s return: " << ++s << endl;

    // test Card
    Card<Rank, Suit> c(Rank::ace, Suit::spades);

    // test PinochleDeck's shift operator<<
    cout << "=========================================" << endl;
    cout << "Test PinochleDeck's rank shift operator<<" << endl;
    cout << "=========================================" << endl;
    cout << "PinochleRank::nine: " << PinochleRank::nine << endl;
    cout << "PinochleRank::jack: " << PinochleRank::jack << endl;
    cout << "PinochleRank::queen: " << PinochleRank::queen << endl;
    cout << "PinochleRank::king: " << PinochleRank::king << endl;
    cout << "PinochleRank::undefined: " << PinochleRank::undefined << endl;

    // test HoldEmDeck's shift operator<<
    cout << "=========================================" << endl;
    cout << "Test HoldEmDeck's rank shift operator<<" << endl;
    cout << "=========================================" << endl;
    cout << "HoldEmRank::two: " << HoldEmRank::two << endl;
    cout << "HoldEmRank::three: " << HoldEmRank::three << endl;
    cout << "HoldEmRank::four: " << HoldEmRank::four << endl;
    cout << "HoldEmRank::five: " << HoldEmRank::five << endl;
    cout << "HoldEmRank::undefined: " << HoldEmRank::undefined << endl;

    // test PinochleDeck's prefix increment operator++
    cout << "====================================================" << endl;
    cout << "Test PinochleDeck's rank prefix increment operator++" << endl;
    cout << "====================================================" << endl;
    PinochleRank r = PinochleRank::nine;
    cout << "PinochleRank is initialized to: " << r << endl;
    cout << "Prefix increment ++r return: " << ++r << endl;

    // test HoldEmDeck's prefix increment operator++
    cout << "====================================================" << endl;
    cout << "Test HoldEmDeck's rank prefix increment operator++" << endl;
    cout << "====================================================" << endl;
    HoldEmRank h = HoldEmRank::two;
    cout << "HoldEmRank is initialized to: " << h << endl;
    cout << "Prefix increment ++h return: " << ++h << endl;

    // test PinochleDeck Class default constructor and print function
    cout << "====================================================" << endl;
    cout << "Test PinochleDeck Class default constructor and print function" << endl;
    cout << "====================================================" << endl;
    PinochleDeck pd;
    cout << "Printing PinochleDeck pd: ";
    pd.print(cout, 4);
        
    // test HoldEmDeck Class default constructor and print function
    cout << "====================================================" << endl;
    cout << "Test HoldEmDeck Class default constructor and print function" << endl;
    cout << "====================================================" << endl;
    HoldEmDeck hd;
    cout << "Printing HoldEmDeck hd: ";
    hd.print(cout, 4);

 

    return 0;
}


