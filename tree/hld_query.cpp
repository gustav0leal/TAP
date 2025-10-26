#include<bits/stdc++.h>
using namespace std;
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
const int N = 200100;
vector<int> adj[N];
int sz[N], pai[N], gordo[N], tin[N], tout[N], a[N], aux[N];
int n;
struct segtree{
    int tree[N<<2];
    void build(int p, int tl, int tr)
    {
        if(tl == tr)
        {
            // cout << tl << ' ' << a[tl] << '\n'; 
            tree[p] = a[tl];
        }
        else
        {
            int tmid = (tl+tr) >> 1;
            build(lef(p), tl, tmid);
            build(rig(p), tmid+1, tr);
            tree[p] = max(tree[lef(p)], tree[rig(p)]);
        }
    }

    void update(int p, int tl, int tr, int k, int x)
    {
        if(tl == tr)
            tree[p] = x;
        else
        {
            int tmid = (tl+tr) >> 1;
            if(tmid < k)
                update(rig(p), tmid+1, tr, k, x);
            else
                update(lef(p), tl, tmid, k, x);
            tree[p] = max(tree[lef(p)], tree[rig(p)]);
        } 
    }
    int query(int p, int tl, int tr, int l, int r)
    {
        if(l > r)
            return 0;
        if(tl == l && tr == r)
            return tree[p];
        int tmid = (tl + tr) >> 1;
        return max(
            query(lef(p), tl, tmid, l, min(r, tmid)),
            query(rig(p), tmid+1, tr, max(l,tmid+1), r)
        );
    }
} seg;


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

int tt = 0;
void dfs_hld(int u, int p)
{
    tin[u] = ++tt;
    pai[u] = p;
    if(adj[p][0] == u)
        gordo[u] = gordo[p];
    else
        gordo[u] = u;
    // cout << u << ' ' << tin[u] << '\n';
    if(adj[u].size() != 1){
        int pesada = -1;
        for(int v: adj[u])
        {
            if(v == p)
                continue;
            if(pesada == -1)
                pesada = v;
            if(sz[pesada] <= sz[v])
                pesada = v;
        }
        adj[u].erase(find(adj[u].begin(),adj[u].end(),pesada));
        adj[u].insert(adj[u].begin(), pesada);
    }
    for(int v: adj[u])
    {
        if(v == p)
            continue;
        dfs_hld(v, u);
    }
    tout[u] = tt;
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

// assuma que u é ancestral de v
int query(int u, int v)
{
    int mx = 0;
    while(!is_parent(gordo[v],u))
    {
        if(gordo[v] == v)
            mx = max(mx, a[tin[v]]);
        else
            mx = max(mx, seg.query(1, 1, n, tin[gordo[v]],tin[v]));
        v = pai[gordo[v]];
    }
    return max(mx, seg.query(1, 1, n, tin[u],tin[v]));
}


int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);

    int q;
    cin >> n >> q;
    
    for(int i = 1; i <= n; i++)
        cin >> aux[i];
    for(int i = 2; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sz(1, 1);
    dfs_hld(1, 1);
    
    for(int i = 1; i <= n; i++)
        a[tin[i]] = aux[i];
    seg.build(1, 1, n);
    while(q--)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int u, x;
            cin >> u >> x;
            a[tin[u]] = x;
            seg.update(1, 1, n, tin[u], x);
        }else
        {
            int u, v;
            cin >> u >> v;
            int lc = lca(u, v);
            // cout << lc << ' ' << v << ' ' << query(lc, v) << '\n';
            // cout << lc << ' ' << u << ' ' << query(lc, u) << '\n';
            cout << max(query(lc, v), query(lc, u)) << "\n";
        }
    }
}