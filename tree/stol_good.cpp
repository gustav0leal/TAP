#include<bits/stdc++.h>
using namespace std;

const int N = 200100;
vector<int> adj[N], sub[N];
int c[N], sz[N], resp[N], cores[N];

void dfs_sz(int u, int p)
{
    sz[u] = 1;
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}


void dfs(int u, int p, int keep = 0)
{
    int pesada = -1;
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        if(sz[u] <= 2*sz[v])
            pesada = v;
    }
    for(int v: adj[u])
    {
        if(v == p || v == pesada)
            continue;
        dfs(v, u, 0);
    }
    if(pesada != -1)
    {
        dfs(pesada, u, 1);
        resp[u] = resp[pesada];
        swap(sub[u],sub[pesada]);
    }
    sub[u].push_back(u);
    if(cores[c[u]] == 0)
        resp[u]++;
    cores[c[u]] = 1;
    for(int v: adj[u])
    {
        if(v == p || v == pesada)
            continue;
        for(int x:sub[v])
        {
            sub[u].push_back(x);
            if(cores[c[x]] == 0)
                resp[u]++;
            cores[c[x]] = 1;
        }
    }
    if(!keep)
        for(int x:sub[u])
            cores[c[x]] = 0;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> rid;
    for(int i = 1; i <= n; i++){
        cin >> c[i];
        rid.push_back(c[i]);
    }
    sort(rid.begin(), rid.end()); 
    for(int i = 1; i <= n; i++)
        c[i] = lower_bound(rid.begin(),rid.end(),c[i])-rid.begin();

    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sz(1,1);
    dfs(1, 1);
    for(int i = 1; i <= n; i++)
        cout << resp[i] << ' ';
    cout << '\n';
}