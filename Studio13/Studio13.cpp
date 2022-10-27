

#include "Foo.h"
#include <iostream>
#include <memory>
#include "myMove.h"
#include <typeinfo>
#include <type_traits>

using namespace std;

enum message {
    success,
};

std::unique_ptr<Foo> foo(std::unique_ptr<Foo> f) {
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

    // std::unique_ptr<Foo> foo1(new Foo("hello"));
    unique_ptr<Foo> foo1 = make_unique<Foo>("hello");
    std::unique_ptr<Foo> foo2 =  myMove(foo1);
    foo1 = foo(myMove(foo2));
    foo1->print();

    cout << typeid(std::remove_reference<decltype(*foo1)>::type).name() << endl;


    return message::success;
}