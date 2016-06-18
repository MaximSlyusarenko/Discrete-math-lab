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
int n, m, v1, v2, k = 0;
bool used[200000];
int num[200000];

void dfs(int v)
{
	used[v] = true;
	num[v] = k;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
		}
	}
}

int main()
{
	freopen ("components.in", "r", stdin);
	freopen ("components.out", "w", stdout);
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
			k++;
			dfs(i);
		}
	