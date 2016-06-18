
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
 
using namespace std;
 
int n, k, a1, a2, a3, inf = 2000000000, dist[200], p[200], potentials[200], d[200], pr[200], num[200], mt[200], vect_ans[200];
vector <int> g[200], cap[200], cost[200], rev[200], gr[3], init_cap[200];
bool was[200], used[200], can[200][200];
set <pair <int, int> > s;
long long ans = 0;
 
void djkstra()
{
    int start = 0;
    pair <int, int> st = make_pair(0, start);
    for (int i = 0; i <= 2 * n + 1; i++)
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
    int s = 0;
    for (int i = 0; i <= 2 * n + 1; i++)
    {
        was[i] = false;
        dist[i] = inf;
    }
    was[s] = true;
    dist[s] = 0;
    p[s] = s;
    for (int i = 1; i < 2 * n + 1; i++)
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
    for (int i = 0; i <= 2 * n + 1; i++)
    {
        potentials[i] = dist[i];
    }
}
 
void min_cost_flow()
{
    ford_bellman();
    while (true)
    {
        djkstra();
        int tmp = 2 * n + 1;
        int mini_cap = inf;
        long long price = 0;
        if (d[2 * n + 1] == inf)
        {
            cout << ans << endl;
            break;
        }
        while (pr[tmp] != -1)
        {
            mini_cap = min(mini_cap, cap[pr[tmp]][num[tmp]]);
            tmp = pr[tmp];
        }
        tmp = 2 * n + 1;
        while (pr[tmp] != -1)
        {
            price += mini_cap * 1ll * cost[pr[tmp]][num[tmp]];
            cap[pr[tmp]][num[tmp]] -= mini_cap;
            cap[g[pr[tmp]][num[tmp]]][rev[pr[tmp]][num[tmp]]] += mini_cap;
            tmp = pr[tmp];
        }
        ans += price;
        for (int i = 1; i <= 2 * n + 1; i++)
        {
            if (dist[i] != inf)
            {
                potentials[i] += dist[i];
            }
        }
    }
}
 
bool dfs(int v)
{
    if (used[v])
    {
        return false;
    }
    used[v] = true;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (can[v][i] && (mt[i] == -1 || dfs(mt[i])))
        {
            mt[i] = v;
            return true;
        }
    }
    return false;
}
 
void kuhn()
{
    ans = 0;
    for (int i = 1; i <= 2 * n; i++)
    {
        mt[i] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 2 * n; j++)
        {
            used[j] = false;
        }
        if (dfs(i))
        {
            ans++;
        }
    }
}
 
int main()
{
    freopen ("multiassignment.in", "r", stdin);
    freopen ("multiassignment.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a1 = i;
            a2 = n + j;
            cin >> a3;
            g[a1].push_back(a2);
            rev[a2].push_back(g[a1].size() - 1);
            g[a2].push_back(a1);
            rev[a1].push_back(g[a2].size() - 1);
            cap[a1].push_back(1);
            init_cap[a1].push_back(1);
            cap[a2].push_back(0);
            init_cap[a2].push_back(0);
            cost[a1].push_back(a3);
            cost[a2].push_back(-a3);
            gr[0].push_back(a1);
            gr[1].push_back(a2);
            gr[2].push_back(a3);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        g[0].push_back(i);
        rev[i].push_back(g[0].size() - 1);
        g[i].push_back(0);
        rev[0].push_back(g[i].size() - 1);
        cap[0].push_back(k);
        init_cap[0].push_back(k);
        cap[i].push_back(0);
        init_cap[i].push_back(0);
        cost[0].push_back(0);
        cost[i].push_back(0);
        gr[0].push_back(0);
        gr[1].push_back(i);
        gr[2].push_back(0);
        g[n + i].push_back(2 * n + 1);
        rev[2 * n + 1].push_back(g[n + i].size() - 1);
        g[2 * n + 1].push_back(n + i);
        rev[n + i].push_back(g[2 * n + 1].size() - 1);
        cap[n + i].push_back(k);
        init_cap[n + i].push_back(k);
        cap[2 * n + 1].push_back(0);
        init_cap[2 * n + 1].push_back(0);
        cost[n + i].push_back(0);
        cost[2 * n + 1].push_back(0);
        gr[0].push_back(n + i);
        gr[1].push_back(2 * n + 1);
        gr[2].push_back(0);
    }
    min_cost_flow();
    for (int i = 1; i <= 2 * n; i++)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            if ((g[i][j] != 0) && (g[i][j] != 2 * n + 1) && (cap[i][j] < init_cap[i][j]))
            {
                can[i][g[i][j]] = true;
            }
        }
    }
    for (int i = 0; i < k; i++)
    {
        kuhn();
        for (int i = 1; i <= n; i++)
        {
            can[mt[n + i]][n + i] = false;
            vect_ans[mt[n + i]] = i;
        }
        for (int i = 1; i <= n; i++)
        {
            cout << vect_ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}