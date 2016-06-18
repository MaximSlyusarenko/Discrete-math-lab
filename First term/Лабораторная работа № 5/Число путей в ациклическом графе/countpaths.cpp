#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

long long n, m, d[300000];
vector <long long> a[200001];

long long sol(long long p)
{
	if (d[p] != -1)
		return d[p];
	d[p] = 0;
	for (int i = 0; i < a[p].size(); i++)
	{
		d[p] += sol(a[p][i]);
		d[p] %= 1000000007;
	}
	return d[p];
}

int main()
{
	freopen ("countpaths.in", "r", stdin);
	freopen ("countpaths.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		long long b, c;
		cin >> b >> c;
		a[c].push_back(b);
	}
	for (int i = 1; i <= n; i++)
		d[i] = -1;
	d[1] = 1;
	long long q = sol(n);
	cout << q;
	return 0;
}