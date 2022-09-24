/*
    function.h
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 24, 2022
    @brief: function.h contains enum message
*/


#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <iostream>



enum arrayIndex{
    programName = 0,
    firstPlayer = 1,
    secondPlayer = 2,
    thirdPlayer = 3,
    fourthPlayer = 4,
    fifthPlayer = 5,
    sixthPlayer = 6,
};

enum GameRules{
    minPlayer = 2,
    maxPlayer = 8,
};

enum message {
    success,
    quit_game,
    end_game,
    continue_game,
};

enum PinochleGameGameRules{
    num_of_players = 4,
    packet_of_cards = 3,
};


// declare the helper function
int usageMessage(const char* programName);





#endif