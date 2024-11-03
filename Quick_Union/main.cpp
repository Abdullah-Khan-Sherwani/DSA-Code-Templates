#include <iostream>
#include<vector>
using namespace std;

class QuickUnion{
  private:
  int* parent;
  
  int root(int p){
      return parent[p];
  }
  
  public:
  QuickUnion(int n){
      parent = new int[n];
      for(int i = 0; i < n; i++){
          parent[i] = i;
      }
  }
  
  ~QuickUnion(){ delete[] parent; }
  
  int find(int p){
      while(p != parent[p]){
          p = parent[p];
      }
      
      return p;
  }
  
  bool connected(int p, int q){
      return find(p) == find(q);
  }
  
  void union_(int p, int q){
      int pRoot = find(p);
      int qRoot = find(q);
      parent[pRoot] = qRoot;
  }
};

//GPT made
int main() {
    // Create QuickUnion object for 10 elements
    QuickUnion qu(10);

    // Test union operations
    qu.union_(1, 2);
    qu.union_(3, 4);
    qu.union_(1, 4);  // This should also connect 1, 2, 3, and 4

    // Test connected function
    cout << "Are 1 and 2 connected? " << (qu.connected(1, 2) ? "Yes" : "No") << endl;
    cout << "Are 1 and 3 connected? " << (qu.connected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (qu.connected(1, 4) ? "Yes" : "No") << endl;
    cout << "Are 2 and 4 connected? " << (qu.connected(2, 4) ? "Yes" : "No") << endl;
    cout << "Are 5 and 6 connected? " << (qu.connected(5, 6) ? "Yes" : "No") << endl;

    return 0;
}