/*
    HoldEmDeck.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 2, 2022
*/

#include "HoldEmDeck.h"
#include <iostream>

using namespace std;

/**
 * @brief shift operator<<
 * @param os
 * @param const HoldEmRank
 * @return os
 */
ostream &operator<<(ostream &os, const HoldEmRank &rank){
    /*
        "2" for two, "3" for three, "4" for four, "5" for five, "6" for six, 
        "7" for seven, "8" for eight, "9" for nine, "T" for ten, "J" for jack, 
        "Q" for queen, "K" for king, "A" for ace, or "?" for undefined
    */
    switch (rank)
    {
    case HoldEmRank::two:
        os << "2";
        break;
    case HoldEmRank::three:
        os << "3";
        break;
    case HoldEmRank::four:
        os << "4";
        break;
    case HoldEmRank::five:
        os << "5";
        break;
    case HoldEmRank::six:
        os << "6";
        break;
    case HoldEmRank::seven:
        os << "7";
        break;
    case HoldEmRank::eight:
        os << "8";
        break;
    case HoldEmRank::nine:
        os << "9";
        break;
    case HoldEmRank::ten:
        os << "10";
        break;
    case HoldEmRank::jack:
        os << "J";
        break;
    case HoldEmRank::queen:
        os << "Q";
        break;
    case HoldEmRank::king:
        os << "K";
        break;
    case HoldEmRank::ace:
        os << "A";
        break;
    case HoldEmRank::undefined:
        os << "?";
        break;
    }
    return os;
}


/**
 * @brief prefix operator++
 * 
 * @return PinochleRanks& 
 */
HoldEmRank &operator++(HoldEmRank &rank){
    // if rank is not undefined, increment it to the next rank
    if (rank != HoldEmRank::undefined)
    {
        rank = static_cast<HoldEmRank>(static_cast<int>(rank) + 1);
    }
    return rank;
}


// default constructor only once pushes back a card of each valid suit of each valid rank 
HoldEmDeck::HoldEmDeck()
{
    // each rank
    for(HoldEmRank r = HoldEmRank::two; r <= HoldEmRank::ace; ++r)
    {
        // each suit
        for(Suit s = Suit::clubs; s <= Suit::spades; ++s)
        {
            // only once
            cards.push_back(Card<HoldEmRank, Suit>(r, s));
        }
    }
}


// TODO: destructor



/**
 * @brief print function
 * @param os
 */
void HoldEmDeck::print(std::ostream &os){
    for(auto c : cards){
        os << c << " ";
    }
    os << endl;
}



