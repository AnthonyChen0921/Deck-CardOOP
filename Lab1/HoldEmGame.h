/*
    HoldEmGame.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 24, 2022
*/

#pragma once
#include "Deck.h"
#include "Game.h"
#include "HoldEmDeck.h"
#include "function.h"



enum class HoldEmState {
    preflop,
    flop,
    turn,
    river,
    undefined
};

class HoldEmGame : public Game {
protected:
    // HoldEmState enum
    HoldEmState state;
    // HoldEmDeck
    HoldEmDeck deck;
    // hands of the players
    std::vector<CardSet<HoldEmRank, Suit> > hands;
    // store common board cards
    CardSet<HoldEmRank, Suit> board;
    // virtual deal()
    virtual void deal();
public:
    // constructor
    HoldEmGame(int argc, const char *argv[]);
    // virtual play()
    virtual int play();
    // helper functions
    // print out the hands of each player
    void printPlayersHand();
    // collect the cards from the players to the deck
    void collectCardsFromPlayer();
    // collect the cards from the board to the deck
    void collectCardsFromBoard();
    // printout board cards
    void printBoard(std::string s);
};