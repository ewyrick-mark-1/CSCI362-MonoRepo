
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include <list>
#include <fstream>

struct Edge {
    int destination;
    double cost;
    double gain;

    double getWeight() const {
        return cost / gain;
    }
};

class Graph {
private:
    int V; // Number of vertices (nodes)
    std::vector<std::vector<Edge>> adj;

    void printPathRecursive(const std::vector<int>& parent, int j);

public:
    Graph(int V);

    void addEdge(int u, int v, double cost, double gain);

    void dijkstra(int src, int target);
};

#endif // MAP_H