/*
    PinochleDeck.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 2, 2022
*/

#include "PinochleDeck.h"
#include <iostream>

using namespace std;

/**
 * @brief shift operator<<
 * @param os
 * @param const PinochleRanks
 * @return os
 */
ostream &operator<<(ostream &os, const PinochleRanks &rank){
    // "9" for nine, "J" for jack, "Q" for queen, "K" for king, "T" for ten, "A" for ace, or "?" for undefined
    switch (rank)
    {
    case PinochleRanks::nine:
        os << "9";
        break;
    case PinochleRanks::jack:
        os << "J";
        break;
    case PinochleRanks::queen:
        os << "Q";
        break;
    case PinochleRanks::king:
        os << "K";
        break;
    case PinochleRanks::ten:
        os << "10";
        break;
    case PinochleRanks::ace:
        os << "A";
        break;
    case PinochleRanks::undefined:
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
PinochleRanks &operator++(PinochleRanks &rank){
    // if rank is not undefined, increment it to the next rank
    if (rank != PinochleRanks::undefined)
    {
        rank = static_cast<PinochleRanks>(static_cast<int>(rank) + 1);
    }
    return rank;
}


// default constructor twice pushes back a card of each valid suit of each valid rank 
PinochleDeck::PinochleDeck()
{
    
    for(PinochleRanks r = PinochleRanks::nine; r <= PinochleRanks::ace; ++r)
    {
        for(Suit s = Suit::clubs; s <= Suit::spades; ++s)
        {
            cards.push_back(Card<PinochleRanks, Suit>(r, s));
        }
    }
}


// TODO: destructor



/**
 * @brief print function
 * @param os
 */
void PinochleDeck::print(std::ostream &os){
    for(auto c : cards){
        os << c << " ";
    }
}



