
#include <iostream>
#include <string>
#include "Foo.h"
#include "template.h"
#include "func.h"

using namespace std;





int main()
{
    string str1 = "Hello";
    const char *str2 = "World";
    const Foo foo1("This is Foo");
    int i = 5;
    float f = 5.5;
    //3
    printit(cout,str1);
    //4
    printit(cout,str2);
    // 5
    printit(cout, foo1);
    cout << endl;
    //6 // print all the variables
    printit(cout, str1, str2, foo1, i, f);
    
    return 0;
}