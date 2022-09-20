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
#include "PinochleGame.h"
#include "Game.h"

using namespace std;


int main(int argc, const char *argv[]) {

    // LAB1
    PinochleDeck pd;
    HoldEmDeck hd;

    // test PinochleDeck Class shuffle function
    cout << "====================================================" << endl;
    cout << "Test PinochleDeck Class shuffle function" << endl;
    cout << "====================================================" << endl;
    pd.shuffle();
    cout << "Printing PinochleDeck pd after shuffle: " << endl;
    pd.print(cout, 4);

    // test HoldEmDeck Class shuffle function
    cout << "====================================================" << endl;
    cout << "Test HoldEmDeck Class shuffle function" << endl;
    cout << "====================================================" << endl;
    hd.shuffle();
    cout << "Printing HoldEmDeck hd after shuffle: " << endl;
    hd.print(cout, 4);

    // test cardset right shift operator>> using try catch block
    cout << "====================================================" << endl;
    cout << "Test cardset right shift operator>> using try catch block" << endl;
    cout << "====================================================" << endl;
    PinochleDeck cs;
    try {
        pd >> cs;
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    cout << "Printing PinochleDeck cs after right shift operator>>: " << endl;
    cs.print(cout, 4);
    cout << "Printing PinochleDeck pd after right shift operator>>: " << endl;
    pd.print(cout, 4);

    // test PinochleGame Class
    cout << "====================================================" << endl;
    cout << "Test PinochleGame Class" << endl;
    cout << "====================================================" << endl;
    // pass in the number of players and player name
    PinochleGame pg(argc, argv);
    pg.play();
    

 

    return 0;
}


