#include<iostream>
#include<vector>
#include<algorithm>
#include<exception>
using namespace std;

/*Uses all elements in the vector including 0th element. Therefore formula for firt child is (2k + 1) and for second child is (2k + 2). For parent the 
formula is [(k - 1) / 2]. Errors in inheritance so this-> pointer had to be used in minheap class*/

template<typename T>
class MaxHeap {
public:
    MaxHeap() {}

    void insert(T value) {                                      
        heap.push_back(value);
        swim(heap.size() - 1);                                  // Place the value according to it's magnitude
    }

    void buildHeap(vector<T>& arr) {
        heap = arr;                                             // Load the array into the heap for heapsort
        
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            sink(i);
        }
    }

    T extractMax() {
        if (isEmpty()) throw runtime_error("Heap is Empty");

        T max = heap[0];
        swap(heap[0], heap.back());
        heap.pop_back();                                        // Remove the last element (which was the max)
        sink(0);
        return max;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    size_t Size() const {
        return heap.size();
    }

    vector<T> getHeap() const {
        return heap;
    }

protected:
    vector<T> heap;

    void swim(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            
            if (heap[index] <= heap[parent]) break;             // Check if parent node is greater than child node
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void sink(int index) {
        int n = heap.size();
        
        while (2 * index + 1 < n) {
            int child = 2 * index + 1;
            
            if (child + 1 < n && heap[child] < heap[child + 1]) {
                child++;                                        // Check which child is larger for efficient swap; could also use std::max
            }
            
            if (heap[index] >= heap[child]) break;
            swap(heap[index], heap[child]);
            index = child;
        }
    }
};

template<typename T>
class MinHeap : public MaxHeap<T> {
public:
    void insert(T value) {
        this->heap.push_back(value);                            // Use this-> to access the inherited heap
        swim(this->heap.size() - 1);
    }  
    
    T extractMin() {
        if (this->isEmpty()) throw runtime_error("Heap is Empty");
        
        T min = this->heap[0];                                  // Use this-> to access the inherited heap
        swap(this->heap[0], this->heap.back());
        this->heap.pop_back();
        
        sink(0);
        return min;
    }
    
protected:
    void swim(int index){
        while (index > 0) {
            int parent = (index - 1) / 2;
            
            if (this->heap[index] >= this->heap[parent]) break; // Use this-> to access the inherited heap
            swap(this->heap[index], this->heap[parent]);        // swap if parent is larger than value
            index = parent;
        }
    }
    
    void sink(int index){
        int n = this->heap.size();                              // Use this-> to access the inherited heap
        while (2 * index + 1 < n) {
            int child = 2 * index + 1;
            
            if (child + 1 < n && this->heap[child + 1] < this->heap[child]) {
                child++;                                        // Find the smaller child to compare with parent
            }
            
            if (this->heap[index] <= this->heap[child]) break;  // Use this-> to access the inherited heap
            swap(this->heap[index], this->heap[child]);
            
            index = child;
        }
    }
};

template<typename T>
// Descending Sort
void min_heap_sort(vector<T>& arr){
    MinHeap<T> minheap;
    minheap.buildHeap(arr);
    
    for (int i = arr.size() - 1; i >= 0; --i) {
        arr[i] = minheap.extractMin();                          // Extract min and place it at the end
    }
}

template<typename T>
// Ascending Sort 
void heap_sort(vector<T>& arr) {
    MaxHeap<T> maxHeap;
    maxHeap.buildHeap(arr);                                     // Build max heap from the array

    for (int i = arr.size() - 1; i >= 0; --i) {
        arr[i] = maxHeap.extractMax();                          // Extract max and place it at the end
    }
}

int main(){
    // Test MaxHeap
    MaxHeap<int> maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);
    maxHeap.insert(15);

    cout << "MaxHeap Elements (Extracted in order): ";
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extractMax() << " "; // Should print max values in descending order
    }
    cout << endl;

    // Test MinHeap
    MinHeap<int> minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(30);
    minHeap.insert(15);

    cout << "MinHeap Elements (Extracted in order): ";
    while (!minHeap.isEmpty()) {
        cout << minHeap.extractMin() << " "; // Should print min values in ascending order
    }
    cout << endl;
    
    vector<int> arr = {10, 20, 5, 30, 15};

    cout << "\nOriginal Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    min_heap_sort(arr);  // Sort the array using heap sort

    cout << "Sorted Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    //vector<int> arr1 = {10, 20, 5, 30, 15};

    cout << "\nOriginal Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    heap_sort(arr);  // Sort the array using heap sort

    cout << "Sorted Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}