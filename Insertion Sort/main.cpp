#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void insertionSort(vector<T>& arr){
    size_t size = arr.size();
    
    for(int i = 1; i < size; i++){
        int temp = arr[i];
        int j;
        
        for(j = i - 1; j >= 0 && arr[j] > temp; j--){
            //swap(arr[j], arr[j - 1]);
            arr[j + 1] = arr[j];
        }
        
        arr[j + 1] = temp;
    }
}

int main(){
    vector<int> vec = {9,8,7,6,5,4,3,2,1};   
    insertionSort(vec);
    
    for(auto& elem : vec){
        cout << elem << "   ";
    }
}