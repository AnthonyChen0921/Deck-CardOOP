/*
    Card_T.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/

#include "Card_T.h"


// declare template operator<< for Card
/**
 * @brief operator<<
 * @param os
 * @param const card
 * @return os
 */
template <typename R, typename S>
std::ostream &operator<<(std::ostream &os, const Card<R, S> &card)
{
    os << card.rank << card.suit;
    return os;
}

template <typename R, typename S>
bool compareRank(const Card<R, S> &lhs, const Card<R, S> &rhs){
    if(lhs.rank < rhs.rank || (lhs.rank == rhs.rank && lhs.suit < rhs.suit)){
        return true;
    }
    else{
        return false;
    }
}

template <typename R, typename S>
bool compareSuit(const Card<R, S> &lhs, const Card<R, S> &rhs){
    if(lhs.suit < rhs.suit || (lhs.suit == rhs.suit && lhs.rank < rhs.rank)){
        return true;
    }
    else{
        return false;
    }
}