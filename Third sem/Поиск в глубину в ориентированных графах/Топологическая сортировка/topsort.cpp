#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> a;
vector <int> g[200000];
int n, m, v1, v2;
bool used[200000];
int c[200000];
bool flag = false;

void dfs(int v)
{
	used[v] = true;
	c[v] = 1;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
		}
		else
		{
			if (c[g[v][i]] == 1)
			{
				flag = true;
			}
		}
	}
	c[v] = 2;
	a.push_back(v);
}

int main()
{
	freopen ("topsort.in", "r", stdin);
	freopen ("topsort.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		c[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs(i);
			if (flag)
			{
				cout << -1;
				return 0;
			}
		}
	}
	reverse(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}