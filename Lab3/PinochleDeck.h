/*
    PinochleDeck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 2, 2022
*/

#pragma once
#include "Deck.h"
#include "Suit.h"
#include "Card_T.h"
#include "CardSet_T.h"
#include <string>
#include <ostream>
#include <vector>

// enum class Ranks for PinochleDeck
enum class PinochleRank
{
    nine,
    jack,
    queen,
    king,
    ten,
    ace,
    undefined
};

// PinochleDeck class
class PinochleDeck : public Deck<PinochleRank, Suit>
{
public:
    // default constructor
    PinochleDeck();
};

// overloaded operator<<
std::ostream &operator<<(std::ostream &os, const PinochleRank &rank);

// overloaded prefix operator++ for PinochleRank
PinochleRank &operator++(PinochleRank &rank);