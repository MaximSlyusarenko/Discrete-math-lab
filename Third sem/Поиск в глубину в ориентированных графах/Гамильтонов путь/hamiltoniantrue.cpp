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
int num[200000];
bool used[200000];
int n, m, v1, v2;
bool flag = false;

void dfs(int v)
{
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
		}
		num[v] = max(num[v], num[g[v][i]] + 1);
	}
}

int main()
{
	freopen ("hamiltonian.in", "r", stdin);
	freopen ("hamiltonian.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
	}
	for (int i = 1; i <= n; i++)
	{
		num[i] = 1;
		used[i] = false;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs(i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (num[i] == n)
		{
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
	return 0;
}