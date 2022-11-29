
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

/*
void printit(std::ostream& os, const Foo& s) {
    os << "{" << s << "} ";
    add_size(s);
    // print the size of the arguments
    os << "size: " << count << std::endl;
}


template <typename... Args>
void printit(std::ostream& os, const Foo& s, const Args&... rest) {
    os << "{" << s << "} ";
    printit(os,rest...);
    add_size(s);
    // print the size of the arguments
    os << "size: " << count << std::endl;
}
*/
