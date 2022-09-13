
#include <cstring>
#include <iostream>
#include <cmath>
#include <functional>

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
    std::function<float(float)> sn = [](float x)
    { return std::sin(x); };
    std::function<float(float)> cn = [](float x)
    { return std::cos(x); };
    // call sn(cn(f1))
    cout << "sn(cn(f1)): " << sn(cn(f1)) << endl;


    return 0;
}