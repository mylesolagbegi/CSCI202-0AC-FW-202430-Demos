#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

class graphType {
public:
    // Constructor to initialize the graph (assuming adjacency list)
    graphType(int size = 10) {
        adjList.resize(size);
    }

    // Create graph from a file (implementing basic file parsing)
    void createGraph(const std::string& filename) {
        std::ifstream file(filename);
        int v1, v2;
        while (file >> v1 >> v2) {
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1); // Assuming undirected graph
        }
    }

    // Print graph representation (adjacency list format)
    std::string printGraph() const {
        std::string result;
        for (int i = 0; i < adjList.size(); ++i) {
            result += std::to_string(i) + ": ";
            for (int j : adjList[i]) {
                result += std::to_string(j) + " ";
            }
            result += "\n";
        }
        return result;
    }

    // Depth-First Traversal (DFS)
    std::string depthFirstTraversal() const {
        std::vector<bool> visited(adjList.size(), false);
        std::string result;
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[i]) {
                dfs(i, visited, result);
            }
        }
        return result;
    }

    // Breadth-First Traversal (BFS)
    std::string breadthFirstTraversal() const {
        std::vector<bool> visited(adjList.size(), false);
        std::string result;
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[i]) {
                bfs(i, visited, result);
            }
        }
        return result;
    }

    // Connected function: Returns true if two vertices are connected
    bool connected(int vertex1, int vertex2) {
        // Edge case: if the same vertex is being checked
        if (vertex1 == vertex2) {
            return true;
        }

        std::vector<bool> visited(adjList.size(), false);
        std::stack<int> s;

        // Start DFS from vertex1
        visited[vertex1] = true;
        s.push(vertex1);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            // If we reached vertex2, they are connected
            if (current == vertex2) {
                return true;
            }

            // Explore all neighbors of the current vertex
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }

        // If no path was found
        return false;
    }

private:
    std::vector<std::vector<int>> adjList; // Adjacency list for graph representation

    // DFS helper function
    void dfs(int vertex, std::vector<bool>& visited, std::string& result) const {
        visited[vertex] = true;
        result += std::to_string(vertex) + " ";

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, result);
            }
        }
    }

    // BFS helper function
    void bfs(int vertex, std::vector<bool>& visited, std::string& result) const {
        std::vector<int> queue;
        visited[vertex] = true;
        queue.push_back(vertex);

        while (!queue.empty()) {
            int current = queue.front();
            queue.erase(queue.begin());
            result += std::to_string(current) + " ";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push_back(neighbor);
                }
            }
        }
    }
};

int main() {
    graphType g;
    g.createGraph("graph.txt");

    // Print the graph to console and save it to file
    std::cout << g.printGraph() << std::endl;
    std::ofstream fout("g.txt");
    fout << g.printGraph();

    // Depth-First Traversal and Breadth-First Traversal
    std::cout << "Depth-First Traversal: " << g.depthFirstTraversal() << std::endl;
    std::cout << "Breadth-First Traversal: " << g.breadthFirstTraversal() << std::endl;

    // Check if two vertices are connected
    int vertex1 = 0;  // Example vertex 1
    int vertex2 = 3;  // Example vertex 2

    if (g.connected(vertex1, vertex2)) {
        std::cout << "Vertices " << vertex1 << " and " << vertex2 << " are connected." << std::endl;
    } else {
        std::cout << "Vertices " << vertex1 << " and " << vertex2 << " are NOT connected." << std::endl;
    }

    // Create a new graph as a copy and print it
    graphType h(g);
    std::cout << h.printGraph() << std::endl;

    return 0;
}
