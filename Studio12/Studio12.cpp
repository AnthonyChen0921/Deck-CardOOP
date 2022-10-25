

#include <iostream>
#include "myStruct.h"
#include <algorithm>



using namespace std;

int main() {

    
    myStruct<> a(1);
    myStruct<> b(2);

    cout << a << " " << b << endl;

    std::swap(a, b);
    cout << a << " " << b << endl;

    return 0;
}