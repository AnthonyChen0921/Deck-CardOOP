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
    size_t numCards = 3 * players.size();
    // deal 3 cards to each player until the deck is empty
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
        cout << endl;
    }
}

/**
 * @brief collectCards() function collect the cards from the players to the deck
 * 
 */
void PinochleGame::collectCards(){
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        deck.collect(hands[i]);
    }
}

/**
 * @brief askEndGame() function ask the player want to end the game or not
 * 
 * @return int return 1 if want to end
 */
int PinochleGame::askEndGame(){
    cout << "Do you want to end the game? (y/n)" << endl;
    string input;
    cin >> input;
    if (input == "y"){
        return 1;
    }
    return 0;
}

/**
 * @brief play() function 
 * 
 * @return 
 */
int PinochleGame::play(){
    // repeatly call shuffle() and deal()
    // printout the hands of each player by calling printPlayersHand()
    // use Deck's collect() function to repeatly move the cards back out of each player's hand into the deck
    // print a string to the standard output stream that asks the user whether or not to end the game
    // read in a string from the standard input stream, 
    // if the string is "y" or "Y", then return 0, otherwise repeat the loop
    while (true)
    {
        // shuffle the deck
        deck.shuffle();
        // deal the cards
        deal();
        // print out the hands of each player
        printPlayersHand();
        // collect the cards from the players to the deck
        collectCards();
        // ask the player want to end the game or not
        if (askEndGame()){
            return 0;
        }
    }
}

