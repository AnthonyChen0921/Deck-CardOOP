
// if guards

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>
#include "Foo.h"

static unsigned int count = 0;

template <typename T>
const T& add_size(const T& t) {
    count += sizeof(t);
    return t;
}

template <typename T>
void print(std::ostream& os, const T& t) {
    os << t << " ";
}

template <typename T, typename... Args>
void print(std::ostream& os, const T& t, const Args&... rest) {
    os << t << " ";
    print(os, rest...);
    add_size(t);
    // print the size of the arguments
    os << "size: " << count << std::endl;
}

template <typename... Args>
void print2(std::ostream& os, const Args&... rest) {
    os << sizeof...(rest) << " ";
    print(os, rest...);
}




#endif // TEMPLATE_H