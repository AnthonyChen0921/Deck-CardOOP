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
    // check if the number of players is less than minPlayers
    if (argc <= GameRules::minPlayer){
        throw invalid_argument("Not enough players");
    }
    // check if the number of players is more than maxPlayers
    if (argc > GameRules::maxPlayer){
        throw invalid_argument("Too many players");
    }
    // push back the players' name to the players vector
    for (int i = arrayIndex::firstPlayer; i < argc; i++)
    {
        players.push_back(argv[i]);
        //cout << "Player " << i << ": " << players[i-1] << endl;
    }
}

/**
 * @brief askEndGame() function ask the player want to end the game or not
 * 
 * @return int return 1 if want to end
 */
int Game::askEndGame(){
    cout << "Do you want to end the game? (y/n)" << endl;
    string input;
    cin >> input;
    if (input == "y" || input == "Y" || input == "yes" || input == "Yes"){
        return message::quit_game;
    }
    return message::continue_game;
}
