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
int usageMessage(const char *program_name)
{
    cout << "Usage: " << program_name << " <Pinochle / HoldEm> "
         << " <4 players / 2-8 players>" << endl;
    return message::WRRONG_USAGE;
}

// printLogo() function prints the logo of the game
void printLogo(string s)
{
        cout << "====================================================" << endl;
    if (s == "Pinochle"){
        cout << "=                 PinochleGame                     =" << endl;
    }
    else if (s == "HoldEm"){
        cout << "=                 HoldEmGame                       =" << endl;
    }
        cout << "====================================================" << endl;
}