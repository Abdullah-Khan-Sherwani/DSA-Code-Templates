#include <iostream>
#include<vector>
#include<iomanip>
using namespace std;

template<typename T>
void merge(vector<T>& a, vector<T>& aux, int lo, int mid, int hi){
    int i = lo, j = mid + 1;
    
    for(int k = lo; k <= hi; k++){
        if(i > mid) aux[k] = a[j++];
        else if(j > hi) aux[k] = a[i++];
        else if(a[j] < a[i]) aux[k] = a[j++];
        else a[k] = a[i++];
    }
}

template<typename T>
void merge_sort(vector<T>& a, vector<T>& aux, int lo, int hi){
    if(hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    
    merge_sort(aux, a, lo, mid);
    merge_sort(aux, a, mid + 1, hi);
    
    if (a[mid] <= a[mid + 1]) {
		// If already sorted, just copy the relevant portion.
		copy(a.begin() + lo, a.begin() + hi + 1, aux.begin() + lo);
		return;
	}
    
    merge(a, aux, lo, mid, hi);
}

template<typename T>
void merge_sort(vector<T>& a){
    vector<T> aux = a;
    
    merge_sort(aux, a, 0, a.size() - 1);
}

int main() {
	vector<int> arr = { 1,3,5,7,9,2,4,6,8,10, 11, 12, 13, 14};

	cout << "Before Sorting:\n";
	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";

	cout << "\nAfter Sorting:\n";
	merge_sort(arr);

	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";
}