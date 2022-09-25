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

// enum for command line arguments index
enum arrayIndex{
    programName = 0,
    gameName = 1,
    firstPlayer = 2,
    minArg = 2,
    maxArg = 11,
};

// enum for return message, 
// SUCCESS should be fixed to 0
enum message {
    SUCCESS = 0,
    WRRONG_USAGE,
    GAME_NOT_CREATED,
    quit_game,
    end_game,
    continue_game,
    invalid_game_name,
    no_game_name,
};

// Game class specific enum
enum GameRules{
    minPlayer = 2,
    maxPlayer = 8,
    print_format_4 = 4,
    print_format_5 = 5,
};

// Pinochle class specific enum
enum PinochleGameGameRules{
    num_of_players = 4,
    packet_of_cards = 3,
    numPlayerPinochle = 6,
};

// HoldEm class specific enum
enum HoldEmGameRules{
    num_of_flop_cards = 3,
    // 2-9 players, 1 program name, 1 game name
    minPlayerHoldEm = 4, // 2 players + 2
    maxPlayerHoldEm = 11, // 9 players + 2
};

// declare the helper function
int usageMessage(const char* programName);
// print game logo
void printLogo(std::string gameName);

#endif