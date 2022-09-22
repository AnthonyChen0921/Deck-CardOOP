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
    // deal 3 cards to each player until the deck is empty
    while (!deck.is_empty()){
        for (int i = 0; i < static_cast<int>(hands.size()); i++)
        {
            try{ 
                deck >> hands[i];
                deck >> hands[i];
                deck >> hands[i];  
            }
            catch (const exception &e){
                break;
            }
            // Problem: currently if the deck has 2 cards left, shifting 3 cards will be unsafe, cauing runtime error

            // Solution1: add size() function in the deck class to check the size of the deck
            //             -- result: the deck will have 2 cards leftover

            // Solution2: use try catch block to catch the runtime error and break the loop
            //             -- result: the deck will have all cards on player's hand but unevenly distributed

            // Solution3: deal with the number of the card before call deal() function, and make sure the number of the card is divisible by 3
            //             -- result: the deck will have 2 cards leftover, add helper function, complicated
        }
    }
    cout << "Dealing cards..." << endl;
}

/**
 * @brief printPlayersHand() function print out the hands of each player
 * 
 */
void PinochleGame::printPlayersHand(){
    for (int i = 0; i < static_cast<int>(hands.size()); i++)
    {
        cout << players[i] << "'s hand: " << endl;
        hands[i].print(cout, 4);
    }
}

/**
 * @brief play() function 
 * 
 * @return 
 */
int PinochleGame::play(){
    // shuffle the deck
    //deck.shuffle();
    // deal cards
    deal();
    // print out the hands of each player
    printPlayersHand();
    return 0;
}

