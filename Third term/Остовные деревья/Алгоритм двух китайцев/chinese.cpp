
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdexcept>
 
using namespace std;
 
vector <int> num;
int k;
vector <bool> used;
vector <int> q;
 
void dfs(int v, vector <vector <int> > &g)
{
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
    {
        if (!used[g[v][i]])
        {
            dfs(g[v][i], g);
        }
    }
}
 
void dfs2(int v, vector <vector <int> > &edges)
{
    used[v] = true;
    for (int i = 0; i < edges[v].size(); i++)
    {
        if (!used[edges[v][i]])
        {
            dfs2(edges[v][i], edges);
        }
    }
}
 
void dfs3(int v, vector <vector <int> > &g2)
{
    used[v] = true;
    for (int i = 0; i < g2[v].size(); i++)
    {
        if (!used[g2[v][i]])
        {
            dfs3(g2[v][i], g2);
        }
    }
    q.push_back(v);
}
 
void dfs4(int v, vector <vector <int> > &gr)
{
    used[v] = true;
    num[v] = k;
    for (int i = 0; i < gr[v].size(); i++)
    {
        if (!used[gr[v][i]])
        {
            dfs4(gr[v][i], gr);
        }
    }
}
 
void condensation (vector <vector <int> > &g, vector <vector <int> > &gr, int n)
{
    for (int i = 1; i <= n; i++)
    {
        used[i] = false;
    }
    q.clear();
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            dfs3(i, g);
        }
    }
    reverse(q.begin(), q.end());
    for (int i = 1; i <= n; i++)
    {
        used[i] = false;
        num[i] = 0;
    }
    k = 0;
    for (int i = 1; i <= n; i++)
    {
        int v = q[i - 1];
        if (!used[v])
        {
            k++;
            dfs4(v, gr);
        }
    }
}
 
long long find (vector <vector <int> > &g, vector <vector <int> > &w, int n, int start)
{
    long long res = 0;
    vector <int> min_edges(n + 1, 2000000000);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            min_edges[g[i][j]] = min(min_edges[g[i][j]], w[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (i != start)
        {
            res += min_edges[i];
        }
    }
    vector <vector <int> > g1(n + 1), gr1(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            if (min_edges[g[i][j]] == w[i][j])
            {
                g1[i].push_back(g[i][j]);
                gr1[g[i][j]].push_back(i);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        used[i] = false;
    }
    dfs2(start, g1);
    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            flag = false;
        }
    }
    if (flag)
    {
        return res;
    }
    condensation(g1, gr1, n);
    vector <vector <int> > g_comp(k + 1);
    vector <vector <int> > w_comp(k + 1);
    for (int j = 1; j <= n; j++)
    {
        for (int r = 0; r < g[j].size(); r++)
        {
            if (num[j] != num[g[j][r]])
            {
                g_comp[num[j]].push_back(num[g[j][r]]);
                w_comp[num[j]].push_back(w[j][r] - min_edges[g[j][r]]);
            }
        }
    }
    res += find(g_comp, w_comp, k, num[start]);
    return res;
}
 
int main()
{
    freopen ("chinese.in", "r", stdin);
    freopen ("chinese.out", "w", stdout);
    int n, m, a, b, c;
    cin >> n >> m;
    vector <vector <int> > g(n + 1);
    vector <vector <int> > w(n + 1);
    num.resize(n + 1);
    used.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        g[a].push_back(b);
        w[a].push_back(c);
    }
    for (int i = 1; i <= n; i++)
    {
        used[i] = false;
    }
    dfs(1, g);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            flag = true;
        }
    }
    if (flag)
    {
        cout << "NO";
        return 0;
    }
    long long ans = find(g, w, n, 1);
    cout << "YES" << endl << ans;
    return 0;
}