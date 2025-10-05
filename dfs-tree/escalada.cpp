#include<bits/stdc++.h>
using namespace std;
const int N = 200100;

int low[N], dep[N], vis[N], t = 0, target;
vector<int> adj[N];
vector<int> at_p;
bool dfs(int v, int p)
{
    // if(v == target)
    vis[v] = 1;
    dep[v] = t++;
    low[v] = dep[v];
    bool is_art = false, at_hit = false;
    int cnt = 0;
    if(target == v)
        at_hit = true;
    for(int u:adj[v])
    {
        if(u == p)
            continue;
        if(!vis[u])
        {
            cnt++;
            // cout << v << " --> " << u << '\n';
            bool hit_target = dfs(u, v);
            // é ponto de articulação porque u alcança no maximo v
            if(low[u] >= dep[v] && hit_target)
            {
                is_art = true;
            }
            if(hit_target)
                at_hit = true;
            low[v] = min(low[v], low[u]);
        }else
        {
            low[v] = min(low[v], dep[u]);
        }
    }
    if(v == p)
    {
        is_art = false;
        // if(cnt > 1)
        //     is_art = true;
        // else
    }
    if(is_art)
        at_p.push_back(v);
    return at_hit;
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
    int u;
    cin >> u >> target;
    // cout << u << " alcança " << target << '\n';
    dfs(u, u);
    cout << at_p.size()+2 << '\n';
    // for(int v: at_p)
    //     cout << v << ' ';
    // cout << '\n';
}