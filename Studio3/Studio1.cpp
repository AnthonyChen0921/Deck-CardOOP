/*
    Studio1.cpp
    Author: @Anthony Chen, @Yunlai Chen
    Email: chenerdong@wustl.edu, c.yunlai@wustl.edu
    Date: Sep 1, 2022
*/

#include "Studio1.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>

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


Pressure &operator++(Pressure &pressure){
    if(pressure == Pressure::pop){
        return pressure;
    }
    else{
        pressure = static_cast<Pressure>(static_cast<int>(pressure) + 1);
    }
    return pressure;
}


int main()
{
    
    Pressure p = Pressure::lo;
    cout << p << endl;

    // question 4
    // declare associate container set for weekday
    set<Weekday> weekdays;
    weekdays.insert(Weekday::Monday);
    weekdays.insert(Weekday::Tuesday);
    weekdays.insert(Weekday::Wednesday);
    weekdays.insert(Weekday::Thursday);
    weekdays.insert(Weekday::Friday);
    
    // print out the weekdays
    cout << "printing out the weekdays" << endl;
    for (auto it = weekdays.begin(); it != weekdays.end(); ++it)
    {
        cout << *it;
    }
    cout << endl;
    cout << "weekdays printed" << endl << endl;

    // declare associate container set for weekday2
    set<Weekday> weekdays2;
    weekdays2.insert(Weekday::Monday);
    weekdays2.insert(Weekday::Friday);
    weekdays2.insert(Weekday::Saturday);
    weekdays2.insert(Weekday::Sunday);

    // question 5
    // declare intersection set
    set<Weekday> intersectionSet;

    //set_intersection
    set_intersection(weekdays.begin(), weekdays.end(), weekdays2.begin(), weekdays2.end(), inserter(intersectionSet, intersectionSet.end()));


    // print out the intersection
    cout << "printing out the intersection" << endl;
    for (auto it = intersectionSet.begin(); it != intersectionSet.end(); ++it)
    {
        cout << *it;
    }
    cout << endl;
    cout << "intersection printed" << endl << endl;

    // question 6
    // declare union set
    set<Weekday> unionSet;

    //set_union
    set_union(weekdays.begin(), weekdays.end(), weekdays2.begin(), weekdays2.end(), inserter(unionSet, unionSet.end()));

    // print out the union
    cout << "printing out the union" << endl;
    for (auto it = unionSet.begin(); it != unionSet.end(); ++it)
    {
        cout << *it;
    }
    cout << endl;
    cout << "union printed" << endl << endl;
    




    return 0;
}
