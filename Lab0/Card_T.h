/*
    Card_T.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Aug 31, 2022
*/

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