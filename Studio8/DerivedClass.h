

// include guards
#ifndef DERIVEDCLASS_H
#define DERIVEDCLASS_H

#include "BaseClass.h"

class DerivedClass : public BaseClass
{
private:
    std::string name;

public:
    // std::string name;
    DerivedClass();
    virtual ~DerivedClass();
     void DoSomething();
    const std::string DerivedClass::*GetNamePtr() const { return &DerivedClass::name; }
};

#endif