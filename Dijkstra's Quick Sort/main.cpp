#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

template<typename T>
void DjisktraSort(vector<T>& arr, int lo, int hi){
    if(hi <= lo) {return;}
    
    int i = lo + 1, lt = lo, gt = hi;
    T v = arr[lo];
    
    while(i <= gt){
        if(arr[i] > v) {swap(arr[i], arr[gt--]);}       // Place element greater than v in spot for greater than part of array
        else if(arr[i] < v) {swap(arr[i], arr[lt++]);}  // Place element lesser than v in spot for lesser than part of array
        else {i++;}                                     // if same element then do nothing and move forward
    }
    
    DjisktraSort(arr, lo, lt - 1);                      // Sort the array containing elements less than v
    DjisktraSort(arr, gt + 1, hi);                      // Sort the array containing elements greater than v
}

/*template<typename T>
void QuickSort(vector<T>& arr, int lo, int hi){
    if(hi <= lo) return;                // If the array is of size 1 then return
    int j = partition(arr, lo, hi);     // Returns the index where the partition was placed
    
    QuickSort(arr, lo, j - 1);          // Sort the elements lower than the pivot
    QuickSort(arr, j + 1, hi);          // Sort the elements greater than the pivot
}*/

template<typename T>
void QuickSort(vector<T>& arr){
    shuffle(arr.begin(), arr.end(), default_random_engine(random_device{}()));
    DjisktraSort(arr, 0, arr.size() - 1);
}

std::vector<int> generateRandomVector(int size, int min, int max) {
    std::vector<int> vec(size);
    std::random_device rd;              // Obtain a random number from hardware
    std::mt19937 gen(rd());             // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    for (int i = 0; i < size; ++i) {
        vec[i] = distr(gen);
    }

    return vec;
}

int main() {
    int vectorSize = 1000000;           // You can adjust the size for larger/smaller vectors
    int minValue = 0;
    int maxValue = 1000000;

    std::vector<int> testVector = generateRandomVector(vectorSize, minValue, maxValue);

    // Output a small portion of the vector to check
    std::cout << "First 10 elements of the generated vector:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << testVector[i] << " ";
    }
    std::cout << std::endl;
    
    QuickSort(testVector);
    std::cout << "\nAfter sorting the first 10 elements of the generated vector:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << testVector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}





