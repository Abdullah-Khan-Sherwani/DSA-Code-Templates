#include<iostream>
#include<vector>
#include<exception>
#include <functional>
#include<algorithm>
#include<string>
#include<random>

class BinarySearchDeluxe {
public:
	// Returns the index of the first key in the sorted array that is equal to the search key.
	template <typename Key>
	static int firstIndexOf(const std::vector<Key>& a, const Key& key, std::function<bool(const Key&, const Key&)> comparator) {
		if (a.empty() || !comparator) { throw std::invalid_argument("Invalid or empty arguments"); };
		//Key result;
		
		// Will take time complexity to atleast nlogn but how else am I supposed to ensure a sorted array inside the class otherwise?
		//sort(a.begin(), a.end(), comparator);		// !!!!!!!!														

		int lo = 0; int hi = a.size() - 1;
		while (hi >= lo) {
			int mid = lo + (hi - lo) / 2;

			if (comparator(a[mid], key)) {
				lo = mid + 1;
			}
			else if(comparator(key, a[mid])) {
				hi = mid - 1;
			}
			else {
				if (mid == 0 || comparator(a[mid - 1], key)) {
					return mid;
				}
				hi = mid - 1;
			}
		}

		return -1;
	}

	// Returns the index of the last key in the sorted array that is equal to the search key.
	template <typename Key>
	static int lastIndexOf(const std::vector<Key>& a, const Key& key, std::function<bool(const Key&, const Key&)> comparator) {
		if (a.empty() || !comparator /* || !key  */ ) { throw std::invalid_argument("Invalid or empty arguments"); };
		//Key result;

		// Will take time complexity to atleast nlogn but how else am I supposed to ensure a sorted array inside the class otherwise?
		//sort(a.begin(), a.end(), comparator);		// !!!!!!!!														

		int lo = 0; int hi = a.size() - 1;
		while (hi >= lo) {
			int mid = lo + (hi - lo) / 2;

			if (comparator(a[mid], key)) {
				hi = lo = mid + 1;
			}
			else if (comparator(key, a[mid])) {
				hi = mid - 1;
			}
			else {
				if (mid == a.size() - 1 || comparator(key, a[mid + 1])) {
					return mid;
				}
				lo = mid + 1;
			}
		}

		return -1;
	}
};

int main() {
    int key;
    std::cin >> key;
    
    std::vector<int> test = {1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 5, 6, 6, 6, 6, 6};
    std::function<bool(const int&, const int&)> comparator = [](const int& a, const int& b) {
        return a < b;
    };
    
    int first = BinarySearchDeluxe::firstIndexOf(test, key, comparator);
    int last = BinarySearchDeluxe::lastIndexOf(test, key, comparator);
    std::cout << first << " " << last << std::endl;
    
    int span = (last - first) + 1;
    std::cout << ((span > test.size() / 4) ? "Yes" : "No");
}