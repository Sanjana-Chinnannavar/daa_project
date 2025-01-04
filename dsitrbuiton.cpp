#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <algorithm>

struct Edge {
    int destination;
    double distance; // Distance in kilometers
};

struct Hospital {
    std::string name;
    int id;
};

class Graph {
public:
    Graph(int n) : adjList(n) {}

    void addEdge(int u, int v, double dist) {
        adjList[u].push_back({v, dist});
        adjList[v].push_back({u, dist}); // Bidirectional road
    }

    // Dijkstra's Algorithm
    std::vector<double> dijkstra(int start) {
        std::vector<double> distances(adjList.size(), INT_MAX);
        distances[start] = 0;
        std::vector<bool> visited(adjList.size(), false);

        for (size_t i = 0; i < adjList.size(); ++i) {
            int u = -1;
            double minDist = INT_MAX;
            for (size_t j = 0; j < adjList.size(); ++j) {
                if (!visited[j] && distances[j] < minDist) {
                    minDist = distances[j];
                    u = j;
                }
            }

            if (u == -1) break; // No more nodes to visit

            visited[u] = true;

            for (const auto& edge : adjList[u]) {
                int v = edge.destination;
                double dist_v = edge.distance;
                if (distances[u] + dist_v < distances[v]) {
                    distances[v] = distances[u] + dist_v;
                }
            }
        }

        return distances;
    }

private:
    std::vector<std::vector<Edge>> adjList;
};

int main() {
    // Assume 5 hospitals, warehouse is hospital 0
    std::vector<Hospital> hospitals = {
        {"Warehouse", 0},
        {"Hospital A", 1},
        {"Hospital B", 2},
        {"Hospital C", 3},
        {"Hospital D", 4}
    };

    // Create the graph with 5 hospitals
    Graph graph(5);

    // Assume roads between hospitals with some distances
    graph.addEdge(0, 1, 10); // Warehouse to Hospital A
    graph.addEdge(0, 2, 15); // Warehouse to Hospital B
    graph.addEdge(1, 2, 5);  // Hospital A to Hospital B
    graph.addEdge(1, 3, 20); // Hospital A to Hospital C
    graph.addEdge(2, 3, 10); // Hospital B to Hospital C
    graph.addEdge(2, 4, 25); // Hospital B to Hospital D
    graph.addEdge(3, 4, 30); // Hospital C to Hospital D

    // Display hospital names and IDs
    std::cout << "Hospitals List (ID - Name):\n";
    for (const auto& hospital : hospitals) {
        std::cout << hospital.id + 1 << " - " << hospital.name << "\n"; // Display 1-based index
    }

    // Ask for supply requests
    int requestCount;
    std::cout << "\nEnter number of hospitals with supply requests: ";
    std::cin >> requestCount;

    std::vector<int> requestedHospitals;
    std::cout << "Enter the hospital numbers (1-based index) with supply requests:\n";
    for (int i = 0; i < requestCount; ++i) {
        int hospitalNumber;
        std::cin >> hospitalNumber;
        requestedHospitals.push_back(hospitalNumber - 1); // Adjust for 0-based index
    }

    // Assuming the warehouse is at hospital 0 (first hospital)
    int warehouse = 0;

    // Find the shortest path to each hospital
    std::vector<double> shortestPaths = graph.dijkstra(warehouse);

    std::cout << "\nShortest paths from warehouse (" << hospitals[warehouse].name << "):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Distance to " << hospitals[i].name << ": " << shortestPaths[i] << " km\n";
    }

    // Find the optimal route covering the requested hospitals (shortest path from warehouse to each requested hospital)
    std::vector<std::pair<std::string, double>> optimalRoute;

    for (int hospitalId : requestedHospitals) {
        optimalRoute.push_back({hospitals[hospitalId].name, shortestPaths[hospitalId]});
    }

    // Sort hospitals by distance to warehouse
    std::sort(optimalRoute.begin(), optimalRoute.end(), [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
        return a.second < b.second;
    });

    std::cout << "\nOptimal route covering requested hospitals:\n";
    double totalDistance = 0;
    for (const auto& entry : optimalRoute) {
        std::cout << "Hospital: " << entry.first << " | Distance: " << entry.second << " km\n";
        totalDistance += entry.second;
    }

    std::cout << "\nTotal distance for optimal route: " << totalDistance << " km\n";

    return 0;
}
