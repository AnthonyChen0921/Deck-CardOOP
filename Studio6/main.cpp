
#include <iostream>
#include "Studio6.h"


// replace with using statements that don't use the keyword namespace and instead use the name of the namespace, the scoping operator, and the name of the type
using namespace enumerations;
using std::cout;
using std::endl;
// using enumerations::Weekday;
// using enumerations::Pressure;


int main()
{
    // declare Weekday and initialize to Monday
    Weekday day = Weekday::Monday;
    //  declare Presssure and initialize to lo
    Pressure pressure = Pressure::lo;
    
    // iterate through the days of the week with a space between each day
    for (int i = 0; i < 7; i++)
    {
        cout << day;
        day++;
    }
    cout << endl;

    // iterate through the pressure values with a space between each value
    for (int i = 0; i < 3; i++)
    {
        cout << pressure;
        pressure++;
    }
    cout << endl;


    return 0;
}