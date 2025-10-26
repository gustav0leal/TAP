#include<bits/stdc++.h>
using namespace std;


vector<int> kmp(string s)
{
    vector<int> p(s.size(), 0);
    for(int i = 1; i < s.size(); i++)
    {
        int j = i-1;
        while(p[j] != 0 && s[i] != s[p[j]])
            j = p[j] - 1; 
        if(s[i] == s[p[j]])
            p[i] = p[j] + 1;
        else
            p[i] = 0;
    }
    return p;
}


int main()
{
    string s, t;
    cin >> t >> s;
    auto p = kmp(t + "#" + s);
    int rs = 0;
    for(int i = t.size(); i < t.size() + s.size() + 1; i++)
    {
        if(p[i] == t.size())
        {
            cout << i - t.size() << '\n';
            rs++;
        }
    }
    cout << rs << '\n';
}