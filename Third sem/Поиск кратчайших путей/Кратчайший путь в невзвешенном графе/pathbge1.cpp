#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

vector <int> g[100000];
int n, m, a, b;
bool used[100000];
queue <int> q;
int dist[100000];

int main()
{
	freopen ("pathbge1.in", "r", stdin);
	freopen ("pathbge1.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}		
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		dist[i] = -1;
	}
	dist[1] = 0;
	used[1] = true;
	q.push(1);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < g[v].size(); i++)
		{
			if (!used[g[v][i]])
			{
				used[g[v][i]] = true;
				q.push(g[v][i]);
				dist[g[v][i]] = dist[v] + 1;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << dist[i] << " ";
	}
	return 0;
}