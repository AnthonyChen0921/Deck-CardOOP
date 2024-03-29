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
#include <algorithm>
#include <unordered_map>

//Declare a public enum class PinochleMelds enumerated type with the following values: dix, marriage, royal_marriage, flush, nob, and run.
enum class PinochleMelds {
    dix, offsuitmarriage, fortyjacks, pinochle,
    insuitmarriage, sixtyqueens, eightykings, 
    hundredaces, insuitrun, doublepinochle, 
    fourhundredjacks, sixhundredqueens, 
    eighthundredkings, thousandaces, insuitdoublerun
};


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
    // print out the melds of each player
    void printPlayersMelds();
    // bid()
    int bid(std::vector<unsigned int> &bids, unsigned int &contract);
    // playTricks()
    void playTricks(std::vector<unsigned int> &bids, std::vector<unsigned int> &scores, unsigned int &contract);
    static std::unordered_map<PinochleMelds,int> points;
private:  
    Suit trump_suit;
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &cs, std::vector<PinochleMelds> &melds);
    void suit_dependent_evaluation(const CardSet<PinochleRank, Suit> &cs, std::vector<PinochleMelds> &melds, Suit s);
    unsigned int getCardPoints(const CardSet<PinochleRank, Suit> &hand);

    // helper function
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> convertCardSetToMap(const CardSet<PinochleRank, Suit> &cs);
    PinochleRank findHighestRank(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map);
    PinochleRank findLowestRank(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map);
    PinochleRank findHighestRankwS(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, Suit &suit);
    PinochleRank findHighestRankwS(std::vector<Card<PinochleRank, Suit>> trick_cards_vector, Suit lead_suit);
    PinochleRank findLowestRankwS(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, Suit &suit);
    Suit findHighestSuit(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, PinochleRank &highest_rank);
    Suit findLowestSuit(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, PinochleRank &lowest_rank);


    // more helper functions
    int findFirstPlayer(std::vector<unsigned int> &bids, unsigned int &contract);
    bool checkTrumpPlayed(std::vector<Card<PinochleRank, Suit>> trick_cards_vector, Suit trump_suit);
    void printMap(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map);
    void PlayThisCard(PinochleRank& rank, Suit& suit, CardSet<PinochleRank, Suit>& trick_thisRound, std::unordered_map<PinochleRank,std::unordered_map<Suit,int>>& map, int i);
    void calculateScore(int j, int i, int& turn, std::vector<unsigned int> &scores, std::vector<Card<PinochleRank, Suit>>& trick_cards_vector);
};

