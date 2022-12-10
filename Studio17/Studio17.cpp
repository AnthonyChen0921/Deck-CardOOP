
#include <iostream>
#include <string>
#include "Studio17.h"
#include "template.h"
#include <vector>
#include <deque>
#include <list>
using namespace std;
int main()
{
    // 2. declare a C-style array of int and initialize it with different values.
    int arr[5] = { 1, 2, 3, 4, 5 };
    /*
    std::cout<<"size of array: "<<sizeof(arr)<<std::endl;
    std::cout<<"size of data type that array contains:" << sizeof(arr[0]) << std::endl;
    */
    // 3.initialize a pointer that points just past the end of the array
    int* end = arr + sizeof(arr)/sizeof(arr[0]);

    //write a for loop  to move a pointer to int from start of the array to just past the end of the array,
    // and prints out each value .
    /*
    for (int* i = arr; i != end; i++)
    {
        std::cout << *i << std::endl;
    }
    */


    // 4
    //printT(arr,arr + sizeof(arr)/sizeof(arr[0]));


    //5

    deque<int> d;
    vector<int> v;
    list<int> l;
    for (int* i = arr; i != end; i++)
    {
        d.emplace_back(*i);
        v.emplace_back(*i);
        l.emplace_back(*i);
    }
    /*
    cout<<"deque:" <<endl;
    printT(d.begin(),d.end());
    cout<<"vector:" <<endl;
    printT(v.begin(),v.end());
    cout<<"list:" <<endl;
    printT(l.begin(),l.end());
    */
    //6
    //assigned it to 1 position after begin    
    cout<<"--------------it initialized using begin +1----------------" << endl;
    vector<int>::iterator it = v.begin() + 1;
    cout<<"printing from begin to iterator it:" <<endl;
    printT(v.begin(),it);
    cout<<"printing from iterator it to end:" <<endl;
    printT(it,v.end());

    //assigned it to the middle
    cout<<"---------------it initialized to point to middle---------------"<<endl;
    it=v.begin()+(v.end()-v.begin())/2;
    cout<<"printing from begin to iterator it:" <<endl;
    printT(v.begin(),it);
    cout<<"printing from iterator it to end:" <<endl;
    printT(it,v.end());

    //7 
    cout<<"1st element of array:"<<arr[0]<<endl;
    cout<<"1st element of deque:"<<d[0]<<endl;
    cout<<"1st element of vector:"<<v[0]<<endl;
    //cout<<"1st element of list:"<<l[0]<<endl;



    return static_cast<int>(status::success);
}