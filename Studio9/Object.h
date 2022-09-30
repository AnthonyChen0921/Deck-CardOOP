


// guards
#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>



class Object
{
public:
    inline static size_t numOfObj = 0;
    size_t id;
    // declare a defualt constructor
    Object();
    // declare a copy constructor
    Object(const Object &p);
    // declare a destructor
    ~Object();

};




#endif