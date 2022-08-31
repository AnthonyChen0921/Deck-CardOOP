/*
    Suit.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Aug 31, 2022
*/

#include <string>
#include <ostream>


// declare enum class suits for cards
enum class Suit
{
    clubs,
    diamonds,
    hearts,
    spades,
    undefined
};

// declare enum class ranks for cards
enum class Rank
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace
};

// declare shift operator for suits
std::ostream &operator<<(std::ostream &os, const Suit &suit);

// declare prefix increment operator for suits
Suit &operator++(Suit &suit);