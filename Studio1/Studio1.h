/*
    Studio1.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 1, 2022
*/


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

// declare shift operator<< for Weekday
std::ostream &operator<<(std::ostream &os, const Weekday &weekday);


// declare postfix operator++ for Weekday
Weekday &operator++(Weekday &weekday);

