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
 
long long n, a, dist[5000], p[5000], inf = 1000000000;
bool was[5000];
vector <long long> g[3], ans;
set <int> x;
 
int main()
{
    freopen ("negcycle.in", "r", stdin);
    freopen ("negcycle.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a;
            if (a != 1000000000)
            {
                g[0].push_back(i);
                g[1].push_back(j);
                g[2].push_back(a);
                if (i == j && a < 0)
                {
                	cout << "YES" << endl << 2 << endl << i << " " << i;
                	return 0;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        was[i] = false;
    }
    for (int s = 1; s <= n; s++)
    {
    	for (int i = 1; i <= n; i++)
    	{	
    		dist[i] = inf;
    	}
        if (!was[s])
        {
            was[s] = true;
            dist[s] = 0;
            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < g[0].size(); j++)
                {
                    if (was[g[0][j]] && (dist[g[1][j]] > dist[g[0][j]] + g[2][j] || !was[g[1][j]]))
                    {
                        dist[g[1][j]] = dist[g[0][j]] + g[2][j];
                        was[g[1][j]] = true;
                        p[g[1][j]] = g[0][j];
                    }
                }
            }
            for (int j = 0; j < g[0].size(); j++)
            {
                if (dist[g[1][j]] > dist[g[0][j]] + g[2][j] && was[g[0][j]])
                {
                    int v = g[1][j];
                    for (int i = 0; i < n; i++)
                    {
                        v = p[v];
                    }
                    int u = v;
                    while (u != v || ans.size() == 0)
                    {
                        ans.push_back(v);
                        v = p[v];
                    }
                    ans.push_back(u);
                    reverse(ans.begin(), ans.end());
                    cout << "YES" << endl << ans.size() << endl;
                    for (int i = 0; i < ans.size(); i++)
                    {
                    	cout << ans[i] << " ";
                    }
                    return 0;
                }
            }
        }
    }
    cout << "NO";
    return 0;
}