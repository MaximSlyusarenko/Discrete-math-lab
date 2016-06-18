
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
 
using namespace std;
 
int n, m, k, a, b, mt[2000], ans = 0;
vector <int> g[2000];
bool used[2000];
 
bool dfs(int v)
{
    if (used[v])
    {
        return false;
    }
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
    {
        if (mt[g[v][i]] == -1 || dfs(mt[g[v][i]]))
        {
            mt[g[v][i]] = v;
            return true;
        }
    }
    return false;
}
 
int main()
{
    freopen ("paths.in", "r", stdin);
    freopen ("paths.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; i++)
    {
        mt[i] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            used[j] = false;
        }
        if (dfs(i))
        {
            ans++;
        }
    }
    cout << n - ans;
    return 0;
}