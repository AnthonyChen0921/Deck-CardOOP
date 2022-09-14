
#include <cstring>
#include <iostream>
#include <cmath>
#include <functional>
#include "Compose_T.h"

using namespace std;

int main()
{
    /*
        Question 2
    */
    // declare c-style string
    const char *str1 = "Hello, ";
    const char *str2 = "World!";

    // print c-style string to the console
    cout << str1 << "/" << str2 << endl;

    // print the length of c-style string
    cout << "strlen(str1): " << strlen(str1) << endl;
    cout << "strlen(str2): " << strlen(str2) << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    /*
        Question 3
    */
    // const pointer pointing to a const char
    // Pointer to function cpp reference page: https://en.cppreference.com/w/cpp/language/pointer
    size_t (*strlen_ptr)(const char * const) = &strlen;

    // print the length of c-style string using the function pointer
    cout << "strlen_ptr(str1): " << strlen_ptr(str1) << endl;
    cout << "strlen_ptr(str2): " << strlen_ptr(str2) << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    /*
        Question 4
    */
    float f1 = 1.0;

    // output the value
    cout << "f1: " << f1 << endl;
    cout << "std::sin(std::cos(f1)): " << std::sin(std::cos(f1)) << endl;

    /*
        Question 5
    */
    // std::function cpp reference page: https://en.cppreference.com/w/cpp/utility/functional/function
    std::function<float(float)> sn = [](auto x)
    { return std::sin(x); };
    std::function<float(float)> cn = [](auto x)
    { return std::cos(x); };
    // call sn(cn(f1))
    cout << "sn(cn(f1)): " << sn(cn(f1)) << endl;

    /*
        Question 6
    */
    auto res = compose(sn, cn);
    cout << "compose(sn, cn)(f1): " << res(f1) << endl;

    /*
        Question 7
    */
   // declare auto variable initialized by previous variable and f1 into std::bind
    auto res2 = std::bind(res, f1);
    cout << "std::bind(compose(sn,cn), f1)(): " << res2() << endl;

    return 0;
}