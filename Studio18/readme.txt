1. Yunlai Chen, Anthony Chen

2. 
code:
    int arr[] = {-2, 19, 80, -47, 80, 80, -2, 19, 19};
    int* p = arr;
    int* p2 = arr + sizeof(arr)/sizeof(arr[0]);
    copy(p, p2, ostream_iterator<int>(cout, " "));
    cout << endl;
	return static_cast<int>(status::success); 
output:
   -2 19 80 -47 80 80 -2 19 19 


3. 
code:
   vector<int> v;
   back_insert_iterator<vector<int>> it = back_inserter(v);
   copy(p, p2, it);
   cout<<"printing vector:"<<endl;
   for (auto i : v) {
     cout << i << " ";
   }
   cout << endl;

output:
   printing vector:
   -2 19 80 -47 80 80 -2 19 19 


4. 
code:
   cout<<"sorted array:"<<endl;
   sort(p, p2);
   copy(p, p2, ostream_iterator<int>(cout, " "));
   cout << endl;

output:
   sorted array:
   -47 -2 -2 19 19 19 80 80 80 



5.  
code:
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
   
output:
   repeated elements:
   -2 -2 
   19 19 19 
   80 80 80 

6. 
code:
   cout<<"sorted vector into into non-increasing order:" <<endl;
   sort(v.begin(), v.end(), greater<int>());
   copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
   cout << endl;
output:
   sorted vector into into non-increasing order:
   80 80 80 19 19 19 -2 -2 -47 


7.
code:
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

   
output:
   median: 19
   mean: 27.3333
   mode: 80

