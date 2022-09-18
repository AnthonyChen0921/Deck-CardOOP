/*
    CardSet_T.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 17, 2022
*/

#include "CardSet_T.h"

// define print member function
template <typename R, typename S>
void CardSet<R, S>::print(std::ostream &os, size_t lb)
{
    size_t count = 0;
    for (auto it = cards.begin(); it != cards.end(); ++it){
        os << *it << " ";
        count++;
        if (count % lb == 0){
            os << std::endl;
        }
    }
}