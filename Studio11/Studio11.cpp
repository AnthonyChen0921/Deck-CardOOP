


#include <iostream>

using namespace std;


// add typedef to int, const int, const pointer to int, const pointer to const int, non-const pointer to int, and non-const pointer to const int.

typedef int myInt;

typedef const int myConstInt;

typedef const int* myConstIntPointer;

typedef const int* const myConstIntPointerConst;

typedef int* myIntPointer;

typedef int* const myIntPointerConst;


int main() {
    // 1
    myConstInt a = 0;
    // 2
    myInt b = 1;
    // 3
    myConstIntPointerConst ptr1 = &a;
    // 4
    myConstIntPointerConst ptr2 = &b;
    // 5
    // int * const ptr3 = &a;
    // 6
    myIntPointerConst ptr4 = &b;
    // 7
    myConstIntPointer ptr5 = &a;
    // 8
    myConstIntPointer ptr6 = &b;
    // 9
    // int * ptr7 = &a;
    // 10
    myIntPointer ptr8 = &b;

    // use prefix increment++ to increment the value of each pointer
    // (*ptr1)++;
    // (*ptr2)++;
    // (*ptr3)++;
    (*ptr4)++;
    // (*ptr5)++;
    // (*ptr6)++;
    // (*ptr7)++;
    (*ptr8)++;

    // auto a1 = a;
    // auto b1 = b;
    // auto ptr11 = ptr1;
    // auto ptr21 = ptr2;
    // auto ptr41 = ptr4;
    // auto ptr51 = ptr5;
    // auto ptr61 = ptr6;
    // auto ptr81 = ptr8;
    
    // use decltype to replace auto
    decltype(a) a1 = a;
    decltype(b) b1 = b;
    decltype(ptr1) ptr11 = ptr1;
    decltype(ptr2) ptr21 = ptr2;
    decltype(ptr4) ptr41 = ptr4;
    decltype(ptr5) ptr51 = ptr5;
    decltype(ptr6) ptr61 = ptr6;
    decltype(ptr8) ptr81 = ptr8;

    // use prefix increment++ to increment the value of each pointer
    // a1++;
    b1++;
    // (*ptr11)++;
    // (*ptr21)++;
    (*ptr41)++;
    // (*ptr51)++;
    // (*ptr61)++;
    (*ptr81)++;
    // ptr11++;
    // ptr21++;
    // ptr41++;
    ptr51++;
    ptr61++;
    ptr81++;


    return 0;
}