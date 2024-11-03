#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

template<typename T>
int partition(vector<T>& arr, int lo, int hi){
    int i = lo; int j = hi + 1;
    
    while(true){
        while(arr[++i] < arr[lo])
            if(i == hi) break;
        
        while(arr[--j] > arr[lo])
            if(j == lo) break;
        
        if(i >= j) break;
        swap(arr[i], arr[j]);
    }
    
    swap(arr[j], arr[lo]);
    return j;
}

// Finds stuff like kth smallest item
template<typename T>
T quick_select(vector<T>& arr, int k){
    k--;
    shuffle(arr.begin(), arr.end(), default_random_engine(random_device{}()));
    int lo = 0; int hi = arr.size() - 1;
    
    while(hi > lo){
        int j = partition(arr, lo, hi);
        
        if(j < k) lo = j + 1;
        else if (j > k) hi = j - 1;
        else return arr[k];
    }
    
    return arr[k];
}

int main(){
    vector<int> a = {2,1,3,4,5,6,7,8,9,10};
    int ten = quick_select(a, 1);
    cout << ten;
}






