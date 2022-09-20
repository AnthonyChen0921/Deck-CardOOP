/*
    Game.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 19, 2022
*/
#pragma once

#include <vector>
#include <string>
#include <iostream>

class Game
{
protected:
    // vector of players
    std::vector<std::string> players;

public:
    // constructor
    Game(int argc, const char *argv[]);
    // pure virtual function play()
    virtual int play() = 0;
};

// overloaded operator<<
std::ostream &operator<<(std::ostream &os, const Game &game);
