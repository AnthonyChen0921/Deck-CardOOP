/*
    Card_T.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
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

