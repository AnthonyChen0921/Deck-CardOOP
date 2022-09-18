/*
    Deck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/

#pragma once
#include <string>
#include <ostream>
#include "CardSet_T.h"



// class template that is parameterized by rank and suit types and inherits from CardSet
template <typename R, typename S>
class Deck : public CardSet<R, S> {
public:
    // constructor
    Deck() {}

    // destructor
    ~Deck() {}

};



