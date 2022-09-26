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
5. It behaves similarly with 4.

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

 