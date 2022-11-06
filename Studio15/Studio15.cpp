
#include <iostream>
#include <string>
#include "Foo.h"
#include "template.h"

using namespace std;





int main()
{
    string str1 = "Hello";
    const char *str2 = "World";
    Foo foo1("This is Foo");
    int i = 5;
    float f = 5.5;
    // print all the variables
    print(cout, str1, str2, foo1, i, f);
    cout << endl;
    return 0;
}