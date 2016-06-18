#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

long long b[200000], d[200000], n;
vector <long long> a[100001], w[100001];
bool used[100001];

void dfs(int v)
{
	used[v] = true;
	for (int i = 0; i < a[v].size(); i++)
	{
		if (!used[a[v][i]])
		{
			dfs(a[v][i]);
			b[v] += d[a[v][i]];
			d[v] = max(d[v], b[a[v][i]] - d[a[v][i]] + w[v][i]);
		}
	}
	if (d[v] == -1)
	{
		d[v] = 0;
		b[v] = 0;
		return;
	}
	d[v] += b[v];
}

int main()
{
	freopen ("matching.in", "r", stdin);
	freopen ("matching.out", "w", stdout);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		long long p, q, v;
		cin >> p >> q >> v;
		a[q].push_back(p);
		a[p].push_back(q);
		w[q].push_back(v);
		w[p].push_back(v);
	}
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		d[i] = 0;
		b[i] = 0;
	}
	dfs(1);
	cout << d[1];
	return 0;
}