#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
vector<int> adj[N];
vector<bool> visited(N);
vector<int> ans, ansdfs, ansbfs;
int n, m;
void dfs(int v)
{
    visited[v] = true;
    ansdfs.push_back(v);
    for (int u : adj[v])
    {
        if(!visited[u]) dfs(u);
    }
    ans.push_back(v);
}
void topological_sort()
{
    ans.clear();
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty())
    {
        int v = q.front();
        ansbfs.push_back(v);
        q.pop();
        for (int u : adj[v])
        {
            if (!visited[u])
            {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }
    while(1)
    {
        cout<<"Enter you choice :"<<endl;
        cout<<"1. DFS :"<<endl;
        cout<<"2. BFS :"<<endl;
        cout<<"3. Topo sort :"<<endl;
        cout<<"4. EXIT"<<endl;
        int x;
        cin>>x;
        for(int i=1; i<=n; ++i) visited[i]=false;
        if(x==1)
        {   
            ansdfs.clear();
            for(int i=1; i<=n; ++i)
            {
                if(!visited[i]) dfs(i);
            }
            cout<<1<<endl;
            for(auto i:ansdfs) cout<<i<<" ";
            cout<<endl;
        }
        if(x==2)
        {   
            ansbfs.clear();
            for(int i=1; i<=n; ++i)
            {
                if(!visited[i]) bfs(i);
            }
            for(auto i:ansbfs) cout<<i<<" ";
            cout<<endl;
        }
        if(x==3)
        {
            topological_sort();
            for(auto i:ans) cout<<i<<" ";
        }
    }
}