
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <fstream>
 
using namespace std;
 
int n, mt[500], a[500][500], inf = 2000000000, ans = 0;
vector <int> g[500];
bool used[500];
vector <int> weights;
 
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
 
void kuhn()
{
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
}
 
int main()
{
    ifstream in ("minimax.in");
    ofstream out ("minimax.out");
    in >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            in >> a[i][j];
            weights.push_back(a[i][j]);
        }
    }
    sort(weights.begin(), weights.end());
    int l = -1;
    int r = weights.size();
    while (r > l + 1)
    {
        int m = (l + r) / 2;
        for (int i = 1; i <= n; i++)
        {
            g[i].clear();
            for (int j = 1; j <= n; j++)
            {
                if (a[i][j] < weights[m])
                {
                    //a[i][j] = inf;
                }
                else
                {
                    g[i].push_back(j);
                }
            }
        }
        ans = 0;
        kuhn();
        if (ans != n)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    out << weights[l] << endl;
    return 0;
}