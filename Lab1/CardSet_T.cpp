/*
    CardSet_T.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 17, 2022
*/

#include "CardSet_T.h"

/**
 * @brief print out the cards in the cardset, each line with lb cards
 * 
 * @tparam R Rank type
 * @tparam S Suit type
 * @param os Output stream
 * @param lb card num to Line break
 */
template <typename R, typename S>
void CardSet<R, S>::print(std::ostream &os, size_t lb)
{
    size_t count = 0;
    // iterate through cards vector
    for (auto it = cards.begin(); it != cards.end(); ++it){
        // insert a space after one card
        os << *it << " ";
        count++;
        // line break when count reaches lb
        if (count % lb == 0){
            os << std::endl;
        }
    }
}