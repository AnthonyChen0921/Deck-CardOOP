


#include "Object.h"
#include <iostream>
#include <memory>

using namespace std;


enum message {
    success,
};

unique_ptr<Object> makeObj(){
    unique_ptr<Object> obj = make_unique<Object>();
    return obj;
}

void useObj(unique_ptr<Object> &obj){
    obj->print();
}

int main(){
    // shared_ptr<Object> obj1 = make_shared<Object>();
    // shared_ptr<Object> obj2 = make_shared<Object>(*obj1);
    // weak_ptr<Object> obj3 = obj1;


    // cout << "About to assign obj1 to obj2" << endl;
    // obj1 = obj2;
    // cout << "Done assigning obj1 to obj2" << endl;
    


    // shared_ptr<Object> obj4 = obj3.lock();

    // if (obj4 == nullptr){
    //     cout << "The weak_ptr no longer points to a valid object" << endl;
    // }
    // else{
    //     obj4->print();
    // }
    // obj4 = nullptr;


    unique_ptr<Object> obj = makeObj();
    useObj(obj);
    obj->print();



    return message::success;
} 