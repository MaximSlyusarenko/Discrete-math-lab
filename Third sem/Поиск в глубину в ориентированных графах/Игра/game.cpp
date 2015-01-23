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
int n, m, v1, v2, s, p = 2;
bool used[200000];
bool flag = false;

void dfs(int v, int l)
{
	bool fl = true;
	for (int i = 0; i < g[v].size(); i++)
	{
		p = l;
		p++;
		if (p == 3)
		{
			p -= 2;
		}
		fl = false;
		dfs(g[v][i], p);
	}
	if (p == 1 && fl)
	{
		flag = true;
	}
}

int main()
{
	freopen ("game.in", "r", stdin);
	freopen ("game.out", "w", stdout);
	cin >> n >> m >> s;
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		g[v1].push_back(v2);
	}
	dfs(s, 2);
	if (flag)
	{
		cout << "First player wins";
		return 0;
	}
	cout << "Second player wins";
	return 0;
}