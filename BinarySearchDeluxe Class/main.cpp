#include<iostream>
#include<vector>
#include<exception>
#include <functional>
#include<algorithm>
#include<string>
#include<random>
//#include "27880Term.cpp"

template<typename T>
void QuickSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comparator);

template<typename T>
void DjisktraSort(std::vector<T>& arr, int lo, int hi, std::function<bool(const T&, const T&)> comparator);

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

	// Unit testing (required)
	//template <typename Key>
	static void test() {
		std::vector<int> tester = { 1,1,1,1,3,4,9 };
		//int temp = BinarySearchDeluxe::firstIndexOf(tester, 1, std::less<int>());
		std::function<bool(const int&, const int&)> comparator = std::less<int>();
		std::cout << "First of 1 (0): " << BinarySearchDeluxe::firstIndexOf(tester, 1, comparator) << std::endl;
		std::cout << "Last of 1 (3): " << BinarySearchDeluxe::lastIndexOf(tester, 1, comparator) << std::endl;

        /*std::vector<Term> terms = { Term("app", 700), Term("apple", 500),Term("application", 300) };
        Term t1("app", 700);
        std::cout << "\nTesting terms array:\n";
        std::cout << "Should return 0: " << BinarySearchDeluxe::firstIndexOf(terms, t1, Term::byPrefixOrder(3)) << std::endl;
        std::cout << "Should return 2: " << BinarySearchDeluxe::lastIndexOf(terms, t1, Term::byPrefixOrder(3)) << std::endl;

        std::vector<Term> Complexterms = { Term("apple", 500), Term("app", 700), Term("app", 600), Term("application", 300) };
        // Note that Quick sort will not wrok with functors. Use built in sort if issues arise
        //std::sort(Complexterms.begin(), Complexterms.end(), Term::byPrefixOrder(3));
        QuickSort(Complexterms, Term::byPrefixOrder(3));

        std::cout << "\nTesting more complex terms: \n";
        std::cout << "Should return 0: " << BinarySearchDeluxe::firstIndexOf(Complexterms, t1, Term::byPrefixOrder(3)) << std::endl;
        std::cout << "Should return 3: " << BinarySearchDeluxe::lastIndexOf(Complexterms, t1, Term::byPrefixOrder(3)) << std::endl;

        std::vector<Term> fraud;
        std::cout << "\nTesting exception handling: \n";
        try {
            firstIndexOf(fraud, t1, Term::byReverseWeightOrder());
        }
        catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }*/
	}
};

// Using the 3 way quicksort algorithm to avoid issues with duplicates.Slight modification of reducing number of functions and adding comparator
template<typename T>
void DjisktraSort(std::vector<T>& arr, int lo, int hi, std::function<bool(const T&, const T&)> comparator) {
    if (hi <= lo) { return; }

    int i = lo + 1, lt = lo, gt = hi;
    T v = arr[lo];

    while (i <= gt) {
        if (comparator(arr[i], v)) {
            std::swap(arr[i++], arr[lt++]);
        }
        else if (comparator(v, arr[i])) {
            std::swap(arr[i], arr[gt--]);
        }
        else {
            i++;
        }
    }

    DjisktraSort(arr, lo, lt - 1, comparator);
    DjisktraSort(arr, gt + 1, hi, comparator);
}

template<typename T>
void QuickSort(std::vector<T>& arr, std::function<bool(const T&, const T&)> comparator) {
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(std::random_device{}()));

    DjisktraSort(arr, 0, arr.size() - 1, comparator);
}

int main() {
    BinarySearchDeluxe::test();
    return 0;
}