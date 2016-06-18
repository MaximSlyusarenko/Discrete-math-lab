
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
 
using namespace std;
 
int n, m, a, b, c[1000][1000], s, t, f[1000][1000], cf[1000][1000], p[1000];
vector <int> g[1000];
bool used[1000];
 
bool dfs(int v)
{
    if (v == t)
    {
        return true;
    }
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
    {
        if (!used[g[v][i]] && cf[v][g[v][i]] > 0)
        {
            if (dfs(g[v][i]))
            {
                p[g[v][i]] = v;
                return true;
            }
        }
    }
    return false;
}
 
int main()
{
    freopen("maxflow.in", "r", stdin);
    freopen ("maxflow.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
    	int tmp;
        cin >> a >> b >> tmp;
        c[a][b] = tmp;
        cf[a][b] = c[a][b];
        g[a].push_back(b);
        g[b].push_back(a);
    }
    s = 1;
    t = n;
    p[s] = -1;
    for (int i = 1; i <= n; i++)
    {
        used[i] = false;
    }
    while (dfs(s))
    {
        int mini = 1000000000;
        int q = t;
        while (p[q] != -1)
        {
            mini = min(mini, cf[p[q]][q]);
            q = p[q];
        }
        q = t;
        while (p[q] != -1)
        {
            f[p[q]][q] += mini;
            f[q][p[q]] = -f[p[q]][q];
            cf[p[q]][q] = c[p[q]][q] - f[p[q]][q];
            cf[q][p[q]] = c[q][p[q]] - f[q][p[q]];
            q = p[q];
        }
        for (int i = 1; i <= n; i++)
        {
            used[i] = false;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += f[s][i];
    }
    cout << ans;
    return 0;
}