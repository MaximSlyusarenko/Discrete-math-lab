#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n, p[600000], r[600000]; 

int main()
{
	freopen ("parking.in", "r", stdin);
	freopen ("parking.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		p[i] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		int k;
		scanf ("%d", &k);
		int j = k;
		while (p[k] != k)
		{
			k = p[k];
		}
		printf ("%d ", k);
		int q = k + 1;
		if (q > n)
			q = 1;
		while (p[q] != q)
			q = p[q];
		while (p[j] != j)
		{
			int d = j;
			j = p[j];
			p[d] = q;
		}
		p[k] = q;                               
	}
	return 0;
}