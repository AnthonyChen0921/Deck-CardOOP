1. Anthony Chen, Yunlai Chen

2. Code:
     BaseClass obj1;
     DerivedClass obj2;

     const string DerivedClass::*ptr1 = &DerivedClass::name;
     const string DerivedClass::*ptr2 = &BaseClass::name;
     const string BaseClass::*ptr3 = &BaseClass::name;

     cout << "ptr1: " << obj2.*ptr1 << endl;
     cout << "ptr2: " << obj2.*ptr2 << endl;
     cout << "ptr3: " << obj2.*ptr3 << endl;

   Output:
     BaseClass default constructor
     BaseClass default constructor
     DerivedClass default constructor
     ptr1: DerivedClass
     ptr2: BaseClass
     ptr3: BaseClass
     DerivedClass destructor
     BaseClass destructor
     BaseClass destructor


3. 
     Error:
          Studio8 % make
          g++ -o studio8 -DUNIX   -Wall -W -g -std=c++17 Studio8.cpp BaseClass.cpp DerivedClass.cpp 
          Studio8.cpp:14:55: error: 'name' is a private member of 'DerivedClass'
          const string DerivedClass::*ptr1 = &DerivedClass::name;
                                                            ^
          ./DerivedClass.h:14:17: note: declared private here
          std::string name;
                         ^
          Studio8.cpp:15:52: error: 'name' is a private member of 'BaseClass'
          const string DerivedClass::*ptr2 = &BaseClass::name;
                                                            ^
          ./BaseClass.h:10:17: note: declared private here
          std::string name;
                         ^
          Studio8.cpp:16:49: error: 'name' is a private member of 'BaseClass'
          const string BaseClass::*ptr3 = &BaseClass::name;
                                                       ^
          ./BaseClass.h:10:17: note: declared private here
          std::string name;
                         ^
          3 errors generated.
          make: *** [studio8] Error 1

     Modified main function code;
          const string DerivedClass::*ptr1 = obj2.GetNamePtr();
          const string DerivedClass::*ptr2 = obj1.GetNamePtr();
          const string BaseClass::*ptr3 = obj1.GetNamePtr();

     Output: same as question 2


4.   Code:
          void (BaseClass::*ptr1)() = &BaseClass::DoSomething;
          void (DerivedClass::*ptr2)() = &BaseClass::DoSomething;
          void (DerivedClass::*ptr3)() = &DerivedClass::DoSomething;
          cout << "ptr1: " << endl;
          (obj1.*ptr1)();
          cout << "ptr2: " << endl;
          (obj2.*ptr2)();
          cout << "ptr3: " << endl;
          (obj2.*ptr3)();


     Output:
          ptr1: 
          BaseClass::DoSomething()
          ptr2: 
          DerivedClass::DoSomething()
          ptr3: 
          DerivedClass::DoSomething()


5.  Output:
          ptr1: 
          BaseClass::DoSomething()
          ptr2: 
          BaseClass::DoSomething()
          ptr3: 
          DerivedClass::DoSomething()

     After changing derived class member function to not virtual,
     void (DerivedClass::*ptr2)() = &BaseClass::DoSomething; produces the different output,
     instead of call DerivedClass::DoSomething(), it now calls BaseClass::DoSomething().
     This is because the compiler will not know which function to call if the function is not virtual,
     so it will call the function according to object type, which is BaseClass.


6.   Code modified:
          std::function<void(BaseClass*)> f1 = &BaseClass::DoSomething;
          std::function<void(DerivedClass*)> f2 = &BaseClass::DoSomething;
          std::function<void(DerivedClass*)> f3 = &DerivedClass::DoSomething;

     output:
          f1: 
          BaseClass::DoSomething()
          f2: 
          BaseClass::DoSomething()
          f3: 
          DerivedClass::DoSomething()

7.   Code modified:
          auto f1 = mem_fn(&BaseClass::DoSomething);
          auto f2 = mem_fn(&BaseClass::DoSomething);
          auto f3 = mem_fn(&DerivedClass::DoSomething);

     Output:
          f1: 
          BaseClass::DoSomething()
          f2: 
          BaseClass::DoSomething()
          f3: 
          DerivedClass::DoSomething()