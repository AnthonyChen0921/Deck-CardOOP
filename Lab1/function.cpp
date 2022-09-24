/*
    function.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 24, 2022
*/

#include "function.h"

using namespace std;


/**
 * @brief function to print the usage message
 * 
 * @param program_name 
 */
int usageMessage(const char *program_name){
    cout << "Usage: " << program_name << " <Pinochle / HoldEm> "<< " <number of players>" << endl;
    return message::success;
}
