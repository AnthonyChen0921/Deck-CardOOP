/*
    Studio1.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 1, 2022
*/
#pragma once

#include <ostream>


// declare the enum class Weekday
enum class Weekday
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

// declare the enum class Pressure
enum class Pressure{
    lo,
    med,
    hi,
    pop
};

// declare shift operator<< for Weekday
std::ostream &operator<<(std::ostream &os, const Weekday &weekday);


// declare postfix operator++ for Weekday
Weekday operator++(Weekday &weekday, int);


// declare the postfix operator-- for Weekday
Weekday operator--(Weekday &weekday, int);

// declare the prefix operator-- for Pressure
Pressure operator--(Pressure &pressure, int);

