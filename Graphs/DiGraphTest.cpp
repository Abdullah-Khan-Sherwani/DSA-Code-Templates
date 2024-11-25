#include <iostream>
#include <sstream>
#include "DirectedGraph.hpp"

int main() {
    // Test 1: Create a DiGraph and add edges
    std::cout << "Test 1: Creating a directed graph with 5 vertices.\n";
    DiGraph graph(5);  // Create a directed graph with 5 vertices
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 2);
    
    std::cout << "Graph structure:\n";
    std::cout << graph.to_string() << "\n";

    // Test 2: Reverse the graph
    std::cout << "Test 2: Reversing the graph.\n";
    DiGraph reversed = graph.reverse();

    std::cout << "Reversed graph structure:\n";
    std::cout << reversed.to_string() << "\n";

    // Test 3: Validate neighbors and degree
    std::cout << "Test 3: Neighbors and degree validation.\n";
    for (int v = 0; v < graph.Vert(); v++) {
        std::cout << "Vertex " << v << " has degree " << graph.degree(v) << " and neighbors: ";
        for (int w : graph.neighbors(v)) {
            std::cout << w << " ";
        }
        std::cout << "\n";
    }

    // Test 4: Read graph from input
    std::cout << "Test 4: Reading a graph from an input stream.\n";
    std::istringstream input(
        "6 7\n"  // 6 vertices, 7 edges
        "0 1\n"
        "0 2\n"
        "1 3\n"
        "3 4\n"
        "4 2\n"
        "2 5\n"
        "5 0\n"
    );
    
    DiGraph inputGraph(input);
    std::cout << "Graph read from input:\n";
    std::cout << inputGraph.to_string() << "\n";

    return 0;
}
