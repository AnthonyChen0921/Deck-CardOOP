/*
    PinochleDeck.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 2, 2022
*/

#include "PinochleDeck.h"
#include <iostream>

using namespace std;

/**
 * @brief shift operator<<
 * @param os
 * @param const PinochleRank
 * @return os
 */
ostream &operator<<(ostream &os, const PinochleRank &rank){
    // "9" for nine, "J" for jack, "Q" for queen, "K" for king, "T" for ten, "A" for ace, or "?" for undefined
    switch (rank)
    {
    case PinochleRank::nine:
        os << "9";
        break;
    case PinochleRank::jack:
        os << "J";
        break;
    case PinochleRank::queen:
        os << "Q";
        break;
    case PinochleRank::king:
        os << "K";
        break;
    case PinochleRank::ten:
        os << "10";
        break;
    case PinochleRank::ace:
        os << "A";
        break;
    case PinochleRank::undefined:
        os << "?";
        break;
    }
    return os;
}


/**
 * @brief prefix operator++
 * 
 * @return PinochleRank& 
 */
PinochleRank &operator++(PinochleRank &rank){
    // if rank is not undefined, increment it to the next rank
    if (rank != PinochleRank::undefined)
    {
        rank = static_cast<PinochleRank>(static_cast<int>(rank) + 1);
    }
    return rank;
}


// default constructor twice pushes back a card of each valid suit of each valid rank 
PinochleDeck::PinochleDeck()
{
    // each rank
    for(PinochleRank r = PinochleRank::nine; r <= PinochleRank::ace; ++r)
    {
        // each suit
        for(Suit s = Suit::clubs; s <= Suit::spades; ++s)
        {
            // twice push back
            cards.push_back(Card<PinochleRank, Suit>(r, s));
            cards.push_back(Card<PinochleRank, Suit>(r, s));
        }
    }
}


// TODO: destructor



