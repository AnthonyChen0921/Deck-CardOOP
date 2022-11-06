1.  
    Anthony Chen, Yunlai Chen

2.  
    Hello World This is Foo 5 5.5

3. 
    Code:
        template <typename T, typename... Args>
        void print(std::ostream& os, const T& t, const Args&... rest) {
            os << t << " ";
            print(os, rest...);
        }

    Main:
        print(cout, str1, str2, foo1, i, f);

    Output:
        Hello World This is Foo 5 5.5

4.
    Code:
        template <typename... Args>
        void print2(std::ostream& os, const Args&... rest) {
            os << sizeof...(rest) << " ";
            print(os, rest...);
        }

    Output:
        5 Hello World This is Foo 5 5.5

5.  
    Code:
        template <typename T>
        const T& add_size(const T& t) {
            count += sizeof(t);
            return t;
        }

    Output:
        Hello World This is Foo 5 5.5 
        size: 4
        size: 28
        size: 36
        size: 60