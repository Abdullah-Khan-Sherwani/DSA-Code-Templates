#include <iostream>
#include <vector>
using namespace std;

class WeightedQuickUnion{
  private:
  int* parent;
  int* sz;
  
  int findRoot(int p){
      while(p != parent[p]){
          parent[p] = parent[parent[p]];
          p = parent[p];
      }
      
      return p;
  }
  
  public:
  
  WeightedQuickUnion(int n){
      parent = new int[n];
      sz = new int[n];
      for(int i = 0; i < n; i++){
          parent[i] = i;
          sz[i] = 1;
      }
  }
  
  ~WeightedQuickUnion(){ delete[] parent;}
  
  bool connected(int p, int q){
      return findRoot(p) == findRoot(q); 
  }
  
  void union_(int p, int q){
      int pid = findRoot(p);
      int qid = findRoot(q);
      if (pid == qid) return;
      
      if(sz[pid] < sz[qid]) {
          sz[qid] += sz[pid];
          parent[pid] = qid;
      }
      else{
          sz[pid] += sz[qid];
          parent[qid] = pid;
      }
  }
};

int main() {
    // Create QuickUnion object for 10 elements
    WeightedQuickUnion wqu(10);

    // Test union operations
    wqu.union_(1, 2);
    wqu.union_(3, 4);
    wqu.union_(1, 4);  // This should also connect 1, 2, 3, and 4

    // Test connected function
    cout << "Are 1 and 2 connected? " << (wqu.connected(1, 2) ? "Yes" : "No") << endl;
    cout << "Are 1 and 3 connected? " << (wqu.connected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (wqu.connected(1, 4) ? "Yes" : "No") << endl;
    cout << "Are 2 and 4 connected? " << (wqu.connected(2, 4) ? "Yes" : "No") << endl;
    cout << "Are 5 and 6 connected? " << (wqu.connected(5, 6) ? "Yes" : "No") << endl;

    return 0;
}