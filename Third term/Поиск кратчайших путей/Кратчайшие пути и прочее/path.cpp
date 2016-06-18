#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdexcept>

using namespace std;

long long n, m, s, a, b, c, num[5000], dist[5000], p[5000], inf = 4;
bool was[5000], used[5000];
vector <long long> g[3], v, gr[5000];

void dfs(int v)
{
	used[v] = true;
	num[v] = 2;
	for (int i = 0; i < gr[v].size(); i++)
	{
		if (!used[gr[v][i]])
		{
			dfs(gr[v][i]);
		}
	}
}				

int main()
{
	freopen ("path.in", "r", stdin);
	freopen ("path.out", "w", stdout);
	cin >> n >> m >> s;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		g[0].push_back(a);
		g[1].push_back(b);
		g[2].push_back(c);
		gr[a].push_back(b);
	}
	for (int i = 1; i <= 18; i++)
	{
		inf *= 10;
	}
	for (int i = 1; i <= n; i++)
	{
		was[i] = false;
		num[i] = 0;
	}
	was[s] = true;
	dist[s] = 0;
	num[s] = 1;
	p[s] = s;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < g[0].size(); j++)
		{
			if (was[g[0][j]] && (dist[g[1][j]] > dist[g[0][j]] + g[2][j] || !was[g[1][j]]))
			{
				dist[g[1][j]] = max(-inf, dist[g[0][j]] + g[2][j]);
				p[g[1][j]] = g[0][j];
				was[g[1][j]] = true;
				num[g[1][j]] = 1;
			}
		}
	}
	for (int j = 0; j < g[0].size(); j++)
	{
		if (dist[g[1][j]] > dist[g[0][j]] + g[2][j] && was[g[0][j]])
		{
			int st = g[1][j];             
			for (int i = 0; i < n; i++)
			{                          
			    st = p[st];            
			}
			dfs(st);               
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (num[i] == 2)
		{
			cout << "-" << endl;
		}
		else if (num[i] == 1)
		{               	
			cout << dist[i] << endl;
		}
		else
		{
			cout << "*" << endl;
		}
	}
	return 0;
}