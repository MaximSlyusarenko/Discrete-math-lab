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
bool flag = false;

void dfs(int v, int c)
{
	if (flag)
	{
		return;
	}
	if (c == n)
	{
		flag = true;
		return;
	}
	for (int i = 0; i < g[v].size(); i++)
	{
		dfs(g[v][i], c + 1);
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
		dfs(i, 1);
		if (flag)
		{
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
	return 0;
}                                                                   