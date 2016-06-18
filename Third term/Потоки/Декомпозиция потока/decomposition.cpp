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
  
long long n, m, a, b, c, d[1000], ans = 0, ptr[1000], cmax, ms;
vector <long long> f[1000];
vector <int> g[1000], cap[1000], num[1000], rev[1000];
vector <pair <long long, vector <int> > > vans;
  
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
            if (d[g[v][i]] == -1 && f[v][i] < (ms & cap[v][i]))
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
        long long p = dfs(g[v][i], min(flow, (ms & cap[v][i]) - f[v][i]));
        if (p != 0)
        {
            f[v][i] += p;
            f[g[v][i]][rev[v][i]] -= p;
            return p;
        }
    }
    return 0;
}
 
pair <long long, vector <int> > simple_decomposition(int s)
{
    vector <int> q;
    vector <int> vv;
    vector <int> vind;
    bool flag[1000];
    for (int i = 1; i <= n; i++)
    {
        flag[i] = false;
    }
    int v = s;
    while (v != n)
    {
        int cur = -1;
        int number = -1;
        int d = -1;
        for (int i = 0; i < g[v].size(); i++)
        {
            if (f[v][i] > 0)
            {
                cur = g[v][i];
                number = num[v][i];
                d = i;
                break;
            }
        }
        if (cur == -1)
        {
            if (v == n)
            {
                break;
            }
            else
            {
                vector <int> tmp;
                return make_pair(-1, tmp);
            }
        }
        q.push_back(number);
        vv.push_back(v);
        vind.push_back(d);
        flag[v] = true;
        v = cur;
    }
    long long mini = 2000000000;
    for (int i = 0; i < q.size(); i++)
    {
        mini = min(mini, f[vv[i]][vind[i]]);
    }
    for (int i = 0; i < q.size(); i++)
    {
        f[vv[i]][vind[i]] -= mini;
    }
    return make_pair(mini, q);
}
 
int main()
{
    ifstream in ("decomposition.in");
    ofstream out ("decomposition.out");
    in >> n >> m;
    for (int i = 0; i < m; i++)
    {
        in >> a >> b >> c;
        g[a].push_back(b);
        cap[a].push_back(c);
        g[b].push_back(a);
        cap[b].push_back(0);
        rev[a].push_back(f[b].size());
        rev[b].push_back(f[a].size());
        f[a].push_back(0);
        f[b].push_back(0);
        num[a].push_back(i + 1);
        num[b].push_back(i + 1);
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
    pair <long long, vector <int> > p = simple_decomposition(1);
    while (p.first != -1)
    {
        vans.push_back(p);
        p = simple_decomposition(1);
    }
    out << vans.size() << endl;
    for (int i = 0; i < vans.size(); i++)
    {
        out << vans[i].first << " " << vans[i].second.size() << " ";
        for (int j = 0; j < vans[i].second.size(); j++)
        {
            out << vans[i].second[j] << " ";
        }
        out << endl;
    }
    return 0;
}