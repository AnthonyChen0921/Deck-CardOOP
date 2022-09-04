/*
    PinochleDeck.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 2, 2022
*/

#pragma once
#include "Deck.h"
#include "Suit.h"
#include "Card_T.h"
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
class PinochleDeck : public Deck
{
public:
    // default constructor
    PinochleDeck();

    // print function
    void print(std::ostream &os);

private:
    // member variable: vector with cards parameterized with the rank and suit
    std::vector< Card<PinochleRank, Suit> > cards;
};

// overloaded operator<<
std::ostream &operator<<(std::ostream &os, const PinochleRank &rank);

// overloaded prefix operator++ for PinochleRank
PinochleRank &operator++(PinochleRank &rank);