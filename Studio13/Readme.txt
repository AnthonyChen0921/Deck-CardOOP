1.
    Yunlai Chen, Anthony Chen

2. 
    Foo Object at: 0x1476067d0 name: hello
    Foo Object at: 0x1476067d0 name: hello
    Foo Object at: 0x1476067d0 name: hello
    Foo Object at: 0x1476067d0 name: hello destroyed

3.  
    Code:
        template <typename T>
        typename std::remove_reference<T>::type&& myMove(T&& t){
            return static_cast<typename std::remove_reference<T>::type&&>(t);
        }

    Output:
        Foo Object at: 0x1316067d0 name: hello
        Foo Object at: 0x1316067d0 name: hello
        Foo Object at: 0x1316067d0 name: hello
        Foo Object at: 0x1316067d0 name: hello destroyed

4.  
    Code:
        unique_ptr<Foo> foo1 = make_unique<Foo>("hello");

    Output is the same as before

5.
    Code:
        cout << typeid(std::remove_reference<decltype(*foo1)>::type).name() << endl;

    Output:
        Foo Object at: 0x154e067d0 name: hello
        Foo Object at: 0x154e067d0 name: hello
        Foo Object at: 0x154e067d0 name: hello
        3Foo
        Foo Object at: 0x154e067d0 name: hello destroyed

