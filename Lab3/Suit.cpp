/*
    Suit.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/
#include "Suit.h"

using namespace std;

/**
 * @brief operator<<
 * @param os
 * @param const suit
 * @return os
 */
std::ostream &operator<<(std::ostream &os, const Suit &suit)
{
    // "C" for clubs, "D" for diamonds, "H" for hearts, "S" spades, or "?" for undefined
    switch (suit)
    {
    case Suit::clubs:
        os << "♣";
        break;
    case Suit::diamonds:
        os << "♦";
        break;
    case Suit::hearts:
        os << "♥";
        break;
    case Suit::spades:
        os << "♠";
        break;
    default:
        os << "?";
        break;
    }
    return os;
}

/**
 * @brief operator++
 * @param suit
 * @return suit
 */
Suit &operator++(Suit &suit)
{
    // if suit is not undefined, increment it to the next suit
    if (suit != Suit::undefined)
    {
        suit = static_cast<Suit>(static_cast<int>(suit) + 1);
    }

    // if suit is undefined it should remain undefined
    return suit;
}
// define prefix increment operator for Rank
Rank &operator++(Rank &rank)
{
    // if rank is not undefined, increment it to the next rank
    if (rank != Rank::ace)
    {
        rank = static_cast<Rank>(static_cast<int>(rank) + 1);
    }

    // if rank is undefined it should remain undefined
    return rank;
}
