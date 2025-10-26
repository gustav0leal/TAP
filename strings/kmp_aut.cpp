#include<bits/stdc++.h>
using namespace std;

const int N = 100'100;
const int A = 26;
int go[N][A];

void kmp(string s)
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
    for(int i = 1; i <= s.size(); i++)
    {
        go[i-1][s[i-1]-'a'] = i;
        for(int alph = 0; alph < A; alph++)
            go[i][alph] = go[p[i-1]][alph];
    }
    
    // for(int i = 0; i <= s.size(); i++)
    // {
    //     cout << i << "<<<\n";
        
    //     for(int alph = 0; alph < A; alph++)
    //         cout << (char)(alph+'a') << " -> " << go[i][alph] << '\n';
    //     cout << "<<<\n";
    // }
}
vector<vector<int>> dp;
string s, t;
int solve(int i, int j)
{
    if(i == s.size())
        return (j == t.size());
    int &ans = dp[i][j];
    if(ans != -1)
        return ans;
    ans = 0;
    if(s[i] == '?')
        for(int alph = 0; alph < A; alph++)
            ans = max(ans, solve(i+1,go[j][alph]));
    else
        ans = solve(i+1,go[j][s[i]-'a']);
    if(j == t.size())
        ans++;
    // cout << i << ' ' << j << ' ' << ans << "\n";
    return ans;
}

int main()
{
    cin >> s >> t;
    kmp(t);
    dp.resize(s.size()+10,vector<int>(t.size()+10,-1));
    cout << solve(0, 0) << '\n';
}