1. 
    Anthony Chen, Yunlai Chen

2. 
    Output: 
        Hello 
        World


3.  
    Output:
        Hello (foo1)
        World (foo2)
        foo1 is less than foo2

4.  
    Code:
        in Foo class in header file:
            friend bool operator<(const Foo& foo1, const Foo& foo2);

        outside Foo class in header file:
            bool operator<(const Foo& foo1, const Foo& foo2);

        in source file:
            bool operator<(const Foo& foo1, const Foo& foo2) {
                return foo1.my_str < foo2.my_str;
            }

5.
    Error:
        error: use of overloaded operator '<' is ambiguous (with operand types 'Foo' and 'Foo')

    Explanation:
        The compiler doesn't know which operator< to use. It could be the one in the Foo class or the one outside the Foo class.

6. 
    Output:
        HelloWorldfoo1 is less than foo2
        (is slightly different from the output in question 3 because of "endl")
    Code:
        template <typename T>
        void print(std::ostream& os, const T& t) {
            os << t;
        }

7.
    Output:
        template called Hello
        mySpace called World
        foo1 is less than foo2

    Code:
        namespace mySpace {
            void print(std::ostream& os, const Foo& t) {
                os << "mySpace called ";
                os << t;
            }
        }

        print(cout, foo1);
        mySpace::print(cout, foo2);