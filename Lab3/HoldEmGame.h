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
#include <string>
#include <unordered_map>

//Declare an enum class HoldEmHandRank enumerated type
enum class HoldEmHandRank{
    xhigh, 
    pair,
    twopair,
    threeofakind, 
    straight, 
    flush, 
    fullhouse, 
    fourofakind, 
    straightflush, 
    undefined
};

enum class HoldEmState {
    preflop,
    flop,
    turn,
    river,
    undefined
};


enum class HoldEmAction {
    check=0,
    fold,
    call,
    raise
};


static const int HoldEmGameInitialScore = 60;

class HoldEmGame : public Game {
    //nested struct to your HoldEmGame class
protected:
    // HoldEmState enum
    HoldEmState state;
    // HoldEmDeck
    HoldEmDeck deck;
    // hands of the players
    std::vector<CardSet<HoldEmRank, Suit> > hands;
    std::vector<CardSet<HoldEmRank, Suit> > bestCardCombination;

    int bigblindInd=1;
    int smallblindInd=0;

    //record if player fold
    std::vector<bool> ifFold;
    std::vector<bool> ifAllIn;
    // store common board cards
    CardSet<HoldEmRank, Suit> board;
    //score member
    std::vector<int> scores;
    std::vector<int> chipsInPot;
    std::vector<int> chipsCurrentRound;
    std::unordered_map<std::string,int> seats; //store the index of each player
    // virtual deal()
    virtual void deal();
public:
    // constructor
    HoldEmGame(int argc, const char *argv[]);
    // virtual destructor
    virtual ~HoldEmGame() {}
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
    //compare the cardset after flop
    void evaluate();

    //bet
    void bet();
    //reset scores and chips
    void resetChips();
    HoldEmAction action(int PlayerInd);

    //delete player whose score is 0
    void kickplayer(int i);
    //nested struct 
    class HoldEmPlayer{
        public:
        friend bool operator<(const HoldEmPlayer &p1, const HoldEmPlayer &p2);
        std::string name;
        CardSet<HoldEmRank, Suit> hand;
        HoldEmHandRank rank;        
        HoldEmPlayer();
        HoldEmPlayer(std::string n, CardSet<HoldEmRank, Suit> c, HoldEmHandRank r);
    };
    std::string winnerName;

private:
    HoldEmHandRank holdem_hand_evaluation (const CardSet<HoldEmRank, Suit> &cs);
};

