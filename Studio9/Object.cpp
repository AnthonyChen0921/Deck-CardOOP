

#include "Object.h"

using namespace std;


// size_t Object::numOfObj = 0;

// define a defualt constructor
Object::Object(){
    numOfObj++;
    id = numOfObj;
    cout << "Default constructor called" << endl;
    cout << "Address of the object: " << this << endl;
    cout << "id: " << id << endl;
}

//declare a copy constructor
Object::Object(const Object &p){
    numOfObj++;
    id = p.id;
    cout << "Copy constructor called" << endl;
    cout << "Address of the object: " << this << endl;
    cout << "id: " << id << endl;
}

// declare a destructor
Object::~Object() {
    std::cout << "Destructor called" << std::endl;
    std::cout << "Address of the object: " << this << std::endl;
    std::cout << "id: " << id << std::endl;
}