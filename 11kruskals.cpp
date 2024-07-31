/*You have a business with several offices; you want to lease phone lines to connect
them up with each other; and the phone company charges different amounts of money 
to connect different pairs of cities. You want a set of lines that connects all 
your offices with a minimum total cost. Solve the problem by suggesting appropriate
data structures and using kruskal's algorithm*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n){
        rank.resize(n+1, 0);
        parent.resize(n+1);
        for(int i = 0; i<=n; i++){
            parent[i] = i;
        } 
    }
    int findUpar(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUpar(parent[node]);
    }
    void unionbyrank(int u, int v){
        int ulp_u = findUpar(u);
        int ulp_v = findUpar(v);
        if(ulp_u == ulp_v) return;
        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_v] < rank[ulp_u]){
            parent[ulp_v] = ulp_u;
        }
        else{
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

vector<pair<int, pair<int, int>>> kruskal(vector<pair<int, pair<int, int>>>& edges, int V) {
    vector<pair<int, pair<int, int>>> mst;
    DisjointSet ds(V);
    sort(edges.begin(), edges.end()); // Sort edges by weight
    for(auto edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int ulp_u = ds.findUpar(u);
        int ulp_v = ds.findUpar(v);
        if(ulp_u != ulp_v) {
            mst.push_back(edge);
            ds.unionbyrank(ulp_u, ulp_v);
        }
    }
    return mst;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    vector<pair<int, pair<int, int>>> edges(E);
    cout << "Enter edges with weight: \n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {w, {u, v}};
    }
    vector<pair<int, pair<int, int>>> mst = kruskal(edges, V);
    int totalCost = 0;
    cout << "Minimum spanning tree : " << endl;
    for(auto edge : mst) {
        totalCost += edge.first;
        cout << edge.second.first << " " << edge.second.second << endl;
    }
    cout << "Minimum Cost : " << totalCost << endl;
    return 0;
}
