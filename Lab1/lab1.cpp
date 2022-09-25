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

    // print game logo
    printLogo(string(game_name));
    
    // call create() function to create/play a game
    shared_ptr<Game> game = create(argc, argv);
    if(game){
        game->play();
    }
    else{
        cout << "Game is not created" << endl;
        return message::GAME_NOT_CREATED;
    }

    return message::SUCCESS;
}


