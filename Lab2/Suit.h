/*
    Suit.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/
#pragma once
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

// declare prefix increment operator for Rank
Rank &operator++(Rank &rank);
