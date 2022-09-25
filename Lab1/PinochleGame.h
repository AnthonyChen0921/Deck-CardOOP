/*
    PinochleGame.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 19, 2022
*/

#pragma once
#include "Game.h"
#include "PinochleDeck.h"
#include "function.h"
#include <vector>

class PinochleGame : public Game
{
protected:
    // member variable
    //  PinochleDeck
    PinochleDeck deck;
    // hands of the players
    std::vector<CardSet<PinochleRank, Suit> > hands;
    // virtual deal()
    virtual void deal();

public:
    // constructor
    PinochleGame(int argc, const char *argv[]);
    // virtual destructor
    virtual ~PinochleGame() {}
    // virtual play()
    virtual int play();

    /** helpers **/
    // print out the hands of each player
    void printPlayersHand();
    // collect the cards from the players to the deck
    void collectCardsFromPlayer();
};

