#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, wt;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int wt = edges[j].wt;
            if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Check for negative cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int wt = edges[j].wt;
        if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
            cout << "Graph contains negative weight cycle.\n";
            return;
        }
    }

    // Print distances
    for (int i = 0; i < V; i++) {
        if (dist[i] == 1e9)
            cout << "INF ";
        else
            cout << dist[i] << " "; 
    }
    cout << endl;
}

int main() {
    int V, E, src;
    cin >> V >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].wt;
    }

    cin >> src;

    bellmanFord(V, E, edges, src);

    return 0;
}
