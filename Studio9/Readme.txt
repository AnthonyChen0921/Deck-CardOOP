1.
    Anthony Chen, Yunlai Chen

2. 
    (1) Output:
        Default constructor called
        Address of the object: 0x16d7bb3f0
        id: 1
        Copy constructor called
        Address of the object: 0x16d7bb3e8
        id: 1
        Destructor called
        Address of the object: 0x16d7bb3e8
        id: 1
        Destructor called
        Address of the object: 0x16d7bb3f0
        id: 1

    (2) Declaration and Definition of object
        class Object
        {
        public:
            inline static size_t numOfObj = 0;
            size_t id;
            // declare a defualt constructor
            Object();
            // declare a copy constructor
            Object(const Object &p);
            // declare a destructor
            ~Object();

        };

        // define a defualt constructor
        Object::Object(){
            numOfObj++;
            id = numOfObj;
            cout << "Default constructor called" << endl;
            cout << "Address of the object: " << this << endl;
            cout << "id: " << id << endl;
        }

        //declare a copy constructor
        Object::Object(const Object &p){
            numOfObj++;
            id = p.id;
            cout << "Copy constructor called" << endl;
            cout << "Address of the object: " << this << endl;
            cout << "id: " << id << endl;
        }

        // declare a destructor
        Object::~Object() {
            std::cout << "Destructor called" << std::endl;
            std::cout << "Address of the object: " << this << std::endl;
            std::cout << "id: " << id << std::endl;
        }

    (3) Main.cpp:
        // declare an object
        Object obj1;
        // copy construct another object of that type from it
        Object obj2 = obj1;


3.  Output:
        Default constructor called
        Address of the object: 0x11e606770
        id: 1
        Default constructor called
        Address of the object: 0x11e606778
        id: 2
        Default constructor called
        Address of the object: 0x11e606780
        id: 3
        Destructor called
        Address of the object: 0x11e606780
        id: 3
        Destructor called
        Address of the object: 0x11e606778
        id: 2
        Destructor called
        Address of the object: 0x11e606770
        id: 1

    After remove the [] after the delete keyword, make produce the error as following:
        Studio9.cpp:16:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete]
            delete obj;
            ^
                []
        Studio9.cpp:15:19: note: allocated with 'new[]' here
            Object *obj = new Object[3];
                        ^
        1 warning generated.

    After run the program with such warning, the program exit with non zero code:
        Default constructor called
        Address of the object: 0x13b606770
        id: 1
        Default constructor called
        Address of the object: 0x13b606778
        id: 2
        Default constructor called
        Address of the object: 0x13b606780
        id: 3
        Destructor called
        Address of the object: 0x13b606770
        id: 1
        studio9(82635,0x1052c8580) malloc: *** error for object 0x13b606770: pointer being freed was not allocated
        studio9(82635,0x1052c8580) malloc: *** set a breakpoint in malloc_error_break to debug
        zsh: abort      ./studio9

    Explanation:
        delete will only invoke the destructor of the first element of the obj array we declared
        delete[] will invoke the each destructor of the elements of the obj array we declared

4.  Output:
        Same as output 2

    Code:
        shared_ptr<Object> obj1 = make_shared<Object>();
        shared_ptr<Object> obj2 = make_shared<Object>(*obj1);


5. Output:
        Default constructor called
        Address of the object: 0x15a606778
        id: 1
        Copy constructor called
        Address of the object: 0x15a606798
        id: 1
        Print function called
        Address of the object: 0x15a606778
        id: 1
        Destructor called
        Address of the object: 0x15a606798
        id: 1
        Destructor called
        Address of the object: 0x15a606778
        id: 1

6.  Main:
        shared_ptr<Object> obj1 = make_shared<Object>();
        shared_ptr<Object> obj2 = make_shared<Object>(*obj1);
        weak_ptr<Object> obj3 = obj1;


        cout << "About to assign obj1 to obj2" << endl;
        obj1 = obj2;
        cout << "Done assigning obj1 to obj2" << endl;
        

        shared_ptr<Object> obj4 = obj3.lock();

        if (obj4 == nullptr){
            cout << "The weak_ptr no longer points to a valid object" << endl;
        }
        else{
            obj4->print();
        }
        obj4 = nullptr;


    Output:
        Default constructor called
        Address of the object: 0x125e06778
        id: 1
        Copy constructor called
        Address of the object: 0x125e06798
        id: 1

        About to assign obj1 to obj2
        Destructor called
        Address of the object: 0x125e06778
        id: 1
        Done assigning obj1 to obj2

        The weak_ptr no longer points to a valid object
        Destructor called
        Address of the object: 0x125e06798
        id: 1   

    As we take a closer look at where is about to assign obj1 to obj2, the shared_ptr automatically invoke the destructor of obj1,
    which is going to be destroied because obj1 will be replace by obj2, and the weak_ptr will no longer point to a valid object(obj1).
    The shared_ptr takes care of the memory management of the object without any pointer to the object.

    The counter for shared_ptr obj1 became 0 when we assign obj1 to obj2, which means the shared_ptr obj1 will be destroied.


7.  Unique_ptr

    Output:
        Default constructor called
        Address of the object: 0x152e06760
        id: 1
        Print function called
        Address of the object: 0x152e06760
        id: 1
        Print function called
        Address of the object: 0x152e06760
        id: 1
        Destructor called
        Address of the object: 0x152e06760
        id: 1