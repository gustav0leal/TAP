#include<bits/stdc++.h>
using namespace std;
const int N = 200100;

int low[N], dep[N], vis[N], t = 0;
vector<int> adj[N];
vector<int> at_p;
void dfs(int v, int p)
{
    vis[v] = 1;
    dep[v] = t++;
    low[v] = dep[v];
    bool is_art = false;
    int cnt = 0;
    for(int u:adj[v])
    {
        if(u == p)
            continue;
        if(!vis[u])
        {
            cnt++;
            dfs(u, v);
            // é ponto de articulação porque u alcança no maximo v
            if(low[u] >= dep[v])
            {
                is_art = true;
            }
            low[v] = min(low[v], low[u]);
        }else
        {
            low[v] = min(low[v], dep[u]);
        }
    }
    if(v == p)
    {
        if(cnt > 1)
            is_art = true;
        else
            is_art = false;
    }
    if(is_art)
        at_p.push_back(v);

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
    cout << at_p.size() << '\n';
    for(int v: at_p)
        cout << v << ' ';
    cout << '\n';
}