
#include <iostream>
#include "Studio5.h"

using namespace std;

int main()
{
    /*
        Question 1
    */
    // delcare a point and print x,y
    // Point p1;
    // cout << "p1.x: " << p1.getX() << endl;
    // cout << "p1.y: " << p1.getY() << endl;
    // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    // // call accessor and mutator
    // const Point p2(1, 2);
    // p1.setX(10).setY(20);
    // cout << "p1.x: " << p1.getX() << endl;
    // cout << "p1.y: " << p1.getY() << endl;
    // cout << "p2.x: " << p1.getX() << endl;
    // cout << "p2.y: " << p1.getY() << endl;




    Point m; // default construction

    //cout << "m.x is " << m.getX() << " and m.y is "<< m.getY() << endl;
    m.foo(m); 

    cout << "before mutator" << endl;

    m.setX(7).setY(3); // chained use of mutator functions

    //cout << "m.x is " << m.getX() << " and m.y is " << m.getY() << endl;
    m.foo(m);

    cout << "before copy constructor" << endl;

    Point n(m); // copy construction

    n.foo(n);

    //cout << "n.x = " << n.getX() << " and n.y = " << n.getY() << endl;




    return 0;
}