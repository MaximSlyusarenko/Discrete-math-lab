#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <stdexcept>

using namespace std;

int n, start, finish, a[3000][3000], dist[5000];
set <pair <int, int> > s;

int main()
{
	freopen ("pathmgep.in", "r", stdin);
	freopen ("pathmgep.out", "w", stdout);
	cin >> n >> start >> finish;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		dist[i] = 1000000000;
	}
	pair <int, int> st;
	st.first = 0;
	st.second = start;
	dist[start] = 0;
	s.insert(st);
	while (!s.empty())
	{
		pair <int, int> cur = *s.begin();
		s.erase(s.begin());
		for (int i = 1; i <= n; i++)
		{
			if (a[cur.second][i] != -1)
			{
				if (a[cur.second][i] + dist[cur.second] < dist[i])
				{
					pair <int, int> b;
					b.first = dist[i];
					b.second = i;
					dist[i] = dist[cur.second] + a[cur.second][i];
					if (s.find(b) != s.end())
					{
						s.erase(b);
						b.first = dist[i];
						s.insert(b);
					}
					else
					{
						b.first = dist[i];
						s.insert(b);
					}
				}
			}
		}
	}
	if (dist[finish] == 1000000000)
	{
		cout << -1;
		return 0;
	}
	cout << dist[finish];
	return 0;
}