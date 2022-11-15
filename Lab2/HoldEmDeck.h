/*
    HoldEmDeck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 4, 2022
*/

#pragma once
#include "Deck.h"
#include "Suit.h"
#include "Card_T.h"
#include "CardSet_T.h"
#include <string>
#include <ostream>
#include <vector>

// enum class Ranks for HoldEmRank
enum class HoldEmRank
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
    undefined
};


// HoldEmDeck class
class HoldEmDeck : public Deck<HoldEmRank, Suit>
{
public:
    // default constructor
    HoldEmDeck();
};

// overloaded operator<< for HoldEmRank
std::ostream &operator<<(std::ostream &os, const HoldEmRank &rank);

// overloaded prefix operator++ for HoldEmRank
HoldEmRank &operator++(HoldEmRank &rank);