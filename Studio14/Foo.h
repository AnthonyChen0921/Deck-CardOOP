

#ifndef FOO_H
#define FOO_H

#include <string>
#include "template.h"

class Foo
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Foo& foo);
    friend bool operator<(const Foo& foo1, const Foo& foo2);
    Foo(const std::string &str): my_str(str) {}
    // bool operator<(const Foo& foo) const;
private:
    std::string my_str;
};


std::ostream& operator<<(std::ostream& os, const Foo& foo);
bool operator<(const Foo& foo1, const Foo& foo2);




#endif // FOO_H