

// struct myStruct
// {
//     int myInt;
//     myStruct(int myInt_) : myInt(myInt_) { }

//     // myStruct(const myStruct&) = delete;
//     // myStruct& operator=(const myStruct&) = delete;
//     // ~myStruct() = delete;


// };

// template <typename T = int>
// struct myStruct
// {
//     T myInt;

//     myStruct(T myInt_) : myInt(myInt_) { }


//     // myStruct(const myStruct&) = delete;
//     // myStruct& operator=(const myStruct&) = delete;
//     // ~myStruct() = delete;
// };

#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <ostream>

using std::ostream;

template <typename T = int>
class myStruct
{
private:
    T myInt;
public:

    myStruct(T myInt_) : myInt(myInt_) { }

    // myStruct(const myStruct&) = delete;
    // myStruct& operator=(const myStruct&) = delete;
    // ~myStruct() = delete;

    friend ostream& operator<<(ostream& os, const myStruct<T>& obj);
};


template <typename T>
ostream& operator<<(ostream& os, const myStruct<T>& obj)
{
    os << obj.myInt;
    return os;
}

#endif
