
#include <memory>
#include <iostream>
#include <functional>
#include "BaseClass.h"
#include "DerivedClass.h"

using namespace std;


int main(){
    BaseClass obj1;
    DerivedClass obj2;

    // const string DerivedClass::*ptr1 = obj2.GetNamePtr();
    // const string DerivedClass::*ptr2 = obj1.GetNamePtr();
    // const string BaseClass::*ptr3 = obj1.GetNamePtr();
    
    // void (BaseClass::*ptr1)() = &BaseClass::DoSomething;
    // void (DerivedClass::*ptr2)() = &BaseClass::DoSomething;
    // void (DerivedClass::*ptr3)() = &DerivedClass::DoSomething;

    //obtain a callable from a pointer to member function by using the library function template
    // std::function<void(BaseClass*)> f1 = &BaseClass::DoSomething;
    // std::function<void(DerivedClass*)> f2 = &BaseClass::DoSomething;
    // std::function<void(DerivedClass*)> f3 = &DerivedClass::DoSomething;

    // use mem_fn to obtain a callable from a pointer to member function
    auto f1 = mem_fn(&BaseClass::DoSomething);
    auto f2 = mem_fn(&BaseClass::DoSomething);
    auto f3 = mem_fn(&DerivedClass::DoSomething);

    // cout << "ptr1: " << obj2.*ptr1 << endl;
    // cout << "ptr2: " << obj2.*ptr2 << endl;
    // cout << "ptr3: " << obj2.*ptr3 << endl;

    // cout << "ptr1: " << endl;
    // (obj1.*ptr1)();
    // cout << "ptr2: " << endl;
    // (obj2.*ptr2)();
    // cout << "ptr3: " << endl;
    // (obj2.*ptr3)();

    cout << "f1: " << endl;
    f1(&obj1);
    cout << "f2: " << endl;
    f2(&obj2);
    cout << "f3: " << endl;
    f3(&obj2);


    return 0;
}