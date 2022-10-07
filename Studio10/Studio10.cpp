

#include "Foo.h"
#include <iostream>
#include <memory>

using namespace std;

enum message {
    success,
};

unique_ptr<Foo> foo(unique_ptr<Foo> f) {
    // print the object
    f->print();
    // return the pointer
    return f;
}



int main(){
    // Foo foo("hello");
    // Foo foo2(foo);

    // Foo foo1("foo1");
    // Foo foo2("foo2");
    // Foo foo3("foo3");
    // foo1 = foo2 = foo3;

    unique_ptr<Foo> foo1(new Foo("hello"));
    unique_ptr<Foo> foo2 = std::move(foo1);
    foo1 = foo(std::move(foo2));
    foo1->print();


    return message::success;
}