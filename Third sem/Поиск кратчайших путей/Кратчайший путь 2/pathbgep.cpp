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

vector <long long> g[50000], w[50000];
long long n, m, dist[50000];
set <pair <long long, long long> > s;

int main()
{
	ifstream in ("pathbgep.in");
	ofstream out ("pathbgep.out");
	in >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		in >> a >> b >> c;
		g[a].push_back(b);
		w[a].push_back(c);
		g[b].push_back(a);
		w[b].push_back(c);
	}
	for (int i = 1; i <= n; i++)
	{
		dist[i] = -1;
	}
	dist[1] = 0;
	s.insert(make_pair(0, 1));
	while (!s.empty())
	{
		pair <int, int> cur = *s.begin();
		s.erase(s.begin());
		for (int i = 0; i < g[cur.second].size(); i++)
		{
			if (w[cur.second][i] + dist[cur.second] < dist[g[cur.second][i]] || dist[g[cur.second][i]] == -1)
			{
				s.erase(make_pair(dist[g[cur.second][i]], g[cur.second][i]));
				dist[g[cur.second][i]] = dist[cur.second] + w[cur.second][i];
				s.insert(make_pair(dist[g[cur.second][i]], g[cur.second][i]));
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		out << dist[i] << " ";
	}
	return 0;
}