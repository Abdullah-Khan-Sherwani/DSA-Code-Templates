#include <iostream>
#include <sstream>
#include <fstream>
#include "DFS.hpp"

void testDepthFirstSearch(Graph& G, int source) {
    try {
        // Perform DFS starting from the source vertex
        DepthFirstSearch dfs(G, source);

        // Print the vertices connected to the source
        std::cout << "Vertices connected to vertex " << source << ":\n";
        for (int v = 0; v < G.V(); v++) {
            if (dfs.isMarked(v)) {
                std::cout << v << " ";
            }
        }
        std::cout << "\n";

        // Print the count of connected vertices
        std::cout << "Number of vertices connected to " << source << ": " << dfs.getCount() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    // Sample graph input
    std::string graphData = R"(
        6 8
        0 1
        0 2
        0 5
        1 2
        2 3
        2 4
        3 4
        3 5
    )";

    // Create a graph from the sample data
    std::istringstream input(graphData);
    Graph G(input);

    // Display the graph
    std::cout << "Graph representation:\n";
    std::cout << G.to_string() << "\n";

    // Test DepthFirstSearch with vertex 0 as the source
    std::cout << "Testing DepthFirstSearch starting from vertex 0...\n";
    testDepthFirstSearch(G, 0);

    // Test with another source vertex
    std::cout << "\nTesting DepthFirstSearch starting from vertex 3...\n";
    testDepthFirstSearch(G, 3);

    return 0;
}
