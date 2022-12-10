1.  
    Anthony Chen, Yunlai Chen

2.  
error:
    /home/warehouse/c.yunlai/cse428_fall22/Deck-CardOOP-master/Studio16/template.h:57: 
    multiple definition of `void print<std::__cxx11::basic_string<char, std::char_traits<char>, 
    std::allocator<char> > >(std::ostream&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'

reason:
    The variadiac template function called it self recursively with less and less argument. 
    When the compiler finds a print() function which can take two arguments, 
    it can also find the non-variadiac template function. This causes multiple definition.


3. 
    Code, template specialization:   
        template <typename... Args>
        void printit(std::ostream& os, const std::string& s, const Args&... rest) {
            os << "\"" << s << "\"";
            printit(os, rest...);
            add_size(s);
        }
        

    Code, non-template:
        void printit(std::ostream& os, const std::string& s) {
            os << "\"" << s << "\"";
            add_size(s);
        }
    Main:
        string str1 = "Hello";
        printit(cout,str1);

    Output:
        "Hello"
 
4.
    Code, specialization of variadic template:
    template <typename... Args>
    void printit(std::ostream& os, const char * const s, const Args&... rest) {
        os << "[" << s << " "<< reinterpret_cast<const void *> (s) << "] ";
        printit(os,rest...);
        add_size(s);
    }

    Code, non-tmplate:
    void printit(std::ostream& os, const char * const s) {
        os << "[" << s << " "<< reinterpret_cast<const void *> (s) << "] ";
        add_size(s);
    }

    Main:
    const char *str2 = "World";
    printit(cout,str2);


    Output:
        [World 0x4035ce]

5.  
    Code, template specialization:
        template <typename... Args>
        void printit(std::ostream& os, const Foo& s, const Args&... rest) {
            os << "{" << s << "} ";
            printit(os,rest...);
            add_size(s);
        }
    code, non-template:
        void printit(std::ostream& os, const Foo& s) {
        os << "{" << s << "} ";
        add_size(s);
    }
    Output:
        {This is Foo} 
6.
    code priniting out size:
    template <typename T>
    void printit(std::ostream& os, const T& t) {
        os << t <<std::endl;
        // print the size of the arguments
        add_size(t);
        os << "size: " << count << std::endl;
        os << "size of int: " << countInt << std::endl;
        os << "size of float: " << countFloat << std::endl;
        os << "size of other: " << (count-countInt-countFloat) << std::endl;
    }


    main:
    printit(cout, str1, str2, foo1, i, f);

    output:
    "Hello"[World 0x40358e] {This is Foo} 5 5.5
    size: 80
    size of int: 4
    size of float: 4
    size of other: 72

