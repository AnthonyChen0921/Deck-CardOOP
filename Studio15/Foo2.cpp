
#include <iostream>
#include <string>
#include "Foo.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Foo& foo) {
    os << foo.my_str;
    return os;
}

bool operator<(const Foo& foo1, const Foo& foo2) {
    return foo1.my_str < foo2.my_str;
}

// bool Foo::operator<(const Foo& foo) const {
//     return my_str < foo.my_str;
// }

