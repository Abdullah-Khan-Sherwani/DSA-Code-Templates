#include <iostream>
#include <sstream>
#include "graph.hpp"  

// Made with AI
int main() {
    // Create a graph with 5 vertices
    Graph g(5);
    
    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    
    // Print number of vertices and edges
    std::cout << "Number of vertices: " << g.V() << std::endl;
    std::cout << "Number of edges: " << g.E() << std::endl;

    // Print the graph's adjacency list
    std::cout << "Graph adjacency list:\n" << g.to_string();

    // Test neighbors and degree functions
    for (int v = 0; v < g.V(); ++v) {
        std::cout << "Neighbors of vertex " << v << ": ";
        for (int neighbor : g.neighbors(v)) {
            std::cout << neighbor << " ";
        }
        std::cout << "\nDegree of vertex " << v << ": " << g.degree(v) << "\n";
    }

    // Test invalid vertex exception
    try {
        g.addEdge(5, 0); // This should throw an exception
    } catch (std::invalid_argument& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}