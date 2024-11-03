#include<iostream>
#include <vector>
#include <random>
#include <iomanip>
#include<algorithm>
using namespace std;
static int threshold = 10;

// without copying between a and aux
template<typename T>
void InsertionSort(vector<T>& a, int lo, int hi) {
	for (int i = lo; i <= hi; i++) {
		for (int j = i; j > lo && a[j] < a[j - 1]; j--) {
			if (a[j] < a[j - 1]) {
				swap(a[j], a[j - 1]);
			}
			else {
				break;
			}
		}
	}
}

template<typename T>
void merge(const vector<T>& a, vector<T>& aux, int lo, int mid, int hi) {
	int i = lo, j = mid + 1;

	for (int k = lo; k <= hi; k++) {
		if (i > mid) aux[k] = a[j++];
		else if (j > hi) aux[k] = a[i++];
		else if (a[j] < a[i]) aux[k] = a[j++];
		else aux[k] = a[i++];
	}
}

template<typename T>
void sort(vector<T>& a, vector<T>& aux, int lo, int hi) {
	if (hi <= lo + threshold) {
		return InsertionSort(aux, lo, hi);  // Perform insertion sort directly on `aux`.
	}

	int mid = lo + (hi - lo) / 2;

	sort(aux, a, lo, mid);      // Recursive sort on the left half.
	sort(aux, a, mid + 1, hi);  // Recursive sort on the right half.

	if (a[mid] <= a[mid + 1]) {
		// If already sorted, just copy the relevant portion.
		copy(a.begin() + lo, a.begin() + hi + 1, aux.begin() + lo);
		return;
	}

	// Perform merge, merging from `a` into `aux`.
	merge(a, aux, lo, mid, hi);
}

template<typename T>
void mergesort(vector<T>& a) {
	vector<T> aux = a;  // Initialize aux with the same size and values.
	sort(aux, a, 0, a.size() - 1);  // Start sorting with `a` as the destination.
}

/*template<typename T>
void InsertionSort(vector<T>& a, int lo, int hi) {
	for (int i = lo; i <= hi; i++) {
		for (int j = i; j > lo && a[j] < a[j - 1]; j--) {
			if (a[j] < a[j - 1]) {
				swap(a[j], a[j - 1]);
			}
			else {
				break;
			}
		}
	}
}

template<typename T>
void merge(vector<T>& a, vector<T>& aux, int lo, int mid, int hi) {
	int i = lo, j = mid + 1;
	copy(a.begin(), a.end(), aux.begin());

	for(int k = lo; k <= hi; k++) {
		if(i > mid) a[k] = aux[j++];
		else if(j > hi) a[k] = aux[i++];
		else if(a[j] < a[i]) a[k] = aux[j++];
		else a[k] = aux[i++];
	}
}

template <typename T>
void sort(vector<T>& a, vector<T>& aux, int lo, int hi) {
	if(hi <= lo + threshold) {
	   	return InsertionSort(a, lo, hi);
	   	//return;
	}

	int mid = lo + (hi - lo) / 2;
	sort(a, aux, lo, mid);
	sort(a, aux, mid + 1, hi);

	if(a[mid] <= a[mid + 1]) {
		for(int k = lo; k <= hi; k++) {
			aux[k] = a[k];
			return;
		}
	}
	else {
		merge(a, aux, lo, mid, hi);
	}
}

template<typename T>
void mergesort(vector<T>& a) {
	vector<T> aux(a.size());
	sort(a, aux, 0, a.size() - 1);
}*/

int main() {
	vector<int> arr = { 1,3,5,7,9,2,4,6,8,10, 11, 12, 13, 14};

	cout << "Before Sorting:\n";
	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";

	cout << "\nAfter Sorting:\n";
	mergesort(arr);

	for (const auto& x : arr)
		std::cout << std::setw(2) << x << " ";
}