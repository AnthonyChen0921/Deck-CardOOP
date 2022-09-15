1. Anthony Chen, Yunlai Chen

2.   Without constructor output (Build with c++17):

        [chenerdong@linuxlab006 studio5]$ make
        g++ -o studio5 -DUNIX   -Wall -W -g -std=c++17 Studio5.cpp 
        Studio5.cpp: In function ‘int main()’:
        Studio5.cpp:15:28: warning: ‘p1.point::x’ may be used uninitialized in this function [-Wmaybe-uninitialized]
            cout << "p1.x: " << p1.x << endl;
                                    ^
        Studio5.cpp:16:28: warning: ‘p1.point::y’ may be used uninitialized in this function [-Wmaybe-uninitialized]
            cout << "p1.y: " << p1.y << endl;
                                    ^
        [chenerdong@linuxlab006 studio5]$ ./studio5 
        p1.x: 0
        p1.y: 0
        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    With default constructor output:
        [chenerdong@linuxlab006 studio5]$ ./studio5 
        p1.x: 0
        p1.y: 0
        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    Before we define the default constructor, we get complier warning about the uninitialized variables.
    The output of x and y are both 0, however.

    After we define the default constructor, the output of x is 0 and y is 0.
    The random number in y came from the memory address of y. 


3.  when the class variable is declared privately, we cannot access the variable outisde of the class.
    When the class variable is declared publicly, we can access the variable outside of the class.
    when the class variable is declared protected, we can't access the variable outside of the class either.


    Difference between Struct and Class:
    1. Struct is default public, Class is default private.
    2. Struct can't have inheritance, Class can have inheritance.

4. 
    When call the mutator for const Point p2, error message:

                    Studio5 % make
                    g++ -o studio5 -DUNIX   -Wall -W -g -std=c++17 Studio5.cpp 
                    Studio5.cpp:23:5: error: 'this' argument to member function 'setX' has type 'const Point', but function is not marked const
                        p2.setX(10).setY(20);
                        ^~
                    ./Studio5.h:21:12: note: 'setX' declared here
                        Point& setX(int x){
                            ^
                    1 error generated.
                    make: *** [studio5] Error 1


    (1) code:
                main.cpp:
                    // delcare a point and print x,y
                    Point p1;
                    cout << "p1.x: " << p1.getX() << endl;
                    cout << "p1.y: " << p1.getY() << endl;
                    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

                    // call accessor and mutator
                    const Point p2(1, 2);
                    p1.setX(10).setY(20);
                    cout << "p1.x: " << p1.getX() << endl;
                    cout << "p1.y: " << p1.getY() << endl;

    
    (2) Using mutator for Point p1 derived following output:

                    Studio5 % ./studio5
                    p1.x: 0
                    p1.y: 0
                    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                    p1.x: 10
                    p1.y: 20


    We could see from the cout that the x, y value of p1 is changed after calling the mutator.



5. 
    Output:

        m.x is 0 and m.y is 0
        m.x is 7 and m.y is 3
        n.x = 7 and n.y = 3

    Explain:
        In the first line, point m is initialized with default constructor.
        In the second line, point m call the mutator to change the value of x and y.
        In the third line, point n is initialized with the copy constructor by passing point m as parameter.
        The "complier defualt copy constructor" copied the value of x and y from point m to point n.


6.
    Output:

        m.x is 0 and m.y is 0
        m.x is 7 and m.y is 3
        n.x = 7 and n.y = 3

    Explain:
        We observed the same output as in question 5.
        The copy constructor we defined function the same way as the complier defualt copy constructor.



7. 
    Code: 
        Point m; // default construction

        m.foo(m); 

        cout << "before mutator" << endl;

        m.setX(7).setY(3); // chained use of mutator functions

        m.foo(m); 

        cout << "before copy constructor" << endl;

        Point n(m); // copy construction

        n.foo(n);

    Output: 
        Studio5 % ./studio5
        Default constructor called
        Address of the object: 0x16db833f4
        x: 0
        y: 0
        Copy constructor called
        Address of the object: 0x16db833ec
        x: 0
        y: 0
        Copy constructor called
        Address of the object: 0x16db833e4
        x: 0
        y: 0
        before mutator
        Copy constructor called
        Address of the object: 0x16db833dc
        x: 7
        y: 3
        Copy constructor called
        Address of the object: 0x16db833d4
        x: 7
        y: 3
        before copy constructor
        Copy constructor called
        Address of the object: 0x16db833cc
        x: 7
        y: 3
        Copy constructor called
        Address of the object: 0x16db833c4
        x: 7
        y: 3
        Copy constructor called
        Address of the object: 0x16db833bc
        x: 7
        y: 3


    Explain: 
        Point foo(Point a) call the copy constructor twice.

        Before mutator:
            Default constructor called at first line since we declare a point m.
            Copy constructor called at second line since we pass point m as parameter to the function foo.
            Copy constructor called at third line since we return point m from the function foo.

        Before copy constructor:
            copy constructor called twice since we call foo()

        After copy constructor:
            One copy constructor called since we use the copy constructor to initialize point n.
            Another two copy constructor called since we call foo() again.


8.  Complier complained about the private constructor of class Point
    Make failed, cannot run the program.