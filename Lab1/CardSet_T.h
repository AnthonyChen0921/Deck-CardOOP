/*
    CardSet_T.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 17, 2022
*/

#ifndef CARDSET_T_H
#define CARDSET_T_H

#include "Card_T.h"
#include <vector>
#include <string>


// class template that is parameterized by rank and suit types
template <typename R, typename S>
class CardSet {
protected:
    // protected member variables vector of cards
    std::vector< Card<R, S> > cards;
public:
    // print function
    void print(std::ostream &os, size_t lb);
    // constructor
    CardSet() {}
    // destructor
    ~CardSet() {}
};

#if defined (CARDSET_T_H)
      #include "CardSet_T.cpp"
#endif /* TEMPLATE_HEADERS_INCLUDE_SOURCE */

#endif



