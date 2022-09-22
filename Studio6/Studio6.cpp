/*
    Studio6.cpp
    Author: @Anthony Chen, @Yunlai Chen
    Email: chenerdong@wustl.edu, c.yunlai@wustl.edu
    Date: Sep 1, 2022
*/

#include "Studio6.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;
using enumerations::Pressure;
using enumerations::Weekday;

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
Weekday operator++(Weekday &weekday, int)
{
    Weekday original = weekday;
    if (weekday == Weekday::Sunday)
    {
        weekday = Weekday::Monday;
    }
    else
    {
        weekday = static_cast<Weekday>(static_cast<int>(weekday) + 1);
    }
    return original;
}

ostream &operator<<(ostream &os, const Pressure &pressure)
{
    switch (pressure)
    {
    case Pressure::lo:
        os << "Low";
        break;
    case Pressure::med:
        os << "Med";
        break;
    case Pressure::hi:
        os << "High";
        break;
    case Pressure::pop:
        os << "Pop";
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
 * @param pressure
 * @return pressure
 */
Pressure operator++(Pressure &pressure, int)
{
    Pressure original = pressure;
    if (pressure == Pressure::pop)
        return pressure;
    else
    {
        pressure = static_cast<Pressure>(static_cast<int>(pressure) + 1);
    }
    return original;
}

// Pressure &operator++(Pressure &pressure){
//     if(pressure == Pressure::pop){
//         return pressure;
//     }
//     else{
//         pressure = static_cast<Pressure>(static_cast<int>(pressure) + 1);
//     }
//     return pressure;
// }
