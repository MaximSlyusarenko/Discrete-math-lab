#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> g[400000], points, c[400000], num, a[3];
int n, m, v1, v2, timer = 1, k = 1;
bool used[400000], point[400000], was[400000];
int enter[400000], up[400000], component[400000], color[400000];

void dfs(int v, int parent)
{
	used[v] = true;
	color[v] = 1;
	enter[v] = timer;
	timer++;
	up[v] = enter[v];
	int child = 0;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (g[v][i] == parent)
		{
			continue;
		}
		if (used[g[v][i]])
		{
			up[v] = min(up[v], enter[g[v][i]]);
			if (!was[c[v][i]] && color[v] == 1)
			{
				a[0].push_back(v);
				a[1].push_back(g[v][i]);
				num.push_back(c[v][i]);
				was[c[v][i]] = true;
			}
		}
		else
		{
			if (!was[c[v][i]])
			{
				a[0].push_back(v);
				a[1].push_back(g[v][i]);
				num.push_back(c[v][i]);
				was[c[v][i]] = true;
			}
			dfs(g[v][i], v);
			up[v] = min(up[v], up[g[v][i]]);
			if (up[g[v][i]] >= enter[v])
			{
				while (a[0].back() != v || a[1].back() != g[v][i])
				{
					component[num.back()] = k;
					a[0].pop_back();         	
					a[1].pop_back();
					num.pop_back();
				}	 
				a[0].pop_back();
				a[1].pop_back();                                                          
				component[num.back()] = k;
				num.pop_back();
				k++;
			}
		}
	}
	color[v] = 2;
}

int main()
{
	freopen ("biconv.in", "r", stdin);
	freopen ("biconv.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		c[v1].push_back(i + 1);
		c[v2].push_back(i + 1);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		point[i] = false;
		up[i] = 1000000000;
		color[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs(i, -1);
		}
	}
	cout << k - 1 << endl;
	for (int i = 1; i <= m; i++)
	{
		cout << component[i] << " ";
	}
	return 0;         
}