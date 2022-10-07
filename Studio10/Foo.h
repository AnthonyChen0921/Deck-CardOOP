

#ifndef FOO_H
#define FOO_H

#include <string>

class Foo {
private:
    std::string name;
public:
    Foo(const std::string& name);
    virtual ~Foo();
    Foo(const Foo& other);
    Foo& operator=(const Foo& other);
    virtual void print();
};



#endif