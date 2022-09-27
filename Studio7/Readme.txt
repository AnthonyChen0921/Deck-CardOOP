1. Anthony Chen, Yunlai Chen


2. Studio7 % ./studio7
    BaseClass default constructor
    BaseClass default constructor
    DerivedClass default constructor
    DerivedClass destructor
    BaseClass destructor
    BaseClass destructor


    The first line and the last line of the baseclass constructor and destructor are responsible for the delaration in our main function:
    BaseClass base;

    Starting second line to the fourth line, the derivedclass called baseClass constructor and destructor, 
    which is the reason why we have two baseclass constructor and destructor in the output.
    Noted that destructor is called in the reverse order of constructor.


3. 
----------------------------------------------------------------------------
base reference initialized using base object, do something
BaseClass::DoSomething()
----------------------------------------------------------------------------
base reference initialized using derived object, do something
BaseClass::DoSomething()
----------------------------------------------------------------------------
derived reference initialized using derived object, do something
DerivedClass::DoSomething()
----------------------------------------------------------------------------

4.
----------------------------------------------------------------------------
base reference initialized using base object, do something
BaseClass::DoSomething()
----------------------------------------------------------------------------
base reference initialized using derived object, do something
DerivedClass::DoSomething()
----------------------------------------------------------------------------
derived reference initialized using derived object, do something
DerivedClass::DoSomething()
----------------------------------------------------------------------------

Explaination: 
     After adding the virtual keyword to the baseclass DoSomething function, the output of the second part is changed,
     which means the derivedclass DoSomething function is called when the base reference is initialized using derived object.


5. It behaves similarly with 4.

Explaination:
     After replace object declaration with pointers, the output remains the same as 4,
     because they basically use the same object constructor.

6. 
----------------------------------------------------------------------------
base shared pointer initialized using base object, do something
BaseClass::DoSomething()
----------------------------------------------------------------------------
base shared pointer initialized using derived object, do something
DerivedClass::DoSomething()
----------------------------------------------------------------------------
derived shared pointer initialized using derived object, do something
DerivedClass::DoSomething()
----------------------------------------------------------------------------

7. 
This time it shows less destructor was called than constructor.
Previous shared pointer called destructor automatically when the excution is finished. 
But when we declared a pointer using new and didn't call delete,  memory allocated on 
that pointer won't be released.

8.
Warnning:
Studio7.cpp: In function ‘int main()’:
Studio7.cpp:64:12: warning: deleting object of polymorphic class type ‘BaseClass’ which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
     delete pointerBase1;
            ^~~~~~~~~~~~
Studio7.cpp:65:12: warning: deleting object of polymorphic class type ‘BaseClass’ which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
     delete pointerBase2;
            ^~~~~~~~~~~~
Studio7.cpp:66:12: warning: deleting object of polymorphic class type ‘DerivedClass’ which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
     delete pointerDerived;
            ^~~~~~~~~~~~~~

----------------------------------------------------------------------------
release memory using delete
BaseClass destructor
BaseClass destructor
DerivedClass destructor
BaseClass destructor
----------------------------------------------------------------------------



9. No warnning
----------------------------------------------------------------------------
release memory using delete
BaseClass destructor
DerivedClass destructor
BaseClass destructor
DerivedClass destructor
BaseClass destructor
----------------------------------------------------------------------------

destructor must be virtual because:
1. As we declare the derivedClass object using baseClass pointer, when we call delete, the destructor of baseClass will be called.
2. The type of the pointer would be considered and not its context, thus the destructor of derivedClass will be simply ignored.
3. As a result, this will cause memory leak.

 