
#include "DerivedClass.h"
#include <iostream>

using namespace std;



/**
 * @brief default constructor
 */
DerivedClass::DerivedClass(){
    cout << "DerivedClass default constructor" << endl;
}

/**
 * @brief destructor
 */
DerivedClass::~DerivedClass(){
    cout << "DerivedClass destructor" << endl;
}

/**
 * @brief DoSomething()
 * 
 */
void DerivedClass::DoSomething(){
    cout << "DerivedClass::DoSomething()" << endl;
}