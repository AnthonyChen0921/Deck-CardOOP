
#include <iostream>
#include <string>
#include "Foo.h"
#include "template.h"

using namespace std;





int main()
{
    int arr[] = {-2, 19, 80, -47, 80, 80, -2, 19, 19};
    //Declare pointer variables that are initialized to point to the first element in the array, and just past the end of the array, respectively; then use the copy algorithm to print out the contents of the array by passing it those pointers and a variable of type ostream_iterator<int> that is initialized with cout and a string like " " to print between each of the integer values in the array.
    int* p = arr;
    int* p2 = arr + sizeof(arr);
    copy(p, p2, ostream_iterator<int>(cout, " "));
    cout << endl;
    // declare a container variable of type vector<int> and an iterator variable of type back_insert_iterator<vector<int> > and pass the pointers from the previous exercise and that iterator into a call to the copy so that it will copy the contents of the array into the vector, and then use other appropriate iterators to print out the contents of the vector to the standard output stream (again with spaces between the elements as in the previous exercise)
    vector<int> v;
    back_insert_iterator<vector<int>> it = back_inserter(v);
    copy(p, p2, it);
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    //Use the sort algorithm to sort the integers in your array from the previous exercises into non-decreasing order (smallest to largest), and then again use the copy algorithm to have your program print out the contents of the sorted array.
    sort(p, p2);
    copy(p, p2, ostream_iterator<int>(cout, " "));
    cout << endl;
    //Use the adjacent_find algorithm to locate and print out each range of repeated elements in the sorted array from the previous exercise on a separate line
    int* p3 = adjacent_find(p, p2);
    while (p3 != p2) {
        cout << *p3 << " ";
        p3 = adjacent_find(p3 + 1, p2);
    }
    cout << endl;
    //Sort the contents of the vector into non-increasing order (largest to smallest) by passing an object of type greater<int> as a third parameter to the sort algorithm and then again use the copy algorithm to print out the contents of the sorted vector.
    sort(v.begin(), v.end(), greater<int>());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //Use the count and accumulate algorithms to compute the median (middle value), mean (average), and mode (most frequent value) over the integers in the sorted vector from the previous exercise.
    cout << "median: " << *(v.begin() + v.size() / 2) << endl;
    cout << "mean: " << accumulate(v.begin(), v.end(), 0) / v.size() << endl;
    //use count to calculate the mode
    int mode = 0;
    int mode_count = 0;
    for (auto i : v) {
        int count = count_if(v.begin(), v.end(), [i](int j) {return i == j; });
        if (count > mode_count) {
            mode = i;
            mode_count = count;
        }
    }
    int mode = *max_element(v.begin(), v.end(), [](int a, int b) {return count(v.begin(), v.end(), a) < count(v.begin(), v.end(), b); });
    cout << "mode: " << mode << endl;

    //Use the adjacent_find algorithm to locate and print out each range of repeated elements in the sorted array from the previous exercise on a separate line
    int* p3 = adjacent_find(p, p2);
    while (p3 != p2) {
        cout << *p3 << endl;
        p3 = adjacent_find(p3 + 1, p2);
    }
}