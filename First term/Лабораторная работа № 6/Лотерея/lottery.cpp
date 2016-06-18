#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

int n, m, a, b[100010];

int main()
{
	freopen ("lottery.in", "r", stdin);
	freopen ("lottery.out", "w", stdout);
	cin >> n >> m;
	b[0] = 0;
	double p = 1, sum = 0;
	for (int i = 1; i <= m; i++)
	{
		double k = p;
		cin >> a >> b[i];
		p /= a;
		double r = 1;
		r /= a;
		k *= 1 - r;
		sum += k * b[i - 1];
	}
	sum += p * b[m];
	double ans = n - sum;
	cout << ans;
	return 0;
}