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