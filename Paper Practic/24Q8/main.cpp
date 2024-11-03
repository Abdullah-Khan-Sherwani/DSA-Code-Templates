#include <iostream>
#include<vector>
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
  
  ~WeightedQuickUnion(){ delete[] parent; delete [] sz;}
  
  bool connected(int p, int q){
      return findRoot(p) == findRoot(q); 
  }
  
  int SubSz(int i){
      int root = findRoot(i);
      return sz[root];
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

class OpenSites{
  private:
  WeightedQuickUnion wuf;
  vector<bool> sites;
  
  public:
  
  OpenSites(int n) : wuf(n), sites(n) {}
  
  void open(int i){
      sites[i] = true;
      
      if(i - 1 >= 0 && sites[i - 1]){
          wuf.union_(i - 1, i);
      }
      else if(i + 1 < sites.size() && sites[i + 1]){
          wuf.union_(i, i + 1);
      }
  }
  
  int OpenLen(int i){
      return wuf.SubSz(i);
  }
};

//GPT made
int main() {
    // Create OpenSites object for 10 sites
    OpenSites os(10);

    // Open some sites and print their component sizes
    os.open(1);
    os.open(2);
    os.open(4);
    os.open(5);
    os.open(6);
    
    cout << "Size of open component at 1: " << os.OpenLen(1) << endl;
    cout << "Size of open component at 2: " << os.OpenLen(2) << endl;
    cout << "Size of open component at 4: " << os.OpenLen(4) << endl;
    cout << "Size of open component at 5: " << os.OpenLen(5) << endl;

    // Check if the components at site 1 and 2 are connected
    //cout << "Is site 1 open? " << (os.isOpen(1) ? "Yes" : "No") << endl;
    //cout << "Is site 4 open? " << (os.isOpen(4) ? "Yes" : "No") << endl;

    return 0;
}