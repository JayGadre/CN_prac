#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minDistance(const vector<int>& dist, const vector<bool>& vis) {
    int minD = INT_MAX;
    int idx = -1;
    for (int i = 0; i < dist.size(); i++) {
        if (!vis[i] && dist[i] < minD) {
            minD = dist[i];
            idx = i;
        }
    }
    return idx;
}

void printPath(vector<int>& parent, int v) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    printPath(parent, parent[v]);
    cout << " -> " << v;
}

void dijkstra(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> vis(n, false);
    vector<int> parent(n, -1);

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = minDistance(dist, vis);
        vis[u] = true;

        for (int v = 0; v < n; v++) {
            if (!vis[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Shortest distance from router " << start 
             << " to router " << i << " = " << dist[i] << endl;
        cout << "Path: ";
        printPath(parent, i);
        cout << "\n\n";
    }
}

int main() {
    int n;
    cout << "Enter number of routers: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix:\n";

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    int start;
    cout << "Enter starting router: ";
    cin >> start;

    graph = {
        {0, 2, 4, 0, 0},
        {2, 0, 1, 7, 0},
        {4, 1, 0, 3, 5},
        {0, 7, 3, 0, 1},
        {0, 0, 5, 1, 0}
    };

    dijkstra(graph, start);

    return 0;
}
