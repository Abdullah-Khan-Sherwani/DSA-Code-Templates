#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void selectionSort(std::vector<T>& arr){
    size_t size = arr.size();
    for(int i = 0; i < size; i++){
        int min = i;
        
        for(int j = i + 1; j < size; j++){
            if(arr[j] < arr[i]){
                min = j;
            }
        }
        
        swap(arr[i], arr[min]);
    }
}

int main(){
    vector<int> vec = {9,8,7,6,5,4,3,2,1};   
    selectionSort(vec);
    
    for(auto& elem : vec){
        cout << elem << "   ";
    }
}