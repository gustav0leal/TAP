#include<bits/stdc++.h>
using namespace std;
#define lef(x) (x<<1) 
#define rig(x) (lef(x)|1) 
typedef long long ll;
const int N = 200'010;
ll v[N], tree[N<<2], lazy[N<<2];
const ll v_null = 0;
ll f(ll a, ll b)
{
    return a+b;
}

void push(int tree_id, int tree_l, int tree_r)
{
    if(tree_l == tree_r)
        return; 
    int tmid = (tree_l + tree_r) >> 1;

    // atualiza o lazy dos filhos
    lazy[lef(tree_id)] += lazy[tree_id];
    lazy[rig(tree_id)] += lazy[tree_id];

    // atualiza o valor dos filhos
    int size_l = tmid - tree_l + 1;
    int size_r = tree_r - (tmid+1) + 1;

    tree[lef(tree_id)] += size_l*lazy[tree_id];
    tree[rig(tree_id)] += size_r*lazy[tree_id];

    lazy[tree_id] = v_null;
}

void update_tree(
    int tree_id, int tree_l, int tree_r, 
    int upd_l, int upd_r, ll upd_v)
{
    if(upd_l > upd_r)
        return ;
    if(tree_l == upd_l && tree_r == upd_r)
    {
        int size = tree_r - tree_l + 1;
        tree[tree_id] += size*upd_v;
        lazy[tree_id] += upd_v;
        return;
    }
    push(tree_id,tree_l,tree_r);

    int tmid = (tree_l + tree_r) >> 1;
    update_tree(
        lef(tree_id), tree_l, tmid, 
        upd_l, min(tmid,upd_r),upd_v
    );
    update_tree(
        rig(tree_id), tmid+1, tree_r, 
        max(tmid+1,upd_l), upd_r,upd_v
    );
    tree[tree_id] = f(tree[lef(tree_id)],tree[rig(tree_id)]);
}

ll query_tree(int tree_id, int tree_l, int tree_r, int v_l, int v_r)
{
    if(v_l > v_r)
        return v_null;
    if(tree_l == v_l && tree_r == v_r)
        return tree[tree_id];
    push(tree_id,tree_l,tree_r);
    
    int tmid = (tree_l + tree_r) >> 1;
    return f(
        query_tree(lef(tree_id), tree_l, tmid, v_l, min(tmid,v_r)),
        query_tree(rig(tree_id), tmid+1, tree_r, max(tmid+1,v_l), v_r)
    );
}

void build(int tree_id, int tree_l, int tree_r)
{
    if(tree_l == tree_r){
        tree[tree_id] = v[tree_l];
    }else
    {
        int tmid = (tree_l + tree_r) >> 1;
        build(lef(tree_id), tree_l, tmid);
        build(rig(tree_id), tmid+1, tree_r);
        tree[tree_id] = f(tree[lef(tree_id)],tree[rig(tree_id)]);
    }
}

int main()
{
    // int n, q;
    // cin >> n >> q;
    // for(int i = 1; i <= n; i++)
    //     cin >> v[i];
    // build(1,1,n);
    // while(q--)
    // {
    //     int tipo;
    //     cin >> tipo;
    //     if(tipo == 1)
    //     {
    //         int id;
    //         ll v;
    //         cin >> id >> v;
    //         update_tree(1, 1, n, id, v);
    //     }else
    //     {
    //         int l, r;
    //         cin >> l >> r;
    //         cout << query_tree(1, 1, n, l ,r) << '\n';
    //     }
    // }

}