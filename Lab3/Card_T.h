/*
    Card_T.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/

#ifndef CARD_T_H
#define CARD_T_H

#include <ostream>

// declare struct template Card that takes suit and rank enumerations
template <typename R, typename S>
struct Card
{
    // member variables
    R rank;
    S suit;

    // public constructor
    Card(R r, S s) : rank(r), suit(s) {}

    // destructor
    ~Card() {}
};

// declare template operator<< for Card
template <typename R, typename S>
std::ostream &operator<<(std::ostream &os, const Card<R, S> &card);

//add two non-member function compare rank and compare suit
template <typename R, typename S>
bool compareRank(const Card<R, S> &lhs, const Card<R, S> &rhs);

template <typename R, typename S>
bool compareSuit(const Card<R, S> &lhs, const Card<R, S> &rhs);



#if defined (CARD_T_H)
      #include "Card_T.cpp"
#endif /* TEMPLATE_HEADERS_INCLUDE_SOURCE */

#endif
