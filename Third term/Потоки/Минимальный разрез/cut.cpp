#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <fstream>
#include <queue>
 
using namespace std;
 
long long n, m, a, b, c, d[1000], f[1000][1000], ans = 0, ptr[1000], cmax, ms;
vector <int> g[1000], cap[1000], vans;
bool used[1000];
 
bool bfs()
{
    queue <long long> q;
    q.push(1);
    for (int i = 1; i <= n; i++)
    {
        d[i] = -1;
    }
    d[1] = 0;
    while (!q.empty() && d[n] == -1)
    {
        long long v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++)
        {
            if (d[g[v][i]] == -1 && f[v][g[v][i]] < (ms & cap[v][i]))
            {
                d[g[v][i]] = d[v] + 1;
                q.push(g[v][i]);
            }
        }
    }
    return (d[n] != -1);
}
 
long long dfs(int v, long long flow)
{
    if (flow <= 0)
    {
        return 0;
    }
    if (v == n)
    {
        return flow;
    }
    for (int i = ptr[v]; i < g[v].size(); i++, ptr[v]++)
    {
        if (d[g[v][i]] != d[v] + 1)
        {
            continue;
        }
        long long p = dfs(g[v][i], min(flow, (ms & cap[v][i]) - f[v][g[v][i]]));
        if (p != 0)
        {
            f[v][g[v][i]] += p;
            f[g[v][i]][v] -= p;
            ptr[v]++;
            return p;
        }
    }
    return 0;
}
 
void dfs1(int v)
{
    used[v] = true;
    vans.push_back(v);
    for (int i = 0; i < g[v].size(); i++)
    {
        if (!used[g[v][i]])
        {
            if (cap[v][i] - f[v][g[v][i]] > 0)
            {
                dfs1(g[v][i]);
            }
        }
    }
}
 
int main()
{
    ifstream in ("cut.in");
    ofstream out ("cut.out");
    in >> n >> m;
    for (int i = 0; i < m; i++)
    {
        in >> a >> b >> c;
        g[a].push_back(b);
        cap[a].push_back(c);
        g[b].push_back(a);
        cap[b].push_back(c);
        cmax = max(cmax, c);
    }
    long long inf = 2000000000;
    inf *= 100000000;
    int k = (int) log2(cmax) + 1;
    for (int i = 1; i <= k; i++)
    {
        ms = (ms >> 1) | (1 << (k - 1));
        while (bfs())
        {
            for (int i = 1; i <= n; i++)
            {
                ptr[i] = 0;
            }
            long long p = dfs(1, inf);
            while (p != 0)
            {
                ans += p;
                p = dfs(1, inf);
            }
        }
    }
    dfs1(1);
    out << vans.size() << endl;
    sort(vans.begin(), vans.end());
    for (int i = 0; i < vans.size(); i++)
    {
        out << vans[i] << " ";
    }
    return 0;
}