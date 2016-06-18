#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

int n, k, c, m;
double x = 0;

int main()
{
	freopen ("exam.in", "r", stdin);
	freopen ("exam.out", "w", stdout);
	cin >> k >> n;
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &c);
		scanf("%d", &m);
		double k = double(c) / double(n);
		double r = double(m) / 100;
		double p = k * r;
		x += p;
	}
	cout.precision(5);
	cout << x;
	return 0;
}