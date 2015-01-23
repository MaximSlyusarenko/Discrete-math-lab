
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
  
long long n, m, a, b, l, r, d[1000], f[1000][1000], ans = 0, ptr[1000], cmax, ms, s, t, c[1000], c1[1000];
vector <long long> g[1000], cap[1000], gr[4];
  
bool bfs()
{
    queue <long long> q;
    q.push(0);
    for (int i = 0; i <= n + 1; i++)
    {
        d[i] = -1;
    }
    d[0] = 0;
    while (!q.empty() && d[n + 1] == -1)
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
    return (d[n + 1] != -1);
}
  
long long dfs(int v, long long flow)
{
    if (flow <= 0)
    {
        return 0;
    }
    if (v == n + 1)
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
            return p;
        }
    }
    return 0;
}
  
int main()
{
    ifstream in ("circulation.in");
    ofstream out ("circulation.out");
    in >> n >> m;
    s = 0;
    t = n + 1;
    for (int i = 0; i < m; i++)
    {
        in >> a >> b >> l >> r;
        c[b] += l;
        c1[a] += l;
        g[a].push_back(b);
        cap[a].push_back(r - l);
        g[b].push_back(a);
        cap[b].push_back(0);
        gr[1].push_back(a);
        gr[2].push_back(b);
        gr[3].push_back(l);
        cmax = max(cmax, r - l);
    }
    for (int i = 1; i <= n; i++)
    {
        if (c[i] != 0)
        {
            g[s].push_back(i);
            cap[s].push_back(c[i]);
            g[i].push_back(s);
            cap[i].push_back(0);
            cmax = max(cmax, c[i]);
        }
        if (c1[i] != 0)
        {
            g[i].push_back(t);
            cap[i].push_back(c1[i]);
            g[t].push_back(i);
            cap[t].push_back(0);
            cmax = max(cmax, c1[i]);
        }
    }
    long long inf = 2000000000;
    inf *= 100000000;
    int k = (int) log2(cmax) + 1;
    for (int i = 1; i <= k; i++)
    {
        ms = (ms >> 1) | (1 << (k - 1));
        while (bfs())
        {
            for (int i = 0; i <= n + 1; i++)
            {
                ptr[i] = 0;
            }
            long long p = dfs(0, inf);
            while (p != 0)
            {
                ans += p;
                p = dfs(0, inf);
            }
        }
    }
    for (int i = 0; i < g[s].size(); i++)
    {
        if (f[s][g[s][i]] < cap[s][i])
        {
            out << "NO";
            return 0;
        }
    }
    out << "YES" << endl;
    for (int i = 0; i < m; i++)
    {
        out << f[gr[1][i]][gr[2][i]] + gr[3][i] << endl;
    }
    return 0;
}