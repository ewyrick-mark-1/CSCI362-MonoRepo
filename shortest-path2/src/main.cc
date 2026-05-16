#include "../inc/map.hh"


using namespace std;

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, double cost, double gain) {
    // Add edge from u to v with cost-gain pair
    Edge e = {v, cost, gain};
    adj[u].push_back(e);
}

void Graph::dijkstra(int src, int target) {
    
    priority_queue<
        pair<double, int>,          //element type
        vector<pair<double, int>>,  //underlying container
        greater<pair<double, int>>  //comparison function
    > pq;

    // Vector for distances, initialized to Infinity
    vector<double> dist(V, numeric_limits<double>::infinity());

    // Vector to store the path tree (parent of node i)
    vector<int> parent(V, -1);

    // Initialize source
    dist[src] = 0.0;
    pq.push({0.0, src});

    cout << "\n--- Starting Dijkstra's Algorithm ---\n";

    while (!pq.empty()) {
        // Extract the vertex with minimum distance value
        int u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        // Optional optimization: Stop if we reached target
        if (u == target) break;

        // If current distance is greater than already found shortest, skip
        if (d > dist[u]) continue;

        // Iterate through all adjacent vertices of u
        for (const auto& edge : adj[u]) {
            int v = edge.destination;
            //weight = cost / gain
            double weight = edge.getWeight();

            // Relaxation
            // If path through u to v is shorter than current known path to v
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});

                cout << "  • Updated Node " << v << ": New Distance " << dist[v]
                     << " (via Node " << u << ")" << endl;
            }
        }
    }

    // Output Results
    cout << "\n--- Results ---\n";
    if (dist[target] == numeric_limits<double>::infinity()) {
        cout << "Target Node " << target << " is unreachable from Source " << src << endl;
    } else {
        cout << "Shortest Distance from Node " << src << " (a) to Node " << target << " (f): "
             << dist[target] << endl;
        
        cout << "Path: ";
        printPathRecursive(parent, target);
        cout << endl;
    }
}

void Graph::printPathRecursive(const vector<int>& parent, int j) {
    //walk back through the vector
    if (parent[j] == -1) {
        cout << j;
        return;
    }
    printPathRecursive(parent, parent[j]);
    cout << " -> " << j;
}


void loadEdgesFromFile(Graph& g, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        exit(1);
    }

    int from, to;
    double cost, gain;

    while (file >> from >> to >> cost >> gain) {
        g.addEdge(from, to, cost, gain);
    }

    file.close();
}

int main() {
    
    int totalNodes = 6;
    Graph g(totalNodes);

    cout << "Constructing Graph with " << totalNodes << " nodes..." << endl;
    cout << "Node 0 = Start (a)" << endl;
    cout << "Node 5 = End (f)" << endl;

    // Load edges from edges.txt
    loadEdgesFromFile(g, "../edges.txt");



    g.dijkstra(0, 5);

    return 0;
}