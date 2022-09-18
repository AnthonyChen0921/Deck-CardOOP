/*
    Deck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 18, 2022
*/

#include "Deck.h"



/**
 * @brief shuffle the deck using random_device and mt19937 and the std::shuffle function
 * 
 * @tparam R Rank type
 * @tparam S Suit type
 */
template <typename R, typename S>
void Deck<R, S>::shuffle()
{
    // random_device reference: https://diego.assencio.com/?index=6890b8c50169ef45b74db135063c227c
    std::random_device device;
    std::mt19937 generator(device());

    // scope into std namespace to call shuffle function
    // scope into CardSet namespace to access cards vector
    std::shuffle(CardSet<R,S>::cards.begin(), CardSet<R,S>::cards.end(), generator);
}
