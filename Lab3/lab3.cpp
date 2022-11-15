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
    // game if initialized to nullptr
    shared_ptr<Game> game;
    // check the game name
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

    // checks that the command line arguments numbers
    // consist of either "Pinochle" followed by exactly four player names (Pinochle player1 player2 player3 player4)
    // or "HoldEm" followed by between two and nine player names (HoldEm player2 - player9)
    if (argc < arrayIndex::minArg || argc > arrayIndex::maxArg) {
        return usageMessage(program_name);
    }
    // checks that the game name is either "Pinochle" or "HoldEm"
    else if (string(game_name) != "Pinochle" && string(game_name) != "HoldEm") {
        cout << "Invalid Gamename" << endl;
        return usageMessage(program_name);
    }
    // Pinochle, check given players number is exactly 4
    else if (string(game_name) == "Pinochle" && argc != PinochleGameGameRules::numPlayerPinochle) {
        cout << "Invalid number of players in Pinochle, must have exactly 4 players." << endl;
        cout << "For example: Pinochle player1 player2 player3 player4" << endl;
        return usageMessage(program_name);
    }
    // HoldEm, check given players number is bewteen 2 - 9
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
        // game is a null pointer
        cout << "Game is not created" << endl;
        return message::GAME_NOT_CREATED;
    }

    // return 0 if the game is successfully created and played
    return message::SUCCESS;
}


