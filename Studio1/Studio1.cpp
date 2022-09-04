/*
    Studio1.cpp
    Author: @Anthony Chen, @Yunlai Chen
    Email: chenerdong@wustl.edu, c.yunlai@wustl.edu
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

/**
 * @brief postfix operator--
 * @param weekday
 * @return weekday
 */
Weekday operator--(Weekday &weekday, int){
    Weekday original = weekday;
    if(weekday == Weekday::Monday){
        weekday = Weekday::Sunday;
    }
    else{
        weekday = static_cast<Weekday>(static_cast<int>(weekday) - 1);
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

/**
 * @brief postfix operator--
 * @param weekday
 * @return weekday
 */
Pressure operator--(Pressure &pressure, int){
    Pressure original = pressure;
    if(pressure == Pressure::lo || pressure == Pressure::pop){
        return pressure;
    }
    else{
        pressure = static_cast<Pressure>(static_cast<int>(pressure) - 1);
    }
    return original;
}




int main()
{
    // test shift operator For Weekday<<
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
    cout << "Testing postfix operator++ for Weekday" << endl;
    cout << "------------------------" << endl;
    Weekday today = Weekday::Monday;

    // do while loop to cycle through the days of the week
    do
    {
        cout << today++ << endl;
    } while (today != Weekday::Monday);
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;

    // test postfix operator--
    cout << "------------------------" << endl;
    cout << "Testing postfix operator-- for Weekday" << endl;
    cout << "------------------------" << endl;
    today = Weekday::Sunday;
    do
    {
        cout << today-- << endl;
    } while (today != Weekday::Sunday);




//////////////////////////////////////////////////////////////////////
   // test shift operator For Pressure<<
    cout << "------------------------" << endl;
    cout << "Testing shift operator<<" << endl;
    cout << "------------------------" << endl;
    cout << Pressure::lo << endl;
    cout << Pressure::med << endl;
    cout << Pressure::hi << endl;
    cout << Pressure::pop << endl;
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;

    // test postfix operator++
    cout << "------------------------" << endl;
    cout << "Testing postfix operator++ for Pressure" << endl;
    cout << "------------------------" << endl;
    Pressure pressure = Pressure::lo;

    // do while loop to cycle through the days of the week
    for(int i=0;i<5;i++)
        cout << pressure++ << endl;
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;

    // test postfix operator--
    cout << "------------------------" << endl;
    cout << "Testing postfix operator-- for Pressure, starting from high" << endl;
    cout << "------------------------" << endl;
    pressure = Pressure::hi;
    for(int i=0;i<5;i++)
        cout << pressure-- << endl;

    pressure = Pressure::pop;
    for(int i=0;i<3;i++)
        cout << pressure-- << endl;
    cout << "------------------------" << endl;
    cout << "      Done Testing      " << endl;
    cout << "------------------------" << endl;





    return 0;
}
