
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>
template <typename T>
void printT(T t1, T t2){
    for (T t = t1; t != t2; t++)
    {
        std::cout << *t << std::endl;
    }
}
#endif // TEMPLATE_H