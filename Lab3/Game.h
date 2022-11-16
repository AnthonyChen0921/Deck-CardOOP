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
    // declare and define a protected dealer member variable of type size_t, that is initialized to 0
    size_t dealer = 0;
    // declare and define a protected scores member variable that is vector of unsigned integers
    std::vector<unsigned int> scores;

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
