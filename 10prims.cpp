/*You have a business with several offices; you want to lease phone lines to connect 
them up with each other; and the phone company charges different amounts of money to
 connect different pairs of cities. You want a set of lines that connects all your 
 offices with a minimum total cost. Solve the problem by suggesting appropriate 
 data structures and using prim’s algorithm*/

#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> primsalgo(vector<vector<pair<int, int>>> graph, vector<int> &visited, int startnode){
    int cost = 0;
    vector<pair<int, int>> mst;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, startnode, startnode}); 
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int charge = it[0];
        int node = it[1];
        int parent = it[2];
        if(visited[node]==1) continue;
        visited[node] = 1;
        mst.push_back({node, parent});
        cost += charge;
        for(auto it : graph[node]){
            int adjN = it.first;
            int edW = it.second;
            if(visited[adjN]!=1){
                pq.push({edW, adjN, node}); 
            }
        }
    }
    cout<<"Minimum Cost : "<<cost<<endl;
    return mst;   
}
 
int main() {
    int V, E; 
    cout << "Enter number of offices and lines: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> graph(V);
    cout << "Enter lines with charge: \n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});  
        graph[v].push_back({u, w});
    }
    vector<int> visited(V, 0);
    int startnode = 0;
    vector<pair<int, int>> mst = primsalgo(graph, visited, startnode);
    cout<<"Minimum spanning tree lines: "<<endl;
    for(auto i : mst){
        if(i.first!=i.second)
            cout<<i.first<<" "<<i.second<<endl;
    }
    return 0;
}