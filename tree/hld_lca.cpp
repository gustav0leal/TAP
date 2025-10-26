#include<bits/stdc++.h>
using namespace std;

const int N = 200100;
vector<int> adj[N];
int sz[N], pai[N], gordo[N], tin[N], tout[N];

void dfs_sz(int u, int p)
{
    sz[u] = 1;
    for(int v: adj[u])
    {
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

int tt = 0;
void dfs_hld(int u, int p)
{
    tin[u] = tt++;
    pai[u] = p;
    if(adj[p][0] == u)
        gordo[u] = gordo[p];
    else
        gordo[u] = u;

    if(!adj[u].empty()){
        int pesada = adj[u][0];
        for(int v: adj[u])
        {
            if(sz[pesada] <= sz[v])
                pesada = v;
        }
        adj[u].erase(find(adj[u].begin(),adj[u].end(),pesada));
        adj[u].insert(adj[u].begin(), pesada);
    }
    for(int v: adj[u])
    {
        dfs_hld(v, u);
    }
    tout[u] = tt++;
}

// u é pai de v???
int is_parent(int u, int v)
{
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v)
{
    while(!is_parent(u,v) && !is_parent(v,u))
    {
        // gordo[v], gordo[u], pai[v], pai[u]
        if(gordo[v] == v)
            v = pai[v];
        else if(!is_parent(gordo[v],u))
            v = gordo[v];

        if(gordo[u] == u)
            u = pai[u];
        else if(!is_parent(gordo[u],v))
            u = gordo[u];
    }
    if(is_parent(u, v))
        return u;
    return v;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for(int i = 2; i <= n; i++)
    {
        int u;
        cin >> u;
        adj[u].push_back(i);
    }
    dfs_sz(1, 1);
    dfs_hld(1, 1);
    while(q--)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}