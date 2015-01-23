#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> g[200000], ans, c[200000];
int n, m, v1, v2, timer = 1;
bool used[200000];
int enter[200000], up[200000];

void dfs(int v, int parent)
{
	used[v] = true;
	enter[v] = timer;
	timer++;
	up[v] = enter[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		if (g[v][i] == parent)
		{
			continue;
		}
		if (used[g[v][i]])
		{
			up[v] = min(up[v], enter[g[v][i]]);
		}
		else
		{
			dfs(g[v][i], v);
			up[v] = min(up[v], up[g[v][i]]);
			if (up[g[v][i]] >= enter[g[v][i]])     
			{                          
				ans.push_back(c[v][i]);
			}                          
		}
	}
}

int main()
{
	freopen ("bridges.in", "r", stdin);
	freopen ("bridges.out", "w", stdout);
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
		up[i] = 1000000000;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs(i, -1);
		}
	}
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	return 0;
}