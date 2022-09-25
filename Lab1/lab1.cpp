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
#include <memory>

using namespace std;



/**
 * @brief create() function create a game based on the game name
 * 
 * @param argc nums of arguments
 * @param argv arguments
 * @return shared_ptr<Game> 
 */
shared_ptr<Game> create(int argc, const char *argv[]) {
    shared_ptr<Game> game;
    if (string(argv[1]) == "Pinochle") {
        game = make_shared<PinochleGame>(argc, argv);
    }
    else if (string(argv[1]) == "HoldEm") {
        game = make_shared<HoldEmGame>(argc, argv);
    }
    return game;
}




int main(int argc, const char *argv[]) {

    // program name
    const char *program_name = argv[0];

    // game name
    const char *game_name = argv[1];

    // checks that the command line arguments
    // consist of either "Pinochle" followed by exactly four player names (Pinochle player1 player2 player3 player4)
    // or "HoldEm" followed by between two and nine player names (HoldEm player2 - player9)
    if (argc < arrayIndex::minArg || argc > arrayIndex::maxArg) {
        return usageMessage(program_name);
    }
    else if (string(game_name) != "Pinochle" && string(game_name) != "HoldEm") {
        cout << "Invalid Gamename" << endl;
        return usageMessage(program_name);
    }
    else if (string(game_name) == "Pinochle" && argc != PinochleGameGameRules::numPlayerPinochle) {
        cout << "Invalid number of players in Pinochle, must have exactly 4 players." << endl;
        cout << "For example: Pinochle player1 player2 player3 player4" << endl;
        return usageMessage(program_name);
    }
    else if (string(game_name) == "HoldEm" && (argc < HoldEmGameRules::minPlayerHoldEm || argc > HoldEmGameRules::maxPlayerHoldEm)) {
        cout << "Invalid number of players in HoldEm, must have between 2 and 9 players." << endl;
        cout << "For example: HoldEm player1 player2" << endl;
        return usageMessage(program_name);
    }
    // use shtd_ptr to create a game
    shared_ptr<Game> game = make_shared<PinochleGame>(argc, argv);
    // play the game
    game->play();
 
    // if(game_name == nullptr){
    //     cout << "No game name is provided" << endl;
    //     usageMessage(program_name);
    //     return message::no_game_name;
    // }
    // else if(strcmp(game_name, "Pinochle") == 0){
    //     // test PinochleGame Class
    //     cout << "====================================================" << endl;
    //     cout << "=              Test PinochleGame Class             ="  << endl;
    //     cout << "====================================================" << endl;
    //     // pass in the number of players and player name
    //     // try catch block to catch invalid_argument exception
    //     try {
    //         PinochleGame pg(argc, argv);
    //         pg.play();
    //     }
    //     catch (const invalid_argument& e) {
    //         // if caught not enough players, print out the usage message
    //         if (e.what() == string("Not enough players")) {
    //             usageMessage(program_name);
    //         }
    //         else {
    //             cout << e.what() << endl;
    //         }
    //     }
    // }
    // else if(strcmp(game_name, "Holdem") == 0){
    //     // test HoldEmGame Class
    //     cout << "====================================================" << endl;
    //     cout << "=              Test HoldEmGame Class               ="  << endl;
    //     cout << "====================================================" << endl;
    //     // pass in the number of players and player name
    //     // try catch block to catch invalid_argument exception
    //     try {
    //         HoldEmGame hg(argc, argv);
    //         hg.play();
    //     }
    //     catch (const invalid_argument& e) {
    //         // if caught not enough players, print out the usage message
    //         if (e.what() == string("Not enough players")) {
    //             usageMessage(program_name);
    //         }
    //         else {
    //             cout << e.what() << endl;
    //         }
    //     }
    // }
    // else{
    //     cout << "Invalid game name" << endl;
    //     usageMessage(program_name);
    //     return message::invalid_game_name;
    // }

    return message::success;
}


