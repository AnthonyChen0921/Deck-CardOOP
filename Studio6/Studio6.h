/*
    Studio6.h
    Author: @Anthony Chen
    Email: chenerdong@wustl.edu
    Date: Sep 1, 2022
*/
#pragma once

#include <ostream>

namespace enumerations
{
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
    enum class Pressure
    {
        lo,
        med,
        hi,
        pop
    };
};


std::ostream &operator<<(std::ostream &os, const enumerations::Weekday &weekday);
enumerations::Weekday operator++(enumerations::Weekday &weekday, int);
std::ostream &operator<<(std::ostream &os, const enumerations::Pressure &pressure);
enumerations::Pressure operator++(enumerations::Pressure &pressure, int);

// };
