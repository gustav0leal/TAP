#include<bits/stdc++.h>
using namespace std;

const int N = 200100;

vector<int> adj[N], comp[N], pil;
int vis[N], rot[N], peso[N];
void dfs(int v, int p)
{
    pil.push_back(v);
    vis[v] = 1;
    rot[v] = v;
    for(int u: adj[v])
    {
        if(u == p)
            continue;
        if(vis[u])
        {
            // v-> x -> x1 -> .... -> u -> v
            while(pil.back() != u)
            {
                rot[pil.back()] = u;
                pil.pop_back();
            }
            peso[u] = 1;
        }else
        {
            dfs(u, v);
        }
    }


    if(v == pil.back())
        pil.pop_back();
}

vector<pair<int,int>> edges;


int main()
{
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.emplace_back(u, v);
    }
    dfs(1,1);
    for(auto [u,v]:edges)
    {
        if(rot[u] == rot[v])
            continue;
        comp[rot[u]].push_back(rot[v]);
        comp[rot[v]].push_back(rot[u]);
    }
}