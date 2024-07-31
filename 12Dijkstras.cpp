/*Write a c++ program for below problem statement 
Tour operator organizes guided bus trips across the Maharashtra. Tourists may 
have different preferences. Tour operator offers a choice from many different 
routes. Every day the bus moves from starting city S to another city F as chosen 
by client. On this way, the tourists can see the sights alongside the route 
travelled from S to F. Client may have preference to choose route. There is a 
restriction on the routes that the tourists may choose from, the bus has to take 
a short route from S to F or a route having one distance unit longer than the 
minimal distance. Two routes from S to F are considered different if there is at 
least one road from a city A to a city B which is part of one route, but not of 
the other route.*/

#include<bits/stdc++.h>
using namespace std;

void dijkstra(vector<vector<pair<int, int>>>& graph, int start, vector<int>& distance) {
    distance[start] = 0;
    set<pair<int,int>> s;
    s.insert({0, start});
    while (!s.empty()) {
        auto it = *(s.begin());
        int u = it.second;
        int d = it.first;
        s.erase(s.begin());
        for (auto it : graph[u]) {
            int v = it.first;
            int dis = it.second;
            if (d + dis < distance[v]) {
                if (distance[v] != INT_MAX) {
                    s.erase({distance[v], v});
                }
                distance[v] = d + dis;
                s.insert({distance[v], v});
            }
        }
    }
}

int main() {
    int V, E; 
    cout << "Enter number of cities and roads: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> graph(V);
    cout << "Enter roads and distances: \n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});  
        graph[v].push_back({u, w});
    }
    int source, destination;
    cout << "Enter starting city and destination city: ";
    cin >> source >> destination;
    vector<int> distance(V, INT_MAX);
    dijkstra(graph, source, distance);
    if (distance[destination] != INT_MAX) {
        cout << "Shortest distance from city " << source << " to city " << destination << ": " << distance[destination] << endl;
    } else {
        cout << "No path found from city " << source << " to city " << destination << endl;
    }
    return 0;
}
