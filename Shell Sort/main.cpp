#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void shellSort(vector<T>& arr){
    size_t size = arr.size();
    int temp, j;
    
    for(int h = 7; h > 0; h -= 2){
        for(int i = h ; i < size; i++){
            temp = arr[i];
            
            for(j = i; j >= h && arr[j - h] > temp; j -= h){
                arr[j] = arr[j - h];
            }
            
            arr[j] = temp;
        }
    }
}

int main(){
    vector<int> vec = {9,8,7,6,5,4,3,2,1};   
    shellSort(vec);
    
    for(auto& elem : vec){
        cout << elem << "   ";
    }
}