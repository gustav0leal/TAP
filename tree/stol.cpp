#include<bits/stdc++.h>
using namespace std;

const int N = 200100;
vector<int> adj[N];
int c[N], sz[N], resp[N];
set<int> cores[N];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    int pesada = -1;
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        if(sz[u] <= 2*sz[v])
            pesada = v;
    }
    if(pesada != -1){
        swap(cores[u],cores[pesada]);
    }
    cores[u].insert(c[u]);
    
    for(int v: adj[u])
    {
        if(v == p || v == pesada)
            continue;
        for(int x:cores[v])
            cores[u].insert(x);
    }
    resp[u] = cores[u].size();
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    for(int i = 1; i <= n; i++)
        cout << resp[i] << ' ';
    cout << '\n';
}