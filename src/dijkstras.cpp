#include "dijkstras.h"
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous.assign(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({source, 0});

    while(!minHeap.empty()){
        int u = minHeap.top().first;
        minHeap.pop();

        if(visited[u]){
            continue;
        }
        visited[u] = true;

        for(const Edge& edge: G[u]){
            int v = edge.dst;
            int weight = edge.weight;

            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int> &, const vector<int> &previous, int destination){
    vector<int> shortest_path;
    for(int cur = destination; cur != -1; cur = previous[cur]){
        shortest_path.push_back(cur);
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

void print_path(const vector<int> &v, int total){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}