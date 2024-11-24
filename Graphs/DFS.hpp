#pragma once
#include <vector>
#include "graph.hpp"

// Basic DFS
class DepthFirstSearch{
    std::vector<bool> marked;
    int count;

    void dfs(Graph& G, int v){
        marked[v] = true;
        count++;

        for(int w : G.neighbors(v)){
            if(!marked[w])
                dfs(G, w);
        }
    }

    public:
    DepthFirstSearch(Graph& G, int s) : marked(G.V(), false), count (0) {
        dfs(G, s);
    }

    public:
    bool isMarked(int v){
        return marked[v];
    }

    int getCount(){
        return count;
    }
};