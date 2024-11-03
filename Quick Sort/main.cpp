#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

template<typename T>
int partition(vector<T>& arr, int lo, int hi){
    int i = lo; int j = hi + 1;
    
    while(true){
        while(arr[++i] < arr[lo])       // Scanning from left to right until an element greater than a[lo] is hit
            if(i == hi) break;
        
        while(arr[--j] > arr[lo])       // Scanning from right to left until an element smaller than a[lo] is reached
            if(j == lo) break;
        
        if(i >= j) break;               // Break if the pointers cross
        
        swap(arr[i], arr[j]);           // Swap the greater element in arr[i] with the smaller element in arr[j]; this way
    }                                   // all the smaller and greater elements will be positioned on one side of the pivot 
    
    swap(arr[lo], arr[j]);              // Finally place the pivot element to it's rightful position; between the elements that 
                                        // are greater than it and those that are smaller than it
                                        
    return j;                           // The true position of the pivot element
}

template<typename T>
void QuickSort(vector<T>& arr, int lo, int hi){
    if(hi <= lo) return;                // If the array is of size 1 then return
    int j = partition(arr, lo, hi);     // Returns the index where the partition was placed
    
    QuickSort(arr, lo, j - 1);          // Sort the elements lower than the pivot
    QuickSort(arr, j + 1, hi);          // Sort the elements greater than the pivot
}

template<typename T>
void QuickSort(vector<T>& arr){
    shuffle(arr.begin(), arr.end(), default_random_engine(random_device{}()));
    QuickSort(arr, 0, arr.size() - 1);
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





