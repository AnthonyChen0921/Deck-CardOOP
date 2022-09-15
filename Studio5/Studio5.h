
#include <iostream>
using namespace std;
// declare point with 2 int
class Point
{
private:
    int x;
    int y;

public:
    // declare a defualt constructor
    Point() : x(0), y(0) {
        cout << "Default constructor called" << endl;
        cout << "Address of the object: " << this << endl;
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
    }
    // declare a constructor with 2 int
    Point(int x, int y) : x(x), y(y) {}
    // declare a copy constructor
    Point(const Point &p) : x(p.x), y(p.y) {
        cout << "Copy constructor called" << endl;
        cout << "Address of the object: " << this << endl;
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
    }

    // accessor
    int getX() const { return x; }
    int getY() const { return y; }

    // mutator
    Point& setX(int x){
        this->x = x;
        return *this;
    }
    Point& setY(int y){
        this->y = y;
        return *this;
    }

    // foo() takes a Point by value and returns a Point by value
    Point foo(Point p) {
        return p;
    }
};
