/*
    HoldEmGame.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 24, 2022
*/

#include "HoldEmGame.h"

using namespace std;

/**
 * @brief constructor: initialize the game and create cards to each player's hand
 * 
 * @param argc the number of arguments
 * @param argv the arguments
 */
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop) {
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        hands.push_back(CardSet<HoldEmRank, Suit>());
    }
}



/**
 * @brief deal() function: deal cards to each player's hand
 *         - deal cards to each player
 *         - increase the state to next state of the game after each round
 */
void HoldEmGame::deal() {
    switch (state) {
        // HoldEmState::preflop deal one card from the deck to each player's hand, 
        // and then deal a second card from the deck to each player's hand, 
        // and then increase the state to the next higher value
        case HoldEmState::preflop:
            for (int i = 0; i < static_cast<int>(players.size()); i++) {
                deck >> hands[i];
            }
            for (int i = 0; i < static_cast<int>(players.size()); i++) {
                deck >> hands[i];
            }
            state = HoldEmState::flop;
            break;
        // HoldEmState::flop deal three cards from the deck to the board
        case HoldEmState::flop:
            for (int i = 0; i < HoldEmGameRules::num_of_flop_cards; i++) {
                deck >> board;
            }
            state = HoldEmState::turn;
            break;
        // HoldEmState::turn deal one card from the deck to the board
        case HoldEmState::turn:
            deck >> board;
            state = HoldEmState::river;
            break;
        // HoldEmState::river deal one card from the deck to the board
        case HoldEmState::river:
            deck >> board;
            state = HoldEmState::undefined;
            break;
        // HoldEmState::undefined do nothing
        case HoldEmState::undefined:
            break;
    }
}

/**
 * @brief printPlayersHand() function print out the hands of each player
 * 
 */
void HoldEmGame::printPlayersHand(){
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
void HoldEmGame::collectCardsFromPlayer() {
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        deck.collect(hands[i]);
    }
}

/**
 * @brief collectCardsFromBoard() function collect the cards from the board to the deck
 * 
 */
void HoldEmGame::collectCardsFromBoard() {
    deck.collect(board);
}

/**
 * @brief printBoard() function printout board cards
 * 
 */
void HoldEmGame::printBoard(string s) {
    cout << s << endl;
    board.print(cout, GameRules::print_format_5);
    cout << endl;
}
 


/**
 * @brief play function: play the game
 * 
 * @return int possible return values: 
 *              message::end_game
 */
int HoldEmGame::play() {
    // repeat the following steps until the game is over:
    while (true) {
        // shuffle the deck
        deck.shuffle();
        // reset state
        state = HoldEmState::preflop;

        // deal cards to each player's hand
        deal();
        printPlayersHand();
        
        // deal cards to the board in 3 rounds
        deal();
        printBoard("Flop: ");

        deal();
        printBoard("Turn: ");
        
        deal();
        printBoard("River: ");

        // collect cards
        collectCardsFromPlayer();
        collectCardsFromBoard();

        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
    }
}
