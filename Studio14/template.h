
// if guards

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>
#include "Foo.h"

template <typename T>
void print(std::ostream& os, const T& t) {
    os << "template called ";
    os << t;
}


#endif // TEMPLATE_H