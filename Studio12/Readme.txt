1. 
    Anthony Chen, Yunlai Chen

2. 
    Struct:
        struct myStruct
        {
            int myInt;
            myStruct(int myInt_) : myInt(myInt_) { }
        };
    Main:
        myStruct a(1);
        myStruct b(2);
        cout << a.myInt << " " << b.myInt << endl;

    Output:
        1 2

3. 
    myStruct(const myStruct&) = delete;
    myStruct& operator=(const myStruct&) = delete;
    ~myStruct() = delete;

    The destructor cannot be deleted because it is implicitly called when the object goes out of scope.

4.  
    Code:
        std::swap(a, b);
        cout << a.myInt << " " << b.myInt << endl;

    Output:
        2 1

5.  
    Code:
        // myStruct(const myStruct&) = delete;
        // myStruct& operator=(const myStruct&) = delete;
        // ~myStruct() = delete;

    Explanation:
        swap function needs to copy the object to a temporary object, so the copy constructor and assignment operator must be defined.

        Q: whether the std::swap function template imposes additional requirements on the struct type?
        A: Yes, the struct type must have a copy constructor and assignment operator to be able to use swap.

6. 
    Struct:
        template <typename T = int>
        struct myStruct
        {
            T myInt;
            myStruct(T myInt_) : myInt(myInt_) { }
        };
    Main:
        myStruct<> a(1);
        myStruct<> b(2);


7.  
    friend ostream& operator<<(ostream& os, const myStruct<T>& obj);

    template <typename T>
    ostream& operator<<(ostream& os, const myStruct<T>& obj)
    {
        os << obj.myInt;
        return os;
    }

    Output:
        1 2
        2 1