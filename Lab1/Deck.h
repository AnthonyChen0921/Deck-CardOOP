/*
    Deck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/

#ifndef DECK_H
#define DECK_H

#include <string>
#include <ostream>
#include "CardSet_T.h"
#include <random>
#include <algorithm>



// class template that is parameterized by rank and suit types and inherits from CardSet
template <typename R, typename S>
class Deck : public CardSet<R, S> {
public:
    // constructor
    Deck() {}

    // destructor
    ~Deck() {}

    // member function
    void shuffle();

};

#if defined (DECK_H)
      #include "Deck.cpp"
#endif /* TEMPLATE_HEADERS_INCLUDE_SOURCE */

#endif



