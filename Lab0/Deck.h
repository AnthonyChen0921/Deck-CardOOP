/*
    Deck.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Aug 31, 2022
*/

#pragma once
#include <string>
#include <ostream>

// abstract base class Deck
class Deck{
public:
    //  pure virtual print function
    virtual void print(std::ostream &os) = 0;

};