/*
    Studio1.cpp
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 1, 2022
*/

#include "Studio1.h"
#include <iostream>

using namespace std;

/**
 * @brief shift operator<<
 * @param os
 * @param const weekday
 * @return os
 */
ostream &operator<<(ostream &os, const Weekday &weekday)
{
    switch (weekday)
    {
    case Weekday::Monday:
        os << "Mon";
        break;
    case Weekday::Tuesday:
        os << "Tue";
        break;
    case Weekday::Wednesday:
        os << "Wed";
        break;
    case Weekday::Thursday:
        os << "Thu";
        break;
    case Weekday::Friday:
        os << "Fri";
        break;
    case Weekday::Saturday:
        os << "Sat";
        break;
    case Weekday::Sunday:
        os << "Sun";
        break;
    default:
        os << " ";
        break;
    }
    os << " ";
    return os;
}

/**
 * @brief postfix operator++
 * @param weekday
 * @return weekday
 */
Weekday &operator++(Weekday &weekday)
{
    if (weekday == Weekday::Sunday)
    {
        weekday = Weekday::Monday;
    }
    else
    {
        weekday = static_cast<Weekday>(static_cast<int>(weekday) + 1);
    }
    return weekday;
}

int main()
{
    // test shift operator<<
    cout << "------------------------" << endl;
    cout << "Testing shift operator<<" << endl;
    cout << "------------------------" << endl;
    cout << Weekday::Monday << endl;
    cout << Weekday::Tuesday << endl;
    cout << Weekday::Wednesday << endl;
    cout << Weekday::Thursday << endl;
    cout << Weekday::Friday << endl;
    cout << Weekday::Saturday << endl;
    cout << Weekday::Sunday << endl;
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;

    // test postfix operator++
    cout << "------------------------" << endl;
    cout << "Testing postfix operator++" << endl;
    cout << "------------------------" << endl;
    Weekday today = Weekday::Monday;

    // do while loop to cycle through the days of the week
    do
    {
        cout << today << endl;
        ++today;
    } while (today != Weekday::Monday);
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;


    return 0;
}