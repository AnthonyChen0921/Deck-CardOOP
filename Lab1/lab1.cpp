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
#include "function.h"
#include "HoldEmGame.h"

using namespace std;


int main(int argc, const char *argv[]) {

    // program name
    const char *program_name = argv[0];

    // game name
    const char *game_name = argv[1];

    /*
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
    */

 
    if(game_name == nullptr){
        cout << "No game name is provided" << endl;
        return 1;
    }
    else if(strcmp(game_name, "pinochle") == 0){
        // test PinochleGame Class
        cout << "====================================================" << endl;
        cout << "               Test PinochleGame Class              "  << endl;
        cout << "====================================================" << endl;
        // pass in the number of players and player name
        // try catch block to catch invalid_argument exception
        try {
            PinochleGame pg(argc, argv);
            pg.play();
        }
        catch (const invalid_argument& e) {
            // if caught not enough players, print out the usage message
            if (e.what() == string("Not enough players")) {
                usageMessage(program_name);
            }
            else {
                cout << e.what() << endl;
            }
        }
    }
    else if(strcmp(game_name, "holdem") == 0){
        // test HoldEmGame Class
        cout << "====================================================" << endl;
        cout << "               Test HoldEmGame Class                "  << endl;
        cout << "====================================================" << endl;
        // pass in the number of players and player name
        // try catch block to catch invalid_argument exception
        try {
            HoldEmGame hg(argc, argv);
            hg.play();
        }
        catch (const invalid_argument& e) {
            // if caught not enough players, print out the usage message
            if (e.what() == string("Not enough players")) {
                usageMessage(program_name);
            }
            else {
                cout << e.what() << endl;
            }
        }
    }
    else{
        cout << "Invalid game name" << endl;
        return 1;
    }


 

    return 0;
}


