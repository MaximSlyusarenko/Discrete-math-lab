#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

long long d[600000][20], n, m, w[20][20], h, st[20];
bool flag[20][20];

int main()
{
	freopen ("salesman.in", "r", stdin);
	freopen ("salesman.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			flag[i][j] = false;
			w[i][j] = 0;
		}
	st[0] = 1;
	for (int i = 1; i <= n + 1; i++)
		st[i] = st[i - 1] * 2;
	h = st[n + 1];
	long long inf = 3000000000;
	for (int i = 1; i <= h; i++)
		for (int j = 0; j <= n; j++)
			d[i][j] = inf;
	long long p, q;
	for (int i = 0; i < m; i++)
	{
		cin >> p >> q;
		flag[p][q] = true;
		flag[q][p] = true;
		cin >> w[q][p];
		w[p][q] = w[q][p];
	}
	for (int i = 1; i <= n; i++)
	{
		flag[i][0] = false;
		flag[0][i] = true;
		w[0][i] = 0;
	}
	d[1][0] = 0;
	for (int mask = 1; mask < h; mask++)
		for (int i = 0; i <= n; i++)
			for (int k = 1; k <= n; k++)
			{   
				int t = mask & st[i];
				int r = mask & st[k];
				if (flag[i][k] && t != 0 && r != 0)
				{
					d[mask][k] = min(d[mask][k], d[mask - st[k]][i] + w[i][k]);
					d[mask][i] = min(d[mask][i], d[mask - st[i]][k] + w[k][i]);
				}
			}					 
	long long mini = inf;
	for (int i = 1; i <= n; i++)
		if (d[h - 1][i] < mini)
			mini = d[h - 1][i];
	if (mini == inf)
	{
		cout << -1;
		return 0;
	}
	cout << mini;
	return 0;
}