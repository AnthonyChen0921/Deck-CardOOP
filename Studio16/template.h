
// if guards

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>
#include "Foo.h"
#include "func.h"
static unsigned int count = 0;
static unsigned int countInt = 0;
static unsigned int countFloat = 0;


template <typename T>
const T& add_size(const T& t) {
    count += sizeof(t);
    if(typeid(t)==typeid(int))
        countInt += sizeof(t);
    if(typeid(t)==typeid(float))
        countFloat += sizeof(t);    
    return t;
}
template <typename T>
void printit(std::ostream& os, const T& t) {
    os << t <<std::endl;
    // print the size of the arguments
    add_size(t);
    os << "size: " << count << std::endl;
    os << "size of int: " << countInt << std::endl;
    os << "size of float: " << countFloat << std::endl;
    os << "size of other: " << (count-countInt-countFloat) << std::endl;
}

template <typename T, typename... Args>
void printit(std::ostream& os, const T& t, const Args&... rest) {
    os << t << " ";
    add_size(t);
    printit(os, rest...);   
}

template <typename... Args>
void printit(std::ostream& os, const std::string& s, const Args&... rest) {
    os << "\"" << s << "\"";
    printit(os, rest...);
    add_size(s);
}
        

template <typename... Args>
void printit(std::ostream& os, const char * const s, const Args&... rest) {
    os << "[" << s << " "<< reinterpret_cast<const void *> (s) << "] ";
    printit(os,rest...);
    add_size(s);
}



template <typename... Args>
void printit(std::ostream& os, const Foo& s, const Args&... rest) {
    os << "{" << s << "} ";
    printit(os,rest...);
    add_size(s);
}




#endif // TEMPLATE_H