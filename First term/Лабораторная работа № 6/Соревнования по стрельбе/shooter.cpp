#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

int n, m, k;
double a[20000];

int main()
{
	freopen ("shooter.in", "r", stdin);
	freopen ("shooter.out", "w", stdout);
	cin >> n >> m >> k;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i] = 1 - a[i];
		double t = a[i];
		for (int j = 0; j < m - 1; j++)
			a[i] *= t;
		sum += a[i];
	}
	if (sum == 0)
	{
		cout << 0;
		return 0;
	}
	double p = a[k - 1] / sum;
	printf("%.13lf", p);
	return 0;
}