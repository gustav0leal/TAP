#include<bits/stdc++.h>
using namespace std;
const int N = 100100;
const int M = N*31;
const int A = 2;

struct no {
    int end;
    int edge[A];
    // map<int,int> edge;
    no(): end(0) {
        // end = 0
        for(int i = 0; i < A; i++)
            edge[i] = -1;
    }
} trie[M];
int last = 0;
void add(int x)
{
    int at = 0;
    for(int i = 31; i >= 0; i--)
    {
        int ch = 0;
        if(x & (1<<i))
            ch = 1;
        if(trie[at].edge[ch] == -1)
            trie[at].edge[ch] = ++last;
        at = trie[at].edge[ch];
    }
    trie[at].end++;
}

int max_xor(int x)
{
    int at = 0, rs = 0;
    for(int i = 31; i >= 0; i--)
    {
        int ch = 1;
        if(x & (1<<i))
            ch = 0;
        if(trie[at].edge[ch] == -1)
            ch^=1;
        else
            rs += (1<<i);
        at = trie[at].edge[ch];
    }
    return rs;
}

int a[N];
int main()
{
    int n, rs = 0;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(i != 0)
            rs = max(rs, max_xor(a[i]));
        add(a[i]);
    }
    cout << rs << '\n';
}