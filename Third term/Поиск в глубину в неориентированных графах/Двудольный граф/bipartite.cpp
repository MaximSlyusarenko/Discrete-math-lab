#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> g[200000];
int n, m, v1, v2;
bool used[200000];
int c[200000];
bool bipartite = true;

void dfs(int v, int color, int parent)
{
	used[v] = true;
	c[v] = color;
	color++;
	color %= 2;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (g[v][i] == parent)
		{
			continue;
		}
		if (!used[g[v][i]])
		{
			dfs(g[v][i], color, v);
		}
		else
		{
			if (color != c[g[v][i]])
			{
				bipartite = false;
			}
		}
	}
}

int main()
{
	freopen ("bipartite.in", "r", stdin);
	freopen ("bipartite.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs(i, 0, -1);
		}
	}
	if (bipartite)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}
	return 0;
}