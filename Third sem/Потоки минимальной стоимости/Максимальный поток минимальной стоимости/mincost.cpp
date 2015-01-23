
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
 
using namespace std;
 
int n, m, a1, a2, a3, a4, inf = 2000000000, dist[200], p[200], potentials[200], d[200], pr[200], num[200];
vector <int> g[200], cap[200], cost[200], rev[200], gr[3];
bool was[200];
set <pair <int, int> > s;
long long ans = 0;
 
void djkstra()
{
    int start = 1;
    pair <int, int> st = make_pair(0, start);
    for (int i = 1; i <= n; i++)
    {
        d[i] = inf;
        pr[i] = -1;
        num[i] = -1;
    }
    d[start] = 0;
    pr[start] = -1;
    s.clear();
    s.insert(st);
    while (!s.empty())
    {
        pair <int, int> cur = *s.begin();
        s.erase(s.begin());
        for (int i = 0; i < g[cur.second].size(); i++)
        {
            if (cap[cur.second][i] > 0 && (d[cur.second] + cost[cur.second][i] - potentials[g[cur.second][i]] + potentials[cur.second] < d[g[cur.second][i]]))
            {
                s.erase(make_pair(d[g[cur.second][i]], g[cur.second][i]));
                d[g[cur.second][i]] = d[cur.second] + cost[cur.second][i] - potentials[g[cur.second][i]] + potentials[cur.second];
                s.insert(make_pair(d[g[cur.second][i]], g[cur.second][i]));
                pr[g[cur.second][i]] = cur.second;
                num[g[cur.second][i]] = i;
            }
        }
    }
}
 
void ford_bellman()
{
    int s = 1;
    for (int i = 1; i <= n; i++)
    {
        was[i] = false;
        dist[i] = inf;
    }
    was[s] = true;
    dist[s] = 0;
    p[s] = s;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < gr[0].size(); j++)
        {
            if (was[gr[0][j]] && (dist[gr[1][j]] > dist[gr[0][j]] + gr[2][j] || !was[gr[1][j]]))
            {
                dist[gr[1][j]] = max(-inf, dist[gr[0][j]] + gr[2][j]);
                p[gr[1][j]] = gr[0][j];
                was[gr[1][j]] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        potentials[i] = dist[i];
    }
}
 
int main()
{
    freopen ("mincost.in", "r", stdin);
    freopen ("mincost.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a1 >> a2 >> a3 >> a4;
        g[a1].push_back(a2);
        rev[a2].push_back(g[a1].size() - 1);
        g[a2].push_back(a1);
        rev[a1].push_back(g[a2].size() - 1);
        cap[a1].push_back(a3);
        cap[a2].push_back(0);
        cost[a1].push_back(a4);
        cost[a2].push_back(-a4);
        gr[0].push_back(a1);
        gr[1].push_back(a2);
        gr[2].push_back(a4);
    }
    ford_bellman();
    while (true)
    {
        djkstra();
        int tmp = n;
        int mini_cap = inf;
        long long price = 0;
        if (d[n] == inf)
        {
            cout << ans << endl;
            break;
        }
        while (pr[tmp] != -1)
        {
            mini_cap = min(mini_cap, cap[pr[tmp]][num[tmp]]);
            tmp = pr[tmp];
        }
        tmp = n;
        while (pr[tmp] != -1)
        {
            price += mini_cap * 1ll * cost[pr[tmp]][num[tmp]];
            cap[pr[tmp]][num[tmp]] -= mini_cap;
            cap[g[pr[tmp]][num[tmp]]][rev[pr[tmp]][num[tmp]]] += mini_cap;
            tmp = pr[tmp];
        }
        ans += price;
        for (int i = 1; i <= n; i++)
        {
            if (dist[i] != inf)
            {
                potentials[i] += dist[i];
            }
        }
    }
    return 0;
}