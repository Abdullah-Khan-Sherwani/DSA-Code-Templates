#include <iostream>
#include <fstream>
#include <stdexcept>
#include "graph.hpp"
#include "BreadthFirstPaths.hpp"
using namespace std;

int main() {
    try {
        // Open the input file containing the graph
        string filename = "graph.txt"; // Update with your file path
        ifstream inFile(filename);

        if (!inFile) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        // Construct the graph from the input file
        Graph G(inFile);
        cout << "Graph:\n" << G.to_string() << "\n";

        // Ask the user for the source vertex
        int source;
        cout << "Enter the source vertex: ";
        cin >> source;

        // Initialize BreadthFirstPath object
        BreadthFirstPath bfs(G, source);

        // Ask the user for a target vertex
        int target;
        cout << "Enter the target vertex: ";
        cin >> target;

        // Check if there is a path from source to target
        if (bfs.hasPathTo(target)) {
            cout << "Path from " << source << " to " << target << ":\n";
            for (int v : bfs.pathTo(target)) {
                cout << v << " ";
            }
            cout << "\n";
        } else {
            cout << "No path from " << source << " to " << target << ".\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
