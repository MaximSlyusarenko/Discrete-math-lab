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
vector <int> g[200000], gr[200000];
int n, m, v1, v2, k = 0;
bool used[200000];
int num[200000];

void dfs1(int v)
{
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		if (!used[g[v][i]])
		{
			dfs1(g[v][i]);
		}
	}
	a.push_back(v);
}

void dfs2(int v)
{
	used[v] = true;
	num[v] = k;
	for (int i = 0; i < gr[v].size(); i++)
	{
		if (!used[gr[v][i]])
		{
			dfs2(gr[v][i]);
		}
	}
}

int main()
{
	freopen ("cond.in", "r", stdin);
	freopen ("cond.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
		gr[v2].push_back(v1);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			dfs1(i);
		}
	}
	reverse(a.begin(), a.end());
	for (int i = 1; i <= n; i++)	
	{
		used[i] = false;
	}
	for (int i = 1; i <= n; i++)
	{
		int v = a[i - 1];
		if (!used[v])
		{
			k++;
			dfs2(v);
		}
	}
	cout << k << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << num[i] << " ";
	}
	return 0;
}