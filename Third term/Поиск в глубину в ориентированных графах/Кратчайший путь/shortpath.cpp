#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> g[200000], c[200000];
int n, m, v1, v2, s, t, k;
bool used[200000];
int len[200000];

void dfs(int v)
{
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
		}
		if (len[v] > len[g[v][i]] + c[v][i])
		{
			len[v] = len[g[v][i]] + c[v][i];
		}
		//len[g[v][i]] = min(len[g[v][i]], len[v] + c[v][i]);
	}
	/*for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
		}
	}*/
}

int main()
{
	freopen ("shortpath.in", "r", stdin);
	freopen ("shortpath.out", "w", stdout);
	cin >> n >> m >> s >> t;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2 >> k;
		g[v2].push_back(v1);
		c[v2].push_back(k);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		len[i] = 2000000000;
	}
	len[s] = 0;
	dfs(t);
	if (!used[s])
	{
		cout << "Unreachable";
		return 0;
	}
	cout << len[t];
	return 0;
}