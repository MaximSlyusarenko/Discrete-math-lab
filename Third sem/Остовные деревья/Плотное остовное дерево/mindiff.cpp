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
 
int n, m;
pair <int, pair <int, int> > g[20000];
vector <int> gr[20000];
bool used[20000];
 
void dfs(int v)
{
    used[v] = true;
    for (int i = 0; i < gr[v].size(); i++)
    {
        if (!used[gr[v][i]])
        {
            dfs(gr[v][i]);
        }
    }
}
 
bool coherence()
{
    bool flag = true;
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            flag = false;
        }
    }
    return flag;
}
 
int main()
{
    freopen("mindiff.in", "r", stdin);
    freopen ("mindiff.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> g[i].second.first >> g[i].second.second >> g[i].first;
    }
    sort(g, g + m);
    int i = 0;
    int j = n - 2;
    int ans = 2000000000;
    while (j < m)
    {
        for (int k = i; k <= j; k++)
        {
            gr[g[k].second.first].push_back(g[k].second.second);
            gr[g[k].second.second].push_back(g[k].second.first);
        }
        for (int k = 1; k <= n; k++)
        {
            used[k] = false;
        }
        if (coherence())
        {
            if (g[j].first - g[i].first < ans)
            {
                ans = g[j].first - g[i].first;
            }
            i++;
        }
        else
        {
            j++;
        }
        for (int i = 1; i <= n; i++)
        {
            gr[i].clear();
        }
    }
    if (ans == 2000000000)
    {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl << ans;
    return 0;
}