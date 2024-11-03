#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

template<typename T>
void merge(vector<T>& a, vector<T>& aux, int lo, int mid, int hi) {
	int i = lo, j = mid + 1;

	for (int k = lo; k <= hi; k++) {
		if (i > mid) a[k] = aux[j++];
		else if (j > hi) a[k] = aux[i++];
		else if (aux[j] < aux[i]) a[k] = aux[j++];
		else a[k] = aux[i++];
	}
}

template<typename T>
void merge_sortBU(vector<T>& a){
    vector<T> aux = a;
    int N = a.size();
    
    for(int sz = 1; sz < N; sz += sz){
        for(int lo = 0; lo < N - sz; lo += sz + sz){
            merge(a, aux, lo, lo + sz - 1, min(lo + sz + sz - 1, N - 1));
        }
    }
}

int main() {
	vector<int> arr = { 1,3,5,7,9,2,4,6,8,10, 11, 12, 13};

	cout << "Before Sorting:\n";
	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";

	cout << "\nAfter Sorting:\n";
	merge_sortBU(arr);

	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";
}