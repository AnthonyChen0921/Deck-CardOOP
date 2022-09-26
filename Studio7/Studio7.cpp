
#include <memory>
#include <iostream>
#include "BaseClass.h"
#include "DerivedClass.h"

using namespace std;

int main()
{
    // declare a baseclass object
    BaseClass base;

    // declare a derivedclass object
    DerivedClass derived;
    
    // add two references to the base class type and one reference to the derived class type. 
    // one of the base class references using the base class object, the other base class 
    // reference and the derived class reference using the derived class object.    BaseClass& ref = base;
    BaseClass& refBase1 = base;
    BaseClass& refBase2 = derived;
    DerivedClass& refDerived = derived;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "base reference initialized using base object, do something" <<endl;
    refBase1.DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "base reference initialized using derived object, do something" <<endl;
    refBase2.DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "derived reference initialized using derived object, do something" <<endl;
    refDerived.DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;

    /* Question 5
    BaseClass pointerBase1 = &base;  
    BaseClass pointerBase2 = &derived;  
    DerivedClass pointerDerived = &derived;  
    */
    
    /* Question 6
    shared_ptr<BaseClass> pointerBase1 = make_shared<BaseClass>(base);  
    shared_ptr<BaseClass> pointerBase2 = make_shared<DerivedClass>(derived);  
    shared_ptr<DerivedClass> pointerDerived = make_shared<DerivedClass>(derived);  
    */
    
    // Question 7
    BaseClass* pointerBase1 = new BaseClass();  
    BaseClass* pointerBase2 =  new DerivedClass();  
    DerivedClass* pointerDerived = new DerivedClass();     

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "base shared pointer initialized using base object, do something" <<endl;
    pointerBase1->DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "base shared pointer initialized using derived object, do something" <<endl;
    pointerBase2->DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<< "derived shared pointer initialized using derived object, do something" <<endl;
    pointerDerived->DoSomething();
    cout<<"----------------------------------------------------------------------------"<<endl;

    //Question 8
    cout<< "release memory using delete" <<endl;
    delete pointerBase1;
    delete pointerBase2;
    delete pointerDerived;
    cout<<"----------------------------------------------------------------------------"<<endl;

    return 0;
}