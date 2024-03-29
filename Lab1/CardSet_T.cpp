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
    for (auto it = CardSet<R,S>::cards.begin(); it != CardSet<R,S>::cards.end(); ++it){
        // insert a space after one card
        os << *it << " ";
        count++;
        // line break when count reaches lb
        if (count % lb == 0){
            os << std::endl;
        }
    }
    os << std::endl;
}





/**
 * @brief right shift operator takes nonconst reference of CardSet and return reference of CardSet
 *        if object is empty, throw an exception: a standard runtime_error
 *        Otherwise, Push a card at the back,
 *        Pop the card
 * 
 * @tparam R Rank type
 * @tparam S Suit type
 * @param cs CardSet object
 * @return CardSet<R, S>& 
 */
template <typename R, typename S>
CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &cardset)
{
    // if object is empty, throw runtime_error
    if (cards.size() == 0){
        throw std::runtime_error("CardSet is empty");
    }
    cardset.cards.push_back(cards.back());
    cards.pop_back();
    return cardset;
}




/**
 * @brief check if the cardset is empty
 * 
 * @tparam R Rank type
 * @tparam S Suit type
 * @return true 
 * @return false 
 */
template <typename R, typename S>
bool CardSet<R, S>::is_empty()
{
    return cards.size() == 0;
}




/**
 * @brief return the size of the cardset
 * 
 * @tparam R Rank type
 * @tparam S Suit type
 * @return size_t 
 */
template <typename R, typename S>
size_t CardSet<R, S>::getSize()
{
    return cards.size();
}
