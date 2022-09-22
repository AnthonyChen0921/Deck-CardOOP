


// include guards
#ifndef DERIVEDCLASS_H
#define DERIVEDCLASS_H


#include "BaseClass.h"


class DerivedClass : public BaseClass{
public:
    DerivedClass();
    ~DerivedClass();
    void DoSomething();
};

#endif