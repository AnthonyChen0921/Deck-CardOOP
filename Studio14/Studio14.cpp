
#include <iostream>
#include <string>
#include "Foo.h"
#include "template.h"

using namespace std;



namespace mySpace {
    void print(std::ostream& os, const Foo& t) {
        os << "mySpace called ";
        os << t;
    }
}

int main()
{
    Foo foo1 = Foo("Hello");
    Foo foo2 = Foo("World");
    print(cout, foo1);
    cout << endl;
    mySpace::print(cout, foo2);
    cout << endl;

    // use < operator to compare two Foo objects and print the result
    if (foo1 < foo2) {
        cout << "foo1 is less than foo2" << endl;
    }
    else {
        cout << "foo1 is greater than or equal to foo2" << endl;
    }

    return 0;
}