/*
    Game.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 19, 2022
*/

#include "Game.h"


using namespace std;


/**
 * @brief constructor build a vector of players
 * 
 * @param argc number of players
 * @param argv name of players
 */
// parse the command line arguments of players' name using shift opertaor and initialize the players vector
// updates the argc and argv arguments so that only capture players' name
Game::Game(int argc, const char *argv[]){
    // check if the number of players is less than 2
    if (argc < 3){
        throw invalid_argument("Not enough players");
    }
    // if argc is 3, 4, 5, 6, 7, push back the players' name to the players vector
    for (int i = 1; i < argc; i++)
    {
        players.push_back(argv[i]);
        //cout << "Player " << i << ": " << players[i-1] << endl;
    }
}

