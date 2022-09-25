/*
    PinochleGame.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 19, 2022
*/

#include "PinochleGame.h"

using namespace std;

/**
 * @brief constructor pass argc and argv to base class Game
 * 
 * @param argc the number of players
 * @param argv the name of players
 * 
 * @note A tutorial on how to call base class constructor: 
 * https://stackoverflow.com/questions/15777635/c-calling-base-class-constructors
 */
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv){
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        hands.push_back(CardSet<PinochleRank, Suit>());
    }
}

/**
 * @brief deal() function repeatedly shift cards to each player's hand, 3 at a time
 *        until the deck is empty
 * 
 */
void PinochleGame::deal(){
    // calculate number of cards to deal in a round
    size_t numCards = PinochleGameGameRules::packet_of_cards * players.size();
    // deal 3 cards to each player until the deck is empty
    cout << "Dealing cards..." << endl;
    while (deck.getSize() >= numCards){
        for (int i = 0; i < static_cast<int>(hands.size()); i++)
        {
            deck >> hands[i];
            deck >> hands[i];
            deck >> hands[i];  
            // Problem: currently if the deck has 2 cards left, shifting 3 cards will be unsafe, cauing runtime error

            // Solution1: add size() function in the deck class to check the size of the deck
            //             -- result: the deck will have 2 cards leftover
            // Accpted

            // Solution2: use try catch block to catch the runtime error and break the loop
            //             -- result: the deck will have all cards on player's hand but unevenly distributed
            // Infeasible, rejected

            // Solution3: deal with the number of the card before call deal() function, and make sure the number of the card is divisible by 3
            //             -- result: the deck will have 2 cards leftover, add helper function, complicated
            // Feasible, rejected
        }
    }
}

/**
 * @brief printPlayersHand() function print out the hands of each player
 * 
 */
void PinochleGame::printPlayersHand(){
    for (int i = 0; i < static_cast<int>(hands.size()); i++)
    {
        cout << players[i] << "'s hand: " << endl;
        hands[i].print(cout, GameRules::print_format_4);
        cout << endl;
    }
}

/**
 * @brief collectCards() function collect the cards from the players to the deck
 * 
 */
void PinochleGame::collectCardsFromPlayer(){
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        deck.collect(hands[i]);
    }
}



/**
 * @brief play() function 
 * 
 * @return possible return values: 
 *              message::end_game
 *              
 */
int PinochleGame::play(){
    while (true)
    {
        // shuffle the deck
        deck.shuffle();
        // deal the cards
        deal();
        // print out the hands of each player
        printPlayersHand();
        // collect the cards from the players to the deck
        collectCardsFromPlayer();
        // ask the player want to end the game or not
        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
    }
}

