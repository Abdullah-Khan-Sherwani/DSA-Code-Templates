#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.hpp"
#include "DepthFirstPaths.hpp"

using namespace std;

// AI generated 

/*void testGraph() {
    // Create a graph with 5 vertices
    Graph g(5);
    cout << "Initial graph (5 vertices):" << endl;
    cout << g.to_string() << endl;

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    cout << "Graph after adding edges:" << endl;
    cout << g.to_string() << endl;

    // Test the number of vertices and edges
    cout << "Number of vertices: " << g.V() << endl;
    cout << "Number of edges: " << g.E() << endl;

    // Test degree of vertices
    for (int v = 0; v < g.V(); ++v) {
        cout << "Degree of vertex " << v << ": " << g.degree(v) << endl;
    }
}*/

void testDepthFirstPaths(Graph& g, int source) {
    cout << "Testing DepthFirstPaths from source vertex " << source << ":" << endl;
    
    DepthFirstPath dfp(g, source);
    
    // Check paths to all vertices
    for (int v = 0; v < g.V(); ++v) {
        if (dfp.hasPathTo(v)) {
            cout << "Path from " << source << " to " << v << ": ";
            forward_list<int> path = dfp.pathTo(v);
            for (int x : path) {
                cout << x << " ";
            }
            cout << endl;
        } else {
            cout << "No path from " << source << " to " << v << endl;
        }
    }
}

int main() {
    // Create another graph for DepthFirstPaths testing
    Graph g2(6);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4);
    g2.addEdge(2, 5);
    
    cout << "\nGraph for DepthFirstPaths testing:" << endl;
    cout << g2.to_string() << endl;

    // Test DepthFirstPaths
    testDepthFirstPaths(g2, 0);

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
        DepthFirstPath dfs(G, source);

        // Ask the user for a target vertex
        int target;
        cout << "Enter the target vertex: ";
        cin >> target;

        // Check if there is a path from source to target
        if (dfs.hasPathTo(target)) {
            cout << "Path from " << source << " to " << target << ":\n";
            for (int v : dfs.pathTo(target)) {
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