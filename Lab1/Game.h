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
#include "function.h"

class Game
{
protected:
    // vector of players
    std::vector<std::string> players;

public:
    // constructor
    Game(int argc, const char *argv[]);

    // member functions
    // pure virtual function play()
    virtual int play() = 0;

    // helper functions
    // ask if player wants to end the game
    int askEndGame();
};

// overloaded operator<<
std::ostream &operator<<(std::ostream &os, const Game &game);
