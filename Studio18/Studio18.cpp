

#include <iostream> 
#include <fstream>  
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Studio18.h"
using namespace std; 

int main() {
    //2
    int arr[] = {-2, 19, 80, -47, 80, 80, -2, 19, 19};
    int* p = arr;
    int* p_end = arr + sizeof(arr)/sizeof(arr[0]);
    copy(p, p_end, ostream_iterator<int>(cout, " "));
    cout << endl;
    //3
    vector<int> v;
    back_insert_iterator<vector<int>> it = back_inserter(v);
    copy(p, p_end, it);
    cout<<"printing vector:"<<endl;
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    //4
    cout<<"sorted array:"<<endl;
    sort(p, p_end);
    copy(p, p_end, ostream_iterator<int>(cout, " "));
    cout << endl;
    
    //5
    cout<<"repeated elements:"<<endl;
    int* p3 = adjacent_find(p, p_end);
    auto tmp=p3;
    while (p3 != p_end) {
        tmp=p3;
        while(tmp!=p_end && *tmp==*p3){
            cout<< *tmp <<" ";
            tmp++;
        }
        cout<<endl;
        p3 = adjacent_find(tmp, p_end);
    }
    cout << endl;

    //6
    cout<<"sorted vector into into non-increasing order:" <<endl;
    sort(v.begin(), v.end(), greater<int>());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //7
    int med=*(v.begin() + v.size() / 2) ;
    cout << "median: " << med << endl;
    float vmean=(float) accumulate(v.begin(), v.end(), 0) / v.size();
    cout << "mean: " << vmean << endl;
    
    int mode = 0;
    int mode_count = 0;
    for (auto i : v) {
        int count = count_if(v.begin(), v.end(), [i](int j) {return i == j; });
        if (count > mode_count) {
            mode = i;
            mode_count = count;
        }
    }
    cout << "mode: " << mode << endl;

	return static_cast<int>(status::success); 

}
