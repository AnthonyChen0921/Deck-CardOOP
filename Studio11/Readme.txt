1. 
    Yunlai Chen, Anthony Chen


2. 
    Errors:
        Studio11.cpp:21:17: error: cannot initialize a variable of type 'int *const' with an rvalue of type 'const int *'
            int * const ptr3 = &a;
                        ^      ~~
        Studio11.cpp:33:11: error: cannot initialize a variable of type 'int *' with an rvalue of type 'const int *'
            int * ptr7 = &a;
                ^      ~~
        2 errors generated.
        make: *** [studio11] Error 1

    Explain: according to comment, the (5) and (9) instruction of delcaration cannot be compiled.
    (5) is due to the fact that we have a pointer that point to a non-const variable, but actally initialize it with the address of const variable.
    (9) is because we have a pointer to non-const variable, but initialize it with the address of const variable.

    "Top-level const concerns whether or not a pointer can be modified, low-level const concerns whether or not the object to which the pointer points can be modified."


3. 
    Errors:
        Studio11.cpp:39:12: error: read-only variable is not assignable
            (*ptr1)++;
            ~~~~~~~^
        Studio11.cpp:40:12: error: read-only variable is not assignable
            (*ptr2)++;
            ~~~~~~~^
        Studio11.cpp:43:12: error: read-only variable is not assignable
            (*ptr5)++;
            ~~~~~~~^
        Studio11.cpp:44:12: error: read-only variable is not assignable
            (*ptr6)++;

    Correspond to (3), (4), (7), (8) in the declaration.
    Explain:
    (3) we cannot change value of const pointer to const int
    (4) we cannot change the value of const pointer to const int, even initialize with a non-cosnt int
    (7) Can't change the value of const int
    (8) Can't change the value of const int, even initialize with a non-const int



4.  
    Since we can change the value of const defined ptr, by using auto, thus we know using auto discard the top-level const, but keep the low-level const.


5. 
    Using decltype instead of auto, we can see we cannot change the value of const defined ptr, thus we know using decltype keep both top-level and low-level const.

6.  
    typedef int myInt;
    typedef const int myConstInt;
    typedef const int* myConstIntPointer;
    typedef const int* const myConstIntPointerConst;
    typedef int* myIntPointer;
    typedef int* const myIntPointerConst;

