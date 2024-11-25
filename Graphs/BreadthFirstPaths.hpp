#pragma once

#include "graph.hpp"
#include <vector>
#include <queue>
#include <forward_list>

class BreadthFirstPath{
    vector<bool> marked;
    vector<int> edgeTo, distTo;
    int s;

    void bfs(Graph& G, int s){
        std::queue<int> q;
        q.push(s);
        marked[s] = true;
        distTo[s] = 0;

        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(int w : G.neighbors(v)){
                if(!marked[w]){
                    q.push(w);
                    marked[w] = true;
                    edgeTo[w] = v;
                    distTo[w] = distTo[v]++;
                }
            }
        }
    }

    public:
    BreadthFirstPath(Graph& G, int s) : edgeTo(G.V()), distTo(G.V()), marked(G.V(), false), s(s) {
        bfs(G, s);
    }

    bool hasPathTo(int v){
        return marked[v];
    }

    forward_list<int> pathTo(int v){
        forward_list<int> path;

        if(!hasPathTo(v))
            return path;

        for(int x = v; x != s; x = edgeTo[x]){
            path.push_front(x);
        }

        path.push_front(s);
        return path;
    }
};