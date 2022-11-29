1.  
    Anthony Chen, Yunlai Chen

2.  

main function:
    // 1. declare a C-style array of int and initialize it with different values.
    int arr[5] = { 1, 2, 3, 4, 5 };
    std::cout<<"size of array: "<<sizeof(arr)<<std::endl;
    std::cout<<"size of data type that array contains:" << sizeof(arr[0]) << std::endl;
    return static_cast<int>(status::success);

output:
size of array: 20
size of data type that array contains:4


3. 
Code:
    //2.initialize a pointer that points just past the end of the array
    int* end = arr + sizeof(arr)/sizeof(arr[0]);

    //write a for loop  to move a pointer to int from start of the array to just past the end of the array,
    // and prints out each value .
    for (int* i = arr; i != end; i++)
    {
        std::cout << *i << std::endl;
    }

Output:
    1
    2
    3
    4
    5
 
4.
Code:
    template <typename T>
    void printT(T t1, T t2){
        for (T t = t1; t != t2; t++)
        {
            std::cout << *t << std::endl;
        }
    }
    Output:
        5 Hello World This is Foo 5 5.5

call:
    printT(arr,arr + sizeof(arr)/sizeof(arr[0]));


5.  
Code:
    deque<int> d;
    vector<int> v;
    list<int> l;
    for (int* i = arr; i != end; i++)
    {
        d.emplace_back(*i);
        v.emplace_back(*i);
        l.emplace_back(*i);
    }
    cout<<"deque:" <<endl;
    printT(d.begin(),d.end());
    cout<<"vector:" <<endl;
    printT(v.begin(),v.end());
    cout<<"list:" <<endl;
    printT(l.begin(),l.end());

Output:
    deque:
    1
    2
    3
    4
    5
    vector:
    1
    2
    3
    4
    5
    list:
    1
    2
    3
    4
    5


6
code:   
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

output:
    --------------it initialized using begin +1----------------
    printing from begin to iterator it:
    1
    printing from iterator it to end:
    2
    3
    4
    5
    ---------------it initialized to point to middle---------------
    printing from begin to iterator it:
    1
    2
    printing from iterator it to end:
    3
    4
    5
7. 
(1)  deque and vector support the array indexing container.
(2) list does not support [] operator.
    because it is a doubly linked list, and the [] operator is O(n) for a doubly linked list. 
    So ISO C++ standard specifically mentions that all STL sequences that support operator[] 
    should do it in O(n), which is achievable for vector and deque, but not list.

