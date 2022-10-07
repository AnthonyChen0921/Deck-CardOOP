


#include "Foo.h"
#include <iostream>

using namespace std;



Foo::Foo(const string& name) : name(name) {
    cout << "Foo Object at: " << this << " name: " << name << endl;
}


Foo::~Foo() {
    cout << "Foo Object at: " << this << " name: " << name << " destroyed" << endl;
}


Foo::Foo(const Foo& other) {
    name = other.name;
    cout << "Copy Constructor Called" << endl;
    cout << "this: " << this << endl;
    cout << "other: " << &other << endl;
    cout << "other.name: " << other.name << endl;
}

Foo& Foo::operator=(const Foo& other) {
    cout << "Assignment Operator Called" << endl;
    cout << "this: " << this << endl;
    cout << "this.name: " << name << endl;
    cout << "other: " << &other << endl;
    cout << "other.name: " << other.name << endl;
    name = other.name;
    return *this;
}

void Foo::print() {
    cout << "Foo Object at: " << this << " name: " << name << endl;
}