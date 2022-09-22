

#include <iostream>
#include "BaseClass.h"

using namespace std;


/**
 * @brief default constructor
 */
BaseClass::BaseClass(){
    cout << "BaseClass default constructor" << endl;
}

/**
 * @brief destructor
 */
BaseClass::~BaseClass(){
    cout << "BaseClass destructor" << endl;
}


/**
 * @brief DoSomething()
 * 
 */
void BaseClass::DoSomething(){
    cout << "BaseClass::DoSomething()" << endl;
}

