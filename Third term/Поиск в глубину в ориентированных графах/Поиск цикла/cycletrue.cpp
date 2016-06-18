#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> a, ans;
vector <int> g[200000];
int n, m, v1, v2, k = -1;
bool used[200000];
int c[200000], start = -1, finish = -1, p[200000];
bool flag = false, fl = false;

bool dfs(int v)
{
	used[v] = true;
	c[v] = 1;
	for (int i = 0; i < g[v].size(); i++)
	{
		int t = g[v][i];
		if (!used[t])
		{
			p[t] = v;
			if (dfs(t))
			{
				return true;
			}
		}
		else
		{
			if (c[t] == 1)
			{
				start = t;
				finish = v;
				return true;
			}
		}
	}
	c[v] = 2;
	return false;
}

int main()
{
	freopen ("cycle.in", "r", stdin);
	freopen ("cycle.out", "w", stdout);
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
	bool flag = false;
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			if (dfs(i))
			{
				cout << "YES" << endl;
				flag = true;
				break;
			}
		}
	}
	if (!flag)
	{
		cout << "NO";
		return 0;
	}
	a.push_back(start);
	while (start != finish)
	{
		a.push_back(finish);
		finish = p[finish];
	}
	reverse(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}