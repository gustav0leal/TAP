#include<bits/stdc++.h>
using namespace std;
const int N = 200100;

int low[N], dep[N], vis[N], t = 0;
vector<int> adj[N];
vector<pair<int, int>> bridges;
void dfs(int v, int p)
{
    vis[v] = 1;
    dep[v] = t++;
    low[v] = dep[v];
    for(int u:adj[v])
    {
        if(u == p)
            continue;
        if(!vis[u])
        {
            dfs(u, v);
            // é ponte porque u não sobe acima de v
            if(low[u] > dep[v])
            {
                bridges.emplace_back(u, v);
            }else{
                // não é ponte
                low[v] = min(low[v], low[u]);
            }
        }else
        {
            low[v] = min(low[v], dep[u]);
        }
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    cout << bridges.size() << "\n";
    for(auto [u,v]:bridges)
        cout << u << ' ' << v << '\n';
}