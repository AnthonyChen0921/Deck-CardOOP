
// include guards
#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>

class BaseClass{
private:
    std::string name;
public:
    //std::string name;
    BaseClass();
    virtual ~BaseClass();
     void DoSomething();
    const std::string BaseClass::*GetNamePtr() const { return &BaseClass::name; }
};

#endif