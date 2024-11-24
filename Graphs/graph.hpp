#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <forward_list>
#include <stdexcept>

using std::cout, std::string, std::vector, std::ifstream, std::istream, std::forward_list, std::invalid_argument;

// Adjacency List graph
class Graph {
    int m;                              // Number of edges
    vector<forward_list<int>> adj;      // adjacency list

public:
    Graph(int n) : m{0}, adj(n) {}

    Graph(istream& in) {                // read from file constructor
        int n, m;
        in >> n >> m;
        std::cerr << "n: " << n << " m: " << m << "\n";
        if (n < 0) throw new invalid_argument("number of vertices in a Graph must be non-negative");
        adj.resize(n);
        if (m < 0) throw new invalid_argument("number of edges in a Graph must be non-negative");
        this->m = 0;
        for (int i = 0; i < m; i++) {
            int v, w;
            in >> v >> w;
            std::cerr << "i: " << i << " v: " << v << " w: " << w << "\n";
            validateVertex(v);
            validateVertex(w);
            addEdge(v, w);
        }
    }

    // Return number of Vertices
    int V() { 
        return adj.size();
    }

    // Return number of edges
    int E() {
        return m;
    }

    // Establishes connection between v and w
    void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        m++;
        adj[v].push_front(w);
        adj[w].push_front(v);
    }

    // Returns vertices adjacent to v
    forward_list<int>& neighbors(int v) {
        validateVertex(v);
        return adj[v];
    }

    // Returns number of vertices connected to v 
    int degree(int v) {
        validateVertex(v);
        return std::distance(adj[v].begin(), adj[v].end());
    }

    // Returns a string representation of connected components
    string to_string() {
        string s; 
        s.append(std::to_string(V()) + " vertices, " + std::to_string(m) + " edges " + "\n");
        for (int v = 0; v < V(); v++) {
            s.append(std::to_string(v) + ": ");
            for (int w : adj[v]) {
                s.append(std::to_string(w) + " ");
            }
            s.append("\n");
        }
        return s;
    }

private:
    void validateVertex(int v) {
        if (v < 0 || v >= V())
            throw new invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string((V()-1)));
    }

};


