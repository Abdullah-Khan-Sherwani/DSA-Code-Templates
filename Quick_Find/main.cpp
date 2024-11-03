#include <iostream>
#include<vector>
using namespace std;

class UF{
  private:
  vector<int> id;
  
  public:
  
  UF(int n) : id(n){
      for(int i = 0; i < n; i++){
          id[i] = i;
      }
  }
  
  int find(int p){
      return id[p];
  }
  
  void union_(int p, int q){
      int pid = id[p];
      int qid = id[q];
      for(int i = 0; i < id.size(); i++){
          if(id[i] == pid){
              id[i] = qid;
          }
      }
  }
  
  bool connected(int p, int q){
      return find(p) == find(q);
  }
};

//GPT made
int main() {
    // Create a UF object for 10 elements
    UF uf(10);

    // Test union operations
    uf.union_(1, 2);
    uf.union_(3, 4);
    uf.union_(1, 4);

    // Test connected function
    cout << "Are 1 and 2 connected? " << (uf.connected(1, 2) ? "Yes" : "No") << endl;
    cout << "Are 1 and 3 connected? " << (uf.connected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 1 and 4 connected? " << (uf.connected(1, 4) ? "Yes" : "No") << endl;
    cout << "Are 2 and 4 connected? " << (uf.connected(2, 4) ? "Yes" : "No") << endl;
    cout << "Are 5 and 6 connected? " << (uf.connected(5, 6) ? "Yes" : "No") << endl;

    return 0;
}