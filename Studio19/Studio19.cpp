
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<iterator>
#include<string>
#include"function.h"

using namespace std;



int main(int argc, char *argv[])
{
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

    // pass the compare function to the set constructor
    // decltype(compare) *p = compare;
        

    // set<string, decltype(compare)*> mySet(p);
    // copy(argv, argv + argc, inserter(mySet, mySet.begin()));
    // copy(mySet.begin(), mySet.end(), ostream_iterator<string>(cout, " "));
    // cout << endl;

    // // replace with a multiset
    // multiset<string, decltype(compare)*> myMultiSet(p);
    // copy(argv, argv + argc, inserter(myMultiSet, myMultiSet.begin()));
    // copy(myMultiSet.begin(), myMultiSet.end(), ostream_iterator<string>(cout, " "));
    // cout << endl;
    

    // set<char*> mySet2;
    // copy(argv, argv + argc, inserter(mySet2, mySet2.begin()));
    // copy(mySet2.begin(), mySet2.end(), ostream_iterator<char*>(cout, " "));
    // cout << endl;

    return 0;
}


