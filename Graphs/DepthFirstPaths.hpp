#pragma once

#include "graph.hpp"
#include <vector>
#include <forward_list> 
#include <exception>

class DepthFirstPath{
    vector<bool> marked;
    vector<int> edgeTo;
    int s;

    void dfs(Graph& G, int v){
        marked[v] = true;
        for(int w : G.neighbors(v)){
            if(!marked[w]){
                edgeTo[w] = v;
                dfs(G, w);
            }
        }
    }

    public:
    DepthFirstPath(Graph& G, int s) : marked(G.V(), false), edgeTo(G.V()), s(s){
        dfs(G, s);
    }

    bool hasPathTo(int v){
        return marked[v];
    }

    forward_list<int> pathTo(int v){
        forward_list<int> path;

        if(!hasPathTo(v))
            return path;

        for(int x = v; x != s; x = edgeTo[x])
            path.push_front(x);
        
        path.push_front(s);
        return path;
    }
};