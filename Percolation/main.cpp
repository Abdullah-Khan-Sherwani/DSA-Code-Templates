#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
using namespace std;

class WeightedQuickUnion{
  private:
  vector<int> parent;
  vector<int> sz;
  
  int findRoot(int p){
      while(p != parent[p]){
          parent[p] = parent[parent[p]];
          p = parent[p];
      }
      
      return p;
  }
  
  public:
  
  WeightedQuickUnion(int n) : parent(n), sz(n) {
      /*parent = new int[n];
      sz = new int[n];*/
      for(int i = 0; i < n; i++){
          parent[i] = i;
          sz[i] = 1;
      }
  }
  
  //~WeightedQuickUnion(){ delete[] parent;}
  
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

class Percolation {
    private:
    vector<vector<bool>> grid;
    WeightedQuickUnion wqu;
    int n;
    int top;
    int bottom;
    int count;
    
    int TwoDtoOneD(int row, int col){
        return row * n + col; 
    }
    
    public: //IbadGOAT
    // creates n-by-n grid, with all sites initially blocked
    Percolation(int n) : grid(n, vector<bool>(n, false)), n(n), wqu(n * n + 2), count(0), top(n * n), bottom(n * n + 1) {
        if(n < 1){
            throw std::invalid_argument("Incorrect input\n");
        }
        
        for (int col = 0; col < n; ++col) {
            wqu.union_(top, TwoDtoOneD(0, col));
            wqu.union_(bottom, TwoDtoOneD(n - 1, col));
        }
    }
    
    // opens the site (row, col) if it is not open already
    void open(int row, int col){
        if(row > n - 1 || col > n - 1 || row < 0 || col < 0){
            throw std::invalid_argument("Incorrect entries\n");
        }
        
        if(isOpen(row, col)) return;
        
        grid[row][col] = true;
        count++;
        int index = TwoDtoOneD(row, col);
        
        if(row > 0 && grid[row - 1][col] == true){
            wqu.union_(index, TwoDtoOneD(row - 1, col));
        }
        if (row < n - 1 && isOpen(row + 1, col)) {
                wqu.union_(index, TwoDtoOneD(row + 1, col));
        }
        if (col > 0 && isOpen(row, col - 1)) {
            wqu.union_(index, TwoDtoOneD(row, col - 1));
        }
        if (col < n - 1 && isOpen(row, col + 1)) {
            wqu.union_(index, TwoDtoOneD(row, col + 1));
        }
    }
    
    // is the site (row, col) open?
    bool isOpen(int row, int col){
        if(row > n - 1 || col > n - 1 || row < 0 || col < 0){
            throw std::invalid_argument("Incorrect entries\n");
        }
        return grid[row][col];
    }
    
    // is the site (row, col) full?
    bool isFull(int row, int col){
        if(row > n - 1 || col > n - 1 || row < 0 || col < 0){
            throw std::invalid_argument("Incorrect entries\n");
        }
        
        return wqu.connected(top, TwoDtoOneD(row, col));
    }
    // returns the number of open sites
    int numberOfOpenSites(){
        return count;
    }
    // does the system percolate?
    bool percolates(){
        return wqu.connected(top, bottom);
    }
    // unit testing (required)
    static void test(){
        Percolation test(5);
        
        assert(!test.percolates());
        cout << "Passed test 1 and does not percolate initially\n";
        
        test.open(0, 0);
        test.open(1, 0);
        test.open(2, 0);
        test.open(3, 0);
        test.open(4, 0);
        
        assert(test.isOpen(0, 0));
        assert(test.isOpen(4, 0));
        assert(test.isFull(0, 0));
        assert(test.isFull(4, 0));
        cout << "Test 2 passed and correctly recognizes open and full sites\n";
        
        assert(test.percolates());
        cout << "Test 3 passed as system percolates when a path between top and bottom is opneed\n";
        
        assert(test.numberOfOpenSites() == 5);
        cout << "Test 4 passed counting sites corrrectly\n";
        
        test.open(2, 2);
        assert(!test.isFull(2, 2));
        test.open(2, 1);
        test.open(0, 1);
        assert(test.isFull(2, 1));
        cout << "Test 5 passed and connections being made correctly\n";
    }
};

int main() {
   Percolation::test();

    return 0;
} 