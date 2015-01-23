#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

int n, m, a, b, c, dist[1000][1000];

int main()
{
	freopen ("pathsg.in", "r", stdin);
	freopen ("pathsg.out", "w", stdout);
	cin >> n >> m;	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
			{
				dist[i][j] = 0;
			}
			else
			{
				dist[i][j] = 1000000000;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		dist[a][b] = c;
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (dist[i][j] == 1000000000)
			{
				cout << -1 << " ";
			}
			else
			{
				cout << dist[i][j] << " ";
			}
		}
		cout << endl;
	}
	return 0;
}