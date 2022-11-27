1. 
    Anthony Chen, Yunlai Chen

2.
    Code:
        set<string> mySet;
        copy(argv, argv + argc, inserter(mySet, mySet.begin()));
        copy(mySet.begin(), mySet.end(), ostream_iterator<string>(cout, " "));
    Explain:
        The container enforced uniqueness of the keys in the container since it's a set, no duplicates allowed.
    Input: 
        ./studio19 1 2 3 4
    Output: 
        ./studio19 1 2 3 4 

3.      
    Output is the same. No difference observed in this case.

4. 
    Input: ./studio19 abc hello wwwooorld 1 bca acv
    Output: ./studio19 1 abc acv bca hello wwwooorld 

    Function Code:
        bool compare(const std::string &s1, const std::string &s2) {return s1 < s2;}

    Main Code:
        decltype(compare) *p = compare;
        set<string, decltype(compare)*> mySet(p);
        copy(argv, argv + argc, inserter(mySet, mySet.begin()));
        copy(mySet.begin(), mySet.end(), ostream_iterator<string>(cout, " "));
        cout << endl;

    Explanation:
        The set is now sorted by the compare function. The string is sorted by length, then by alphabetical order, from shortest to longest, and then from a to z.

5.
    Input:
        ./studio19 abc hello wwwooorld 1 bca acv abc
    Output:
        ./studio19 1 abc acv bca hello wwwooorld 
        ./studio19 1 abc abc acv bca hello wwwooorld

    Explanation:
        Given two abc strings in the input, 
        set only stores one abc string, set does not allow duplicates.
        multiset stores both abc strings, since multiset allows duplicates.

6.
    Code;
        multiset<string> mset;
        copy(argv + 1, argv + argc, inserter(mset, mset.begin()));
        string s = "hello";
        pair<multiset<string>::iterator, multiset<string>::iterator> p = mset.equal_range(s);
        copy(p.first, p.second, ostream_iterator<string>(cout, " "));
        cout << endl;
    Output:
        ./studio19 abc hello 124 hello world good halo
        hello hello 

7.
    Code:
        multiset<string> mset;
        copy(argv + 1, argv + argc, inserter(mset, mset.begin()));
        string s = "hello";
        pair<multiset<string>::iterator, multiset<string>::iterator> p = mset.equal_range(s);
        // print out equal_range result
        cout << "equal_range result: " << endl;
        copy(p.first, p.second, ostream_iterator<string>(cout, " "));
        mset.erase(p.first);
        // mset.erase(p.first, p.second);
        // print out the container
        cout << endl << "after erase: " << endl;
        copy(mset.begin(), mset.end(), ostream_iterator<string>(cout, " "));
        cout << endl;

    Erase first iterators - Output:
        ./studio19 abc hello 124 hello world good halo hello 21
        equal_range result: 
        hello hello hello 
        after erase: 
        124 21 abc good halo hello hello world 

    Erase both iterators - Output:
        ./studio19 abc hello 124 hello world good halo hello 21
        equal_range result: 
        hello hello hello 
        after erase: 
        124 21 abc good halo world 

    Explain:
        erase first iterator - removed the first hello string given in command line
        erase both iterators - removed all hello strings given in command line since given the the range of iterators to erase