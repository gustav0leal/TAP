#include<bits/stdc++.h>
using namespace std;
const int N = 100100;
const int M = 1'000'010;
const int A = 26;

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
void add(string s)
{
    int at = 0;
    for (char ch:s)
    {
        ch -= 'a';
        if(trie[at].edge[ch] == -1)
            trie[at].edge[ch] = ++last;
        at = trie[at].edge[ch];
    }
    trie[at].end++;
}

int check_pref(string s)
{
    int at = 0;
    for (char ch:s)
    {
        ch -= 'a';
        if(trie[at].end)
            return true;
        if(trie[at].edge[ch] == -1)
            return false;   
        at = trie[at].edge[ch];
    }
    return trie[at].end > 1;
}

string s[N];
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> s[i];
        add(s[i]);
    }
    for(int i = 0; i < n; i++)
        if(check_pref(s[i]  ))
            cout << "ACHEI\n";
}